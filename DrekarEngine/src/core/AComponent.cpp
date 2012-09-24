#include "core/AComponent.h"

using namespace de;

AComponent::AComponent()
{
	mOwner = nullptr;
}

//------------------------

GameObject* AComponent::owner()
{
	return mOwner;
}

//-------------------------

void AComponent::init()
{

}

//------------------------

void AComponent::update()
{

}

//-----------------------

void AComponent::preDraw()
{

}

//----------------------

void AComponent::render()
{
}

//----------------------

void AComponent::fromJSON(const std::string& pData)
{

}