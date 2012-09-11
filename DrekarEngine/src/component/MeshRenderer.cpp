#include "component/MeshRenderer.h"
#include "core/Gameobject.h"
#include "component/Camera.h"

#include "renderer/Renderer.h"

using namespace de::component;

void MeshRenderer::init()
{
	de::renderer::Renderer::current()->addRenderable(this);
}

//----------------------------

void MeshRenderer::render()
{
	mMaterial->setup();

	mMaterial->program()->setMatrix("MATRIX_P",	Camera::current()->projectionMatrix());
	mMaterial->program()->setMatrix("MATRIX_V",	Camera::current()->viewMatrix());
	mMaterial->program()->setMatrix("MATRIX_M", mOwner->transform()->matrix());

	mMesh.draw();
}

//-------------------------

void MeshRenderer::setMaterial(de::Material* pMaterial)
{
	mMaterial = pMaterial;
}

//-----------------------

void MeshRenderer::setMesh(de::data::Mesh& pMesh)
{
	mMesh = pMesh;
}