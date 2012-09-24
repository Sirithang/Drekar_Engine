#include "component/MeshRenderer.h"
#include "core/Gameobject.h"
#include "core/Debug.h"
#include "component/Camera.h"

#include "renderer/Renderer.h"

#include "jsmn/jsmn.h"

using namespace de::component;

COMPONENT_DEF_TYPE(MeshRenderer);

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

	mMesh->draw();
}

//-------------------------

void MeshRenderer::setMaterial(de::Material* pMaterial)
{
	mMaterial = pMaterial;
}

//-----------------------

void MeshRenderer::setMesh(de::data::Mesh* pMesh)
{
	mMesh = pMesh;
}

//----------------------

void MeshRenderer::fromJSON(const std::string& pData)
{
	jsmn_parser parser;
	jsmn_init(&parser);

	jsmntok_t tokens[256];
	jsmnerr_t r = jsmn_parse(&parser, pData.c_str(), tokens, 256);

	if(r != JSMN_SUCCESS )
	{
		Debug::Log(std::string("Erreur parson JSON for meshRender : ")+pData+" \n");
		return;
	}

	int i = 1; 
	while(tokens[i].start != -1)
	{
		if(tokens[i].type == JSMN_STRING && tokens[i+1].type == JSMN_STRING)
		{
			std::string type = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);
			i++;
			std::string data = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);
			i++;

			if(type == "mesh")
			{
				mMesh = AssetDatabase<data::Mesh>::load(data);
			}
			else if(type == "material")
			{
				mMaterial = AssetDatabase<Material>::load(data);
			}
		}
	}
}