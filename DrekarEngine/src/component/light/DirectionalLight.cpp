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
	
}

//-----------------------

void DirectionalLight::setupLightType(de::data::Texture* pAlbedo, de::data::Texture* pNormal, de::data::Texture* pDepth)
{
	sDiretionalLightMat->addTexture("_Albedo", pAlbedo);
	sDiretionalLightMat->addTexture("_Normal", pNormal);
	sDiretionalLightMat->addTexture("_Depth",  pDepth);

	sDiretionalLightMat->setup(false);
	sDiretionalLightMat->program()->setMatrix("_InvertP", glm::inverse(component::Camera::current()->projectionMatrix()));
}

///-----------------------

void DirectionalLight::setup()
{
	Light::internalSetup(sDiretionalLightMat->program());

	glm::mat4 toView = glm::transpose(glm::inverse((Camera::current()->viewMatrix())));

	glm::vec4 viewLightDirection = toView * glm::vec4(mOwner->transform()->forward(), 0.0f);

	sDiretionalLightMat->program()->setVector4("_LightDirection", viewLightDirection);

	Helpers::drawQuad();
}