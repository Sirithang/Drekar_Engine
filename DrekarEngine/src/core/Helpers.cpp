#include "core/Helpers.h"

using namespace de;

Helpers* Helpers::sInstance = nullptr;

Helpers::Helpers()
{
	glm::vec3 lVert[4] = {	glm::vec3(-1, -1, 0),
							glm::vec3( 1, -1, 0),
							glm::vec3( 1,  1, 0),
							glm::vec3(-1,  1, 0) };

	glm::vec2 lUv[4]   = {	glm::vec2(0,0),
							glm::vec2(1,0),
							glm::vec2(1,1),
							glm::vec2(0,1)};

	int		 lTri[6]  = {0, 1, 2, 0, 2, 3};



	mFullscreenQuad.setVertex(lVert, 4);
	mFullscreenQuad.setUV(lUv);
	mFullscreenQuad.setTriangles(lTri, 2);
	mFullscreenQuad.uploadToVRAM();
}

//----------------------------------

void Helpers::drawQuad()
{
	sInstance->mFullscreenQuad.draw();
}