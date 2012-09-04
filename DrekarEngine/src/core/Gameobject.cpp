#include "core/Gameobject.h"

using namespace de;

std::list<GameObject*> GameObject::sGameObjects;

GameObject::GameObject()
{
	mTransform = new component::Transform();
	addComponent(mTransform);

	sGameObjects.push_back(this);
}


void GameObject::release()
{
	std::list<GameObject*>::iterator lChild = mChildren.begin();
	while(lChild != mChildren.end())
	{
		(*lChild)->release();
		lChild++;
	}

	mChildren.clear();

	std::list<AComponent*>::iterator lIt = mComponents.begin();
	while(lIt != mComponents.end())
	{
		delete (*lIt);
		lIt++;
	}

	mComponents.clear();
}

//----------------------

void GameObject::internalUpdate()
{
	std::list<GameObject*>::iterator lChild = mChildren.begin();
	while(lChild != mChildren.end())
	{
		(*lChild)->internalUpdate();
		lChild++;
	}

	std::list<AComponent*>::iterator lIt = mComponents.begin();
	while(lIt != mComponents.end())
	{
		(*lIt)->update();
		lIt++;
	}
}

//---------------------

void GameObject::internalDraw()
{
	std::list<GameObject*>::iterator lChild = mChildren.begin();
	while(lChild != mChildren.end())
	{
		(*lChild)->internalDraw();
		lChild++;
	}

	std::list<AComponent*>::iterator lIt = mComponents.begin();
	while(lIt != mComponents.end())
	{
		(*lIt)->preDraw();
		lIt++;
	}
}

//--------------------

void GameObject::update()
{
	std::list<GameObject*>::iterator lChild = mChildren.begin();
	while(lChild != mChildren.end())
	{
		(*lChild)->update();
		lChild++;
	}
}

//--------------------

void GameObject::draw()
{
	std::list<GameObject*>::iterator lChild = mChildren.begin();
	while(lChild != mChildren.end())
	{
		(*lChild)->draw();
		lChild++;
	}
}

//-------------------

AComponent* GameObject::addComponent(AComponent* pComponent)
{
	mComponents.push_back (pComponent);
	pComponent->mOwner = this;
	pComponent->init();

	return pComponent;
}

//------------------

void GameObject::addChild(GameObject* pChild)
{
	mChildren.push_back(pChild);
}