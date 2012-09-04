#include <glm/glm.hpp>

#include "component/Camera.h"
#include "core/GameObject.h"
#include "component/light/PointLight.h"
#include "renderer/Renderer.h"

using namespace de;
using namespace de::component;

void PointLight::init()
{
	mRange = 10.0f;
	de::renderer::Renderer::current()->addPointLight(this);
}

//--------------------------------------------

void PointLight::setup(Program* pProg)
{
	Light::setup(pProg);

	glm::vec4 viewPos = glm::vec4(0,0,0,1.0f) * mOwner->transform()->matrix() * Camera::current()->viewMatrix() ;

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