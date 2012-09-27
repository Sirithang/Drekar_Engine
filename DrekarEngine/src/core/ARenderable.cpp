#include "core/ARenderable.h"

using namespace de;

std::list<ARenderable*> ARenderable::sRenderables;

ARenderable::ARenderable()
{
	sRenderables.push_back(this);
}

//----------------------------------

ARenderable::~ARenderable()
{
	sRenderables.remove(this);
}

//---------------------------------

std::list<ARenderable*>& ARenderable::getRenderables()
{
	return sRenderables;
}