#include "component/Transform.h"
#include <glm/gtc/swizzle.hpp>

using namespace de::component;

COMPONENT_DEF_TYPE(Transform);

Transform::Transform()
	:	mPosition(0,0,0),
		mLocalPosition(0,0,0),
		mRotation(glm::vec3(0,0,0)),
		mLocalRotation(glm::vec3(0,0,0)),
		mLocalScale(1,1,1)
{
	mChanged = true;
	mParent = nullptr;
}

//--------------------------------------

void Transform::update()
{
	
}

//-------------------------------------

bool Transform::recomputed() const
{
	return mRecomputed;
}

//------------------------------------

void Transform::recomputeMatrix()
{
	mMatrix = glm::translate(glm::mat4(),mPosition) * glm::mat4_cast(mRotation) * glm::scale(glm::mat4(), mLocalScale);

	if(mParent != nullptr)
	{
		mCombinedMatrix = mParent->matrix() * mMatrix;
	}

	if(mChildren.size() > 0)
	{
		std::list<Transform*>::iterator lIt = mChildren.begin();
		while(lIt != mChildren.end())
		{
			(*lIt)->parentChanged();
			lIt++;
		}
	}
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

	if(mParent != nullptr)
	{
		glm::vec4 local =  glm::inverse(mParent->matrix()) * glm::vec4(mPosition,1.0f);
		mLocalPosition = glm::vec3(glm::swizzle<glm::X, glm::Y, glm::Z>(local)) / local.w;
	}
	else
		mLocalPosition = mPosition;

	recomputeMatrix();
}

void Transform::setLocalPosition(const glm::vec3& pPosition)
{
	mLocalPosition = pPosition;

	if(mParent != nullptr)
	{
		glm::vec4 global = mParent->matrix()*glm::vec4(mLocalPosition, 1.0f);
		mPosition = glm::vec3(glm::swizzle<glm::X, glm::Y, glm::Z>(global)) / global.w;
	}
	else
		mPosition = pPosition;

	recomputeMatrix();
}

//---------------------------------

void Transform::setRotation(const glm::quat& pRotation)
{
	mRotation = pRotation;
	recomputeMatrix();
}

//---------------------------------

void Transform::setScale(glm::vec3 pScale)
{
	mLocalScale = pScale;
	recomputeMatrix();
}

//---------------------------------

glm::vec3 Transform::forward() const
{
	return glm::normalize(mRotation * glm::vec3(0,0,1));
}

//---------------------------------

glm::vec3 Transform::up() const
{
	return glm::normalize(mRotation * glm::vec3(0,1,0));
}

//--------------------------------

glm::vec3 Transform::left() const
{
	return glm::normalize(mRotation * glm::vec3(1,0,0));
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

//------------------------------

void Transform::parentChanged()
{
	mPosition = glm::vec3(mParent->matrix() * glm::vec4(mLocalPosition, 1.0f));

	recomputeMatrix();
}

//------------------------------

void Transform::setParent(Transform* pParent)
{
	if(pParent == mParent)
		return;

	if(pParent == nullptr)
	{
		if(mParent != nullptr)
		{
			mParent->mChildren.remove(this);
		}
	}
	else
	{
		pParent->mChildren.push_back(this);
	}

	mParent = pParent;
}