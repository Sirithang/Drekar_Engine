#include "component/light/DirectionalLight.h"
#include "component/Camera.h"
#include "renderer/Renderer.h"

#include "core/GameObject.h"

using namespace de;
using namespace de::component;
using namespace de::data;

COMPONENT_DEF_TYPE(DirectionalLight);

void DirectionalLight::init()
{
	de::renderer::Renderer::current()->addDirectionaLight(this);
}

///-----------------------

void DirectionalLight::setup(Program* pProg)
{
	Light::setup(pProg);

	glm::mat4 toView = glm::transpose(glm::inverse((Camera::current()->viewMatrix())));

	glm::vec4 viewLightDirection = toView * glm::vec4(mOwner->transform()->forward(), 0.0f);

	pProg->setVector4("_LightDirection", viewLightDirection);
}