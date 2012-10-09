#include "component/light/DirectionalLight.h"
#include "component/Camera.h"
#include "renderer/Renderer.h"

#include "core/GameObject.h"
#include "core/Helpers.h"

using namespace de;
using namespace de::component;
using namespace de::data;

COMPONENT_DEF_TYPE(DirectionalLight);

de::Material* DirectionalLight::sDiretionalLightMat = nullptr;

DirectionalLight::DirectionalLight() 
	: Light(1)
{
	if(sDiretionalLightMat == nullptr)
	{
		sDiretionalLightMat = AssetDatabase::load<Material>("data/internals/lights/directional/DirectionalLight.mat");
	}
}

//-------------------------

void DirectionalLight::init()
{
	mShadowmapBuffer.init(512, 512, false);
	
	mShadowmap.create(512, 512);
	mShadowmap.init(GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_FLOAT);

	mShadowmap.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	mShadowmap.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	mShadowmapBuffer.addTexture(&mShadowmap, GL_DEPTH_ATTACHMENT);

	mLightGameobject = new GameObject();
	mLightCamera = (Camera*)mLightGameobject->addComponent(new Camera());

	mLightCamera->setOrtho(true);
	mLightCamera->setClipPlane(glm::vec2(0.01f, 1000.0f));
	mLightCamera->setOrthoHalfSize(100);
	mLightCamera->setAspect(1.0f);
}

//-----------------------

void DirectionalLight::setupLightType(de::data::Texture* pAlbedo, de::data::Texture* pNormal, de::data::Texture* pDepth)
{
	sDiretionalLightMat->addTexture("_Albedo", pAlbedo);
	sDiretionalLightMat->addTexture("_Normal", pNormal);
	sDiretionalLightMat->addTexture("_Depth",  pDepth);

	sDiretionalLightMat->setup(false);
	sDiretionalLightMat->program()->setMatrix("_InvertVP", glm::inverse(component::Camera::current()->projectionMatrix() * component::Camera::current()->viewMatrix()));
	sDiretionalLightMat->program()->setVector4("_CamPos", glm::vec4(component::Camera::current()->owner()->transform()->position(), 1.0f));
}

///-----------------------

void DirectionalLight::setup()
{
	Light::internalSetup(sDiretionalLightMat->program());

	sDiretionalLightMat->program()->setVector4("_LightDirection", glm::vec4(mOwner->transform()->forward(), 0.0f));
	sDiretionalLightMat->addTexture("_ShadowMap", &mShadowmap, true);
	sDiretionalLightMat->program()->setMatrix("_VPLight", mLightCamera->projectionMatrix() * mLightCamera->viewMatrix());

	Helpers::drawQuad();
}

//------------------------------

void DirectionalLight::renderShadowmap()
{
	Camera* pPrevious = Camera::current();

	mLightGameobject->transform()->setRotation(mOwner->transform()->rotation());
	mLightGameobject->transform()->setPosition(Camera::current()->owner()->transform()->position() - mLightGameobject->transform()->forward() * 30.0f);

	mLightCamera->setup();

	mShadowmapBuffer.bind();

	glClear(GL_DEPTH_BUFFER_BIT);

	Camera::current()->setReplacementMaterial(AssetDatabase::load<Material>("data/internals/depthOnly/depth.mat"));

	renderer::Renderer::current()->sortRenderList();
	renderer::Renderer::current()->renderOpaque();

	Camera::current()->setReplacementMaterial(nullptr);

	mShadowmapBuffer.unbind();

	pPrevious->setup();
}