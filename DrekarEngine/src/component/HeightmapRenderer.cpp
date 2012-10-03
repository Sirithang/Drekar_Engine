#include "component/HeightmapRenderer.h"
#include "core/GameObject.h"
#include "core/Debug.h"

#include "jsmn/jsmn.h"

using namespace de;
using namespace de::data;
using namespace de::component;

COMPONENT_DEF_TYPE(HeightmapRenderer);


void HeightmapRenderer::setup()
{
	mMaterial->setup();
}

//------------------------------

void HeightmapRenderer::render()
{
	mMaterial->program()->setMatrix("MATRIX_M", mOwner->transform()->matrix());

	mMesh->draw();
}

//------------------------------

void HeightmapRenderer::fromJSON(const std::string& pData)
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
		if(tokens[i].type == JSMN_STRING)
		{
			std::string name = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);

			if(name == "info" && tokens[i+1].type == JSMN_OBJECT)
			{
				i++;
				std::string data = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);
				mInfo.fromJSON(data);

				buildFromInfo();

				i+= tokens[i+1].size -1;
			}
			else if(name == "material")
			{
				i++;
				std::string data = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);

				mMaterial = AssetDatabase::load<Material>(data);
			}
		}

		i++;
	}
}

//-------------------------------------------------------

uint32_t HeightmapRenderer::getKey() const
{
	uint32_t key = 0;

	key |= (uint32_t)mMaterial->getID();

	return key;
}

//--------------------------------------------------------

void HeightmapRenderer::buildFromInfo()
{
	if(mInfo.width == 0 || mInfo.height == 0 || mInfo.heightInfo == nullptr)
	{
		Debug::Log("Heightmap info unrocognized (height, width = 0 or heightInfo empty");
		return;
	}

	int size = mInfo.hmWidth * mInfo.hmHeight;

	float wStep = mInfo.width / mInfo.hmWidth;
	float dStep = mInfo.depth / mInfo.hmHeight;

	glm::vec3* pts		= new glm::vec3[size];
	glm::vec3* normal	= new glm::vec3[size];

	for(int i = 0; i < mInfo.hmWidth ; i++)
	{
		for(int j = 0; j < mInfo.hmHeight; j++)
		{
			pts[i*mInfo.hmHeight + j] = glm::vec3(i * wStep, mInfo.heightInfo[i*mInfo.hmHeight + j] * mInfo.height, j * dStep);
		}
	}

	//----------------------------------------

	for(int i = 0; i < mInfo.hmWidth ; i++)
	{
		for(int j = 0; j < mInfo.hmHeight; j++)
		{
			glm::vec3 ptsMinusX;
			glm::vec3 ptsMinusY;
			glm::vec3 ptsMaxiX;
			glm::vec3 ptsMaxiY;

			//------ x -------

			if(i > 0)
			{
				ptsMinusX = pts[(i-1)*mInfo.hmHeight + j];
			}
			else
			{
				ptsMinusX = pts[i*mInfo.hmHeight + j];
			}

			if(i == mInfo.hmWidth-1)
			{
				ptsMaxiX = pts[i*mInfo.hmHeight + j];
			}
			else
			{
				ptsMaxiX = pts[(i+1)*mInfo.hmHeight + j];
			}

			//------- y -------

			if(j > 0)
			{
				ptsMinusY = pts[i*mInfo.hmHeight + (j-1)];
			}
			else
			{
				ptsMinusY = pts[i*mInfo.hmHeight + j];
			}

			if(j == mInfo.hmHeight-1)
			{
				ptsMaxiY = pts[i*mInfo.hmHeight + j];
			}
			else
			{
				ptsMaxiY = pts[i*mInfo.hmHeight + (j+1)];
			}

			//----- normal computation

			glm::vec3 vec1 = ptsMaxiX - ptsMinusX;
			glm::vec3 vec2 = ptsMaxiY - ptsMinusY;

			normal[i*mInfo.hmHeight + j] = glm::normalize(glm::cross(vec2, vec1));
		}
	}

	mMesh = new Mesh();
	mMesh->setVertex(pts,size);
	mMesh->setNormal(normal);

	delete[] pts;
	delete[] normal;

	//---------------------- Face num -------

	int nbSize = (mInfo.hmWidth - 1) * (2 * (mInfo.hmHeight-1)) * 3;

	int* faces = new int[nbSize];

	int k = 0;
	for(int i = 0; i < mInfo.hmWidth - 1 ; i++)
	{
		for(int j = 0; j < mInfo.hmHeight - 1; j++)
		{
			int idx = i*mInfo.hmHeight + j;

			faces[(k*6)]	= idx;
			faces[(k*6)+1]	= idx+1;
			faces[(k*6)+2]	= idx+1 + mInfo.hmHeight;

			faces[(k*6)+3]	= idx;
			faces[(k*6)+4]	= idx+1 + mInfo.hmHeight;
			faces[(k*6)+5]	= idx	+ mInfo.hmHeight;

			k++;
		}
	}
	
	mMesh->setTriangles(faces, nbSize / 3);
	mMesh->uploadToVRAM();
}