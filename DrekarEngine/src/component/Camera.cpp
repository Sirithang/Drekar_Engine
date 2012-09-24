#include "component/camera.h"
#include "core/Gameobject.h"
#include "core/Debug.h"

using namespace de::component;

COMPONENT_DEF_TYPE(Camera);

std::list<Camera*>	Camera::sCameraList;
Camera*				Camera::sCurrent = nullptr;

void Camera::init()
{
	sCameraList.push_front(this);

	mFov = 60.0f;
	mAspect = 4.0f/3.0f;
	mClipPlanes = glm::vec2(0.01f, 100.0f);

	mRecomputeProjecton = false;

	computeProjection();
}

void Camera::update()
{
	glm::vec3 up = mOwner->transform()->up();
	glm::vec3 pos		= mOwner->transform()->position();
	glm::vec3 target	= pos + mOwner->transform()->forward();
	mView = glm::lookAt(pos, target, up);
}

void Camera::release()
{
	sCameraList.remove(this);
}

//--------------------------------

float Camera::fov() const
{
	return mFov;
}

//---------------------------------

void Camera::computeProjection()
{
	mProjection = glm::perspective(mFov, mAspect, mClipPlanes.x, mClipPlanes.y);
}

//-------------------------------

void Camera::setFov(float pFov)
{
	mFov = pFov;
	mRecomputeProjecton = true;
}

//-----------------------------

void Camera::setAspect(float pAspect)
{
	mAspect = pAspect;
	mRecomputeProjecton = true;
}

//----------------------------

void Camera::setClipPlane(glm::vec2& pClipPlane)
{
	mClipPlanes = pClipPlane;
	mRecomputeProjecton = true;
}

//---------------------------

const glm::mat4& Camera::projectionMatrix()
{
	return mProjection;
}

//---------------------------

const glm::mat4& Camera::viewMatrix()
{
	return mView;
}

//---------------------------

const std::list<Camera*>& Camera::cameraList()
{
	return sCameraList;
}

//--------------------------

Camera* Camera::current()
{
	return sCurrent;
}

//-------------------------

void Camera::setup()
{
	sCurrent = this;
	if(mRecomputeProjecton)
	{
		computeProjection();
		mRecomputeProjecton = false;
	}
}