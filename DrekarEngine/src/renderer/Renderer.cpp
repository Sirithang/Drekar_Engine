#include "renderer/Renderer.h"
#include "core/Engine.h"
#include "core/Helpers.h"
#include "core/ARenderable.h"

#include "internal/InternalData.h"
#include "component/Camera.h"

using namespace de;
using namespace de::renderer;

Renderer* Renderer::sCurrent = nullptr;

Renderer::Renderer()
{
	mRenderBuffer.init(de::Engine::width(), de::Engine::height());

	mAlbedo = (*mRenderBuffer.getTextures().begin());

	mNormal = new de::data::Texture();
	mNormal->create(de::Engine::width(), de::Engine::height());
	mNormal->init(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);

	mRenderBuffer.addTexture(mNormal);

	mDepth  = new de::data::Texture();
	mDepth->create(de::Engine::width(), de::Engine::height());
	mDepth->init( GL_LUMINANCE32F_ARB, GL_LUMINANCE, GL_FLOAT);

	mRenderBuffer.addTexture(mDepth);

	mAmbient = glm::vec3(0,0,0);

	buildClearMat();
	buildLightBufferMat();
	buildCombineMat();
}

//---------------------------

void Renderer::buildCombineMat()
{
	de::data::Shader lGBufferVert(de::data::Shader::VERTEX);
	lGBufferVert.loadShaderFromFile("data/Combine.vert");

	de::data::Shader lGBufferFrag(de::data::Shader::PIXEL);;
	lGBufferFrag.loadShaderFromFile("data/Combine.frag");

	de::Program* lGBufferProg = new de::Program();
	lGBufferProg->addShader(lGBufferVert);
	lGBufferProg->addShader(lGBufferFrag);
	lGBufferProg->compile();

	std::list<data::Texture*>::const_iterator lIt = mRenderBuffer.getTextures().begin();

	mCombineMaterial.setProgram(lGBufferProg);
	mCombineMaterial.addTexture("_Albedo", (*lIt));
	mCombineMaterial.addTexture("_Light", (*mLightBuffer.getTextures().begin()));
}


void Renderer::buildClearMat()
{
	de::data::Shader lClearVert(de::data::Shader::VERTEX);
	lClearVert.loadShader(gClearMRTVert);

	de::data::Shader lClearFrag(de::data::Shader::PIXEL);
	lClearFrag.loadShader(gCleanMRTFrag);

	de::Program* lCleanProg = new de::Program();
	lCleanProg->addShader(lClearVert);
	lCleanProg->addShader(lClearFrag);
	lCleanProg->compile();

	mClearMaterial.setProgram(lCleanProg);
}

//---------------------------

void Renderer::buildLightBufferMat()
{
	mLightBuffer.init(de::Engine::width(), de::Engine::height());
}

//--------------------------

Renderer* Renderer::current()
{
	return sCurrent;
}

//--------------------------

void Renderer::setAmbient(const glm::vec3& pAmbientColor)
{
	mAmbient = pAmbientColor;
}

//--------------------------

void Renderer::setup()
{
	sCurrent = this;
}

//--------------------------

void Renderer::render()
{

	//------------------GBUFFER
	mRenderBuffer.bind();

	// -- clear the buffers
	glDisable(GL_DEPTH_TEST);
	mClearMaterial.setup(false);
	Helpers::drawQuad();
	glEnable(GL_DEPTH_TEST);

	glClear(GL_DEPTH_BUFFER_BIT);


	//---------list buding

	std::list<ARenderable*> renderabeList = ARenderable::getRenderables();

	typedef std::multimap<uint32_t, ARenderable*>  multimap_renderer;
	multimap_renderer orderedList;

	std::list<ARenderable*>::iterator lIt = renderabeList.begin();

	while(lIt != renderabeList.end())
	{//building the ordered map, ordered by the key (containing material and other infos)
		orderedList.insert(std::pair<uint32_t, ARenderable*>((*lIt)->getKey(), (*lIt)));
		lIt++;
	}

	//--------------------

	uint16_t lastMatID = 0;

	multimap_renderer::iterator itRendederer = orderedList.begin();
	while(itRendederer != orderedList.end())
	{
		uint32_t key = itRendederer->first;
		uint16_t materialID = key & 0x0000FFFF;

		if(materialID != lastMatID)
		{
			lastMatID = materialID;
			itRendederer->second->setup();
		}

		itRendederer->second->render();
		itRendederer++;
	}

	mRenderBuffer.unbind();

	///------ LIGHT BUFFER
	mLightBuffer.bind();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc (GL_ONE, GL_ONE);

	glClearColor(mAmbient.r, mAmbient.g, mAmbient.b, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);


	component::Light::multimap_t mapLight = component::Light::getLights();

	component::Light::multimap_t::iterator itLight = mapLight.begin();

	unsigned char previousLightType = 0;
	while(itLight != mapLight.end())
	{
		if(itLight->first != previousLightType)
		{
			itLight->second->setupLightType(mAlbedo, mNormal, mDepth);
		}

		itLight->second->setup();
		itLight++;
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	mLightBuffer.unbind();

	mCombineMaterial.setup(false);

	Helpers::drawQuad();
}

//------------------------