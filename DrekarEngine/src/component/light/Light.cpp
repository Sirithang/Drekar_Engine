#include "component/light/Light.h"

using namespace de;
using namespace de::component;

std::multimap<unsigned char, Light*> Light::sLights;

Light::Light(unsigned char pType)
{
	mIntensity = 0;
	mColor = glm::vec3(1,1,1);
	mType = pType;

	mIterator = sLights.insert(std::pair<unsigned char, Light*>(pType, this));
}

Light::~Light()
{
	sLights.erase(mIterator);
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

void Light::internalSetup(Program* pProg)
{
	pProg->setVector4("_LightColor", glm::vec4(mColor, 1.0f));
}

Light::multimap_t& Light::getLights()
{
	return sLights;
}