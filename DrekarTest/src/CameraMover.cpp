#include "CameraMover.h"
#include "io/AInput.h"
#include "core/GameObject.h"
#include "core/GameTime.h"

using namespace de;

void CameraMover::init()
{
	mKeyboard = InputManager::getInputFromName("Keyboard");
	mMouse = InputManager::getInputFromName("Mouse");

	mLastMousePos.x = mMouse->getAxis("mouseX");
	mLastMousePos.y = mMouse->getAxis("mouseY");
}

void CameraMover::update()
{
	if(mKeyboard->getAxis("Z"))
	{
		mOwner->transform()->setPosition(mOwner->transform()->position() + mOwner->transform()->forward() * (GameTime::deltaTime() * 10));
	}

	if(mKeyboard->getAxis("S"))
	{
		mOwner->transform()->setPosition(mOwner->transform()->position() + mOwner->transform()->forward() * (GameTime::deltaTime() * -10));
	}

	if(mKeyboard->getAxis("Q"))
	{
		mOwner->transform()->setPosition(mOwner->transform()->position() + mOwner->transform()->left() * (GameTime::deltaTime() * 10));
	}

	if(mKeyboard->getAxis("D"))
	{
		mOwner->transform()->setPosition(mOwner->transform()->position() + mOwner->transform()->left() * (GameTime::deltaTime() * -10));
	}


	//----------------- mouse handling

	glm::vec2 currentMouse;

	currentMouse.x = mMouse->getAxis("mouseX");
	currentMouse.y = mMouse->getAxis("mouseY");

	if(mMouse->getAxis("leftButton") > 0.1f)
	{

		glm::vec2 delta = currentMouse - mLastMousePos;

		mOwner->transform()->setRotation(glm::rotate(mOwner->transform()->rotation(), delta.x * -20.0f * GameTime::deltaTime(), glm::vec3(0,1,0)));
		mOwner->transform()->setRotation(glm::rotate(mOwner->transform()->rotation(), delta.y * 20.0f * GameTime::deltaTime(), glm::vec3(1,0,0)));
	}

	mLastMousePos = currentMouse;
}