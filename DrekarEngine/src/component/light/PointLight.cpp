#include <glm/glm.hpp>

#include "component/Camera.h"
#include "core/GameObject.h"
#include "component/light/PointLight.h"
#include "renderer/Renderer.h"

using namespace de;
using namespace de::component;

void PointLight::init()
{
	mRange = 20.0f;
	de::renderer::Renderer::current()->addPointLight(this);
}

//--------------------------------------------

void PointLight::setup(Program* pProg)
{
	Light::setup(pProg);

	glm::vec4 viewPos = Camera::current()->viewMatrix() * glm::vec4(mOwner->transform()->position(), 1.0f);// * glm::vec4(0,0,0,1) ;

	viewPos.x /= viewPos.w;
	viewPos.y /= viewPos.w;
	viewPos.z /= viewPos.w;

	pProg->setVector4("_LightPos", viewPos);
	pProg->setMatrix("MATRIX_M", glm::scale(glm::translate(glm::mat4(), mOwner->transform()->position()), glm::vec3(mRange, mRange, mRange)));
	pProg->setFloat("_Radius", mRange);
}

//---------------------------------------------
float PointLight::range() const
{
	return mRange;
}