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
	std::list<GameObject*>::iterator lIt = GameObject::sGameObjects.begin();

	while(lIt != GameObject::sGameObjects.end())
	{
		(*lIt)->update();
		
		lIt++;
	}
}

//---------------------

void AScreen::draw()
{
}

//---------------------

void AScreen::internalUpdate()
{
	std::list<GameObject*>::iterator lIt = GameObject::sGameObjects.begin();

	while(lIt != GameObject::sGameObjects.end())
	{
		(*lIt)->internalUpdate();
		lIt++;
	}
	
}

//---------------------

void AScreen::internalDraw()
{

	const std::list<Camera*> lCamList = Camera::cameraList();

	std::list<Camera*>::const_iterator lIt = lCamList.begin();

	while(lIt != lCamList.end())
	{
		(*lIt)->setup();

		lIt++;
	}
}