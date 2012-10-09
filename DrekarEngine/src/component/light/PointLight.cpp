#include <glm/glm.hpp>

#include "component/Camera.h"
#include "core/GameObject.h"
#include "component/light/PointLight.h"
#include "renderer/Renderer.h"

using namespace de;
using namespace de::component;

Material*	PointLight::sPointLightMaterial = nullptr;
data::Mesh*	PointLight::sMesh = nullptr;

PointLight::PointLight()
	:Light(2)
{
	if(sPointLightMaterial == nullptr)
	{
		sPointLightMaterial = AssetDatabase::load<Material>("data/internals/lights/point/PointLight.mat");
		sMesh = AssetDatabase::load<data::Mesh>("data/internals/lights/point/sphere.mesh");
	}
}

void PointLight::init()
{
	mRange = 20.0f;
}

//--------------------------------------------

void PointLight::setup()
{
	Light::internalSetup(sPointLightMaterial->program());

	sPointLightMaterial->program()->setVector4("_LightPos", glm::vec4(mOwner->transform()->position(), 0.0f));
	sPointLightMaterial->program()->setMatrix("MATRIX_M", glm::scale(glm::translate(glm::mat4(), mOwner->transform()->position()), glm::vec3(mRange, mRange, mRange)));
	sPointLightMaterial->program()->setFloat("_Radius", mRange);

	sMesh->draw();
}

//---------------------------------------------

void PointLight::setupLightType(de::data::Texture* pAlbedo, de::data::Texture* pNormal, de::data::Texture* pDepth)
{
	sPointLightMaterial->addTexture("_Albedo", pAlbedo);
	sPointLightMaterial->addTexture("_Normal", pNormal);
	sPointLightMaterial->addTexture("_Depth",  pDepth);

	sPointLightMaterial->setup();
	sPointLightMaterial->program()->setMatrix("_InvertVP", glm::inverse(component::Camera::current()->projectionMatrix() * component::Camera::current()->viewMatrix()));
	sPointLightMaterial->program()->setMatrix("MATRIX_P", component::Camera::current()->projectionMatrix());
	sPointLightMaterial->program()->setMatrix("MATRIX_V", component::Camera::current()->viewMatrix());

	sPointLightMaterial->program()->setVector4("_CamPos", glm::vec4(component::Camera::current()->owner()->transform()->position(), 1.0f));
}

//---------------------------------------------
float PointLight::range() const
{
	return mRange;
}

//--------------------------------------------

void PointLight::renderShadowmap()
{

}