#include "component/Transform.h"

using namespace de::component;

Transform::Transform()
	:	mPosition(0,0,0),
		mLocalPosition(0,0,0),
		mRotation(glm::vec3(0,0,0)),
		mLocalRotation(glm::vec3(0,0,0)),
		mLocalScale(1,1,1)
{
	mChanged = true;
}

//--------------------------------------

void Transform::update()
{
	mRecomputed = false;
	if(mChanged)
	{
		mMatrix = glm::translate(glm::mat4(),mPosition) * glm::mat4_cast(mRotation) * glm::scale(glm::mat4(), mLocalScale);
		mChanged = false;
		mRecomputed = true;
	}
}

//-------------------------------------

bool Transform::recomputed() const
{
	return mRecomputed;
}

//------------------------------------

glm::mat4 Transform::matrix() const
{
	return mMatrix;
}

//----------------------------------

void Transform::setPosition(const glm::vec3& pPosition)
{
	mPosition = pPosition;
	mChanged = true;
}

//---------------------------------

void Transform::setRotation(const glm::quat& pRotation)
{
	mRotation = pRotation;
	mChanged = true;
}

//---------------------------------

void Transform::setScale(glm::vec3 pScale)
{
	mLocalScale = pScale;
	mChanged = true;
}

//---------------------------------

glm::vec3 Transform::forward()
{
	return glm::normalize(mRotation * glm::vec3(0,0,1));
}

//---------------------------------

glm::vec3 Transform::up()
{
	return glm::normalize(mRotation * glm::vec3(0,1,0));
}

//--------------------------------

const glm::vec3& Transform::position()
{
	return mPosition;
}

//------------------------------

const glm::quat& Transform::rotation()
{
	return mRotation;
}

//------------------------------

const glm::vec3& Transform::scale()
{
	return mLocalScale;
}