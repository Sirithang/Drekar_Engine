#include "core/AScreen.h"
#include "component/Camera.h"

using namespace de;
using namespace de::component;

//----------------------

void AScreen::init()
{

}

//---------------------

void AScreen::update()
{
}

//---------------------

void AScreen::draw()
{
}

//---------------------

void AScreen::internalUpdate()
{
	mRoot.update();
	mRoot.internalUpdate();
}

//---------------------

void AScreen::internalDraw()
{
	mRoot.draw();

	const std::list<Camera*> lCamList = Camera::cameraList();

	std::list<Camera*>::const_iterator lIt = lCamList.begin();

	while(lIt != lCamList.end())
	{
		(*lIt)->setup();

		mRoot.internalDraw();

		lIt++;
	}
}