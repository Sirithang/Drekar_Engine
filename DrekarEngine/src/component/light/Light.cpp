#include "component/light/Light.h"

using namespace de;
using namespace de::component;

Light::Light()
{
	mIntensity = 0;
	mColor = glm::vec3(1,1,1);
}

//-----------------------------

float Light::intensity() const
{
	return mIntensity;
}

glm::vec3 Light::color() const
{
	return mColor;
}

void Light::setIntensity(float pValue)
{
	mIntensity = pValue;
}

void Light::setColor(const glm::vec3 & pValue)
{
	mColor = glm::clamp(pValue, glm::vec3(0,0,0),glm::vec3(1,1,1));
}

void Light::setup(Program* pProg)
{
	pProg->setVector4("_LightColor", glm::vec4(mColor, 1.0f));
}