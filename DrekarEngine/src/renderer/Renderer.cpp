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

	glBlendFunc (GL_ONE, GL_ONE);
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
	glClearColor(mAmbient.r, mAmbient.g, mAmbient.b, 0.0);
}

//--------------------------

void Renderer::setup()
{
	sCurrent = this;
}

//--------------------------

void Renderer::sortRenderList()
{
	//---------list buding

	mOrderedList.clear();

	std::list<ARenderable*> renderabeList = ARenderable::getRenderables();

	std::list<ARenderable*>::iterator lIt = renderabeList.begin();

	if(component::Camera::current()->replacementMaterial() == nullptr)
	{
		while(lIt != renderabeList.end())
		{//building the ordered map, ordered by the key (containing material and other infos)
			mOrderedList.insert(std::pair<uint32_t, ARenderable*>((*lIt)->getKey(), (*lIt)));
			lIt++;
		}
	}
	else
	{
		uint32_t key = 0;
		key |= (uint32_t)component::Camera::current()->replacementMaterial()->getID();

		while(lIt != renderabeList.end())
		{//building the ordered map, ordered by the key (containing material and other infos)
			mOrderedList.insert(std::pair<uint32_t, ARenderable*>(key, (*lIt)));
			lIt++;
		}
	}
}

//-------------------------

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

	sortRenderList();
	renderOpaque();

	mRenderBuffer.unbind();

	///------ LIGHT BUFFER
	
	component::Light::multimap_t mapLight = component::Light::getLights();

	component::Light::multimap_t::iterator itLight = mapLight.begin();

	//**Render shadowmap

	while(itLight != mapLight.end())
	{
		itLight->second->renderShadowmap();
		itLight++;
	}

	//**Render lightbuffer
	mLightBuffer.bind();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);

	glClear(GL_COLOR_BUFFER_BIT);

	itLight = mapLight.begin();

	unsigned char previousLightType = 0;
	while(itLight != mapLight.end())
	{
		if(itLight->first != previousLightType)
		{
			itLight->second->setupLightType(mAlbedo, mNormal, mDepth);
			previousLightType = itLight->first;
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

void Renderer::renderOpaque()
{
	//------ render opaque geometry -----

	uint16_t lastMatID = 0;

	multimap_renderer::iterator itRendederer = mOrderedList.begin();
	while(itRendederer != mOrderedList.end())
	{
		uint32_t key = itRendederer->first;
		uint16_t materialID = key & 0x0000FFFF;

		if(materialID != lastMatID)
		{
			lastMatID = materialID;
			Material::getMaterialFromID(materialID)->setup();
		}

		itRendederer->second->render();
		itRendederer++;
	}
}