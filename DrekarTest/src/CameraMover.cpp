#include "CameraMover.h"
#include "io/AInput.h"
#include "core/GameObject.h"
#include "core/GameTime.h"

using namespace de;

void CameraMover::init()
{
	mInput = InputManager::getInputFromName("Keyboard");
}

void CameraMover::update()
{
	if(mInput->getAxis("Z"))
	{
		mOwner->transform()->setPosition(mOwner->transform()->position() + mOwner->transform()->forward() * (GameTime::deltaTime() * 10));
	}

	if(mInput->getAxis("S"))
	{
		mOwner->transform()->setPosition(mOwner->transform()->position() + mOwner->transform()->forward() * (GameTime::deltaTime() * -10));
	}

	if(mInput->getAxis("Q"))
	{
		mOwner->transform()->setPosition(mOwner->transform()->position() + mOwner->transform()->left() * (GameTime::deltaTime() * 10));
	}

	if(mInput->getAxis("D"))
	{
		mOwner->transform()->setPosition(mOwner->transform()->position() + mOwner->transform()->left() * (GameTime::deltaTime() * -10));
	}
}