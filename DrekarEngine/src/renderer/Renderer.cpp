#include "renderer/Renderer.h"
#include "core/Engine.h"
#include "core/Helpers.h"

#include "internal/InternalData.h"
#include "component/Camera.h"

using namespace de;
using namespace de::renderer;

Renderer* Renderer::sCurrent = nullptr;

Renderer::Renderer()
{
	mRenderBuffer.init(de::Engine::width(), de::Engine::height());

	de::data::Texture* lNormalTex = new de::data::Texture();
	lNormalTex->create(de::Engine::width(), de::Engine::height(), GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);

	mRenderBuffer.addTexture(lNormalTex);

	de::data::Texture* lDepthTex  = new de::data::Texture();
	lDepthTex->create(de::Engine::width(), de::Engine::height(), GL_LUMINANCE32F_ARB, GL_LUMINANCE, GL_FLOAT);

	mRenderBuffer.addTexture(lDepthTex);

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

	
	initDirectionalLights();
	initPointLights();
}

//--------------------------

void Renderer::initDirectionalLights()
{
	de::data::Shader lDirectionalVert(de::data::Shader::VERTEX);
	lDirectionalVert.loadShaderFromFile("data/DirectionalLight.vert");

	de::data::Shader lDirectionalFrag(de::data::Shader::PIXEL);;
	lDirectionalFrag.loadShaderFromFile("data/DirectionalLight.frag");

	de::Program* lGBufferProg = new de::Program();
	lGBufferProg->addShader(lDirectionalVert);
	lGBufferProg->addShader(lDirectionalFrag);
	lGBufferProg->compile();

	std::list<data::Texture*>::const_iterator lIt = mRenderBuffer.getTextures().begin();

	mDiretionalLightMat.setProgram(lGBufferProg);
	mDiretionalLightMat.addTexture("_Albedo", (*lIt));
	lIt++;
	mDiretionalLightMat.addTexture("_Normal", (*lIt));
	lIt++;
	mDiretionalLightMat.addTexture("_Depth",   (*lIt));
}

//--------------------------

void Renderer::initPointLights()
{
	de::data::Shader lDirectionalVert(de::data::Shader::VERTEX);
	lDirectionalVert.loadShaderFromFile("data/PointLight.vert");

	de::data::Shader lDirectionalFrag(de::data::Shader::PIXEL);;
	lDirectionalFrag.loadShaderFromFile("data/PointLight.frag");

	de::Program* lGBufferProg = new de::Program();
	lGBufferProg->addShader(lDirectionalVert);
	lGBufferProg->addShader(lDirectionalFrag);
	lGBufferProg->compile();

	std::list<data::Texture*>::const_iterator lIt = mRenderBuffer.getTextures().begin();

	mPointLightsMat.setProgram(lGBufferProg);
	mPointLightsMat.addTexture("_Albedo", (*lIt));
	lIt++;
	mPointLightsMat.addTexture("_Normal", (*lIt));
	lIt++;
	mPointLightsMat.addTexture("_Depth",   (*lIt));

	mPointLightsMesh.loadFromFile("data/sphere.mesh");
	mPointLightsMesh.uploadToVRAM();
}


//--------------------------

Renderer* Renderer::current()
{
	return sCurrent;
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
	mClearMaterial.setup();
	Helpers::drawQuad();
	glEnable(GL_DEPTH_TEST);

	glClear(GL_DEPTH_BUFFER_BIT);

	std::list<AComponent*>::iterator lIt = mRenderables.begin();
	while(lIt != mRenderables.end())
	{
		(*lIt)->render();
		lIt++;
	}

	mRenderBuffer.unbind();

	///------ LIGHT BUFFER
	mLightBuffer.bind();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc (GL_ONE, GL_ONE);

	glClearColor(mAmbient.r, mAmbient.g, mAmbient.b, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);


	renderDirectionalLights();
	renderPointLights();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	mLightBuffer.unbind();

	mCombineMaterial.setup();

	Helpers::drawQuad();
}

//-------------------------

void Renderer::addRenderable(AComponent* pComponent)
{
	mRenderables.push_back(pComponent);
}

//------------------------

void Renderer::removeRenderable(AComponent* pComponent)
{
	mRenderables.remove(pComponent);
}

//---------------------------

void Renderer::addDirectionaLight(de::component::DirectionalLight* pLight)
{
	mDirectionalLights.push_back(pLight);
}

//----------------------------

void Renderer::addPointLight(de::component::PointLight* pLight)
{
	mPointLights.push_back(pLight);
}

//---------------------------

void Renderer::renderDirectionalLights()
{
	std::list<de::component::DirectionalLight*>::iterator lIt = mDirectionalLights.begin();
	mDiretionalLightMat.setup();
	mDiretionalLightMat.program()->setMatrix("_InvertP", glm::inverse(component::Camera::current()->projectionMatrix()));

	while(lIt != mDirectionalLights.end())
	{
		(*lIt)->setup(mDiretionalLightMat.program());

		Helpers::drawQuad();

		lIt++;
	}
}

//------------------------

void Renderer::renderPointLights()
{
	std::list<de::component::PointLight*>::iterator lIt = mPointLights.begin();
	mPointLightsMat.setup();
	mPointLightsMat.program()->setMatrix("_InvertP", glm::inverse(component::Camera::current()->projectionMatrix()));
	mPointLightsMat.program()->setMatrix("MATRIX_P", component::Camera::current()->projectionMatrix());
	mPointLightsMat.program()->setMatrix("MATRIX_V", component::Camera::current()->viewMatrix());

	while(lIt != mPointLights.end())
	{
		(*lIt)->setup(mPointLightsMat.program());

		mPointLightsMesh.draw();

		lIt++;
	}
}