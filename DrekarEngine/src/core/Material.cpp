#include "core/Material.h"
#include "data/texture2D.h"
#include "core/Debug.h"
#include "component/Camera.h"

#include "jsmn/jsmn.h"

#include <fstream>

using namespace de;

std::list<int16_t>	Material::sFreeIDs;
int16_t				Material::sIDCounter = 0;

std::map<int16_t, Material*> Material::sMaterials;


Material::Material()
{
	mProgram = nullptr;

	if(sFreeIDs.size() > 0)
	{
		mID = sFreeIDs.front();
		sFreeIDs.pop_front();
	}
	else
	{
		sIDCounter++;
		mID = sIDCounter;
	}

	sMaterials[mID] = this;
}

Material::~Material()
{
	sFreeIDs.push_back(mID);
}

//------------------------------------

Program* Material::program() const
{
	return mProgram;
}

//-------------------------------

void Material::setup(bool pForCurrentCam)
{
	mProgram->use();

	std::map<std::string, argv::AShaderArg*>::iterator lIt = mArguments.begin();
	while(lIt != mArguments.end())
	{
		(*lIt).second->upload(mProgram);
		lIt++;
	}

	if(pForCurrentCam)
	{
		mProgram->setMatrix("MATRIX_P",	component::Camera::current()->projectionMatrix());
		mProgram->setMatrix("MATRIX_V",	component::Camera::current()->viewMatrix());
	}
}

//---------------------

void Material::setProgram(Program* pProgram)
{
	mProgram = pProgram;

	mFreeUnit.clear();
	for(int i = 0; i < 8;i++)
	{
		mFreeUnit.push_back(i);
	}
}

//---------------------

int16_t Material::getID()
{
	return mID;
}

//---------------------

void Material::addTexture(const std::string& pName, data::Texture* pTexture, bool pInstantUpload)
{

	if(mArguments.count(pName) == 0)
	{
		//mTexture.push_back(pTexture);

		int id = mFreeUnit.front();
		mFreeUnit.pop_front();

		mArguments[pName] = new argv::TextureArg(pName, id, pTexture);
	}
	else
	{
		((argv::TextureArg*)mArguments[pName])->changeTexture(pTexture);
	}

	if(pInstantUpload)
		mArguments[pName]->upload(mProgram);
}

//----------------------

void Material::fromFile(const std::string& pFile)
{
	std::ifstream file;

	file.open(pFile, std::ios::in);

	if(!file.is_open())
	{
		Debug::Log("Can't open file : "+pFile);
		return;
	}

	std::string str;

	file.seekg(0, std::ios::end);   
	str.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());

	file.close();

	jsmn_parser parser;
	jsmn_init(&parser);

	jsmntok_t tokens[256];
	jsmnerr_t r = jsmn_parse(&parser, str.c_str(), tokens, 256);

	if(r != JSMN_SUCCESS )
	{
		Debug::Log("Erreur parson JSON\n");
		return;
	}

	//------ JSON loaded, pasing

	data::Shader* shader[3];
	int current = 0;
	memset(shader, 0, 3 * sizeof(data::Shader*));

	if(mProgram != nullptr)
	{
		delete mProgram;
		mProgram = nullptr;
	}
	
	int i = 0;
	while(tokens[i].start != -1)
	{
		if(tokens[i].type == JSMN_OBJECT || tokens[i].type == JSMN_ARRAY)
		{
			i++;
		}
		else
		{
			if(tokens[i].type == JSMN_STRING)
			{
				std::string name(str, tokens[i].start, tokens[i].end - tokens[i].start);

				if(name == "vertex" || name == "fragment")
				{//load vertex shader
					i++;

					if(tokens[i].type == JSMN_STRING)
					{//if next is not a strong we ignore, bad material
						std::string file(str, tokens[i].start, tokens[i].end - tokens[i].start);

						if(mProgram == nullptr) setProgram(new Program());

						if(name == "vertex")
							shader[current] = new data::Shader(data::Shader::VERTEX);
						else
							shader[current] = new data::Shader(data::Shader::PIXEL);
						shader[current]->loadShaderFromFile(file);

						mProgram->addShader(*shader[current]);

						current++;
					}
				}
				else if(name == "textures")
				{//texture defining
					i++;

					if(tokens[i].type == JSMN_ARRAY)
					{//if not an array we skip
						int size = tokens[i].size;
						
						for(int j = 0; j < size; j++)
						{//for each entry retrieve name + file
							i++;
							if(tokens[i].type != JSMN_OBJECT)//if it's not an object, not good
								continue;
							i++;
							if(tokens[i].type != JSMN_STRING)
								continue;
							std::string name(str, tokens[i].start, tokens[i].end - tokens[i].start);
							i++;
							if(tokens[i].type != JSMN_STRING)
								continue;
							std::string file(str, tokens[i].start, tokens[i].end - tokens[i].start);

							data::Texture2D* tex = new data::Texture2D();
							tex->fromFile(file);
							addTexture(name, tex);
						}
					}
				}

				i++;
			}
		}
	}

	for(int i = 0; i < 3; i++)
		if(shader[i] != nullptr) delete shader[i];

	if(mProgram != nullptr) mProgram->compile();
}

//----------------------------

Material* Material::getMaterialFromID(uint16_t pID)
{
	if(sMaterials.count(pID) == 0)
		return nullptr;

	return sMaterials[pID];
}



//*******************************************************************************

argv::AShaderArg::AShaderArg(const std::string& pName)
{
	mName = pName;
}

//------------------------------

argv::Vec4Arg::Vec4Arg(const std::string& pName, glm::vec4 pArgv)
	:AShaderArg(pName)
{
	mData = pArgv;
}

void argv::Vec4Arg::upload(Program* pProgram)
{
	pProgram->setVector4(mName, mData);
}

//----------------------------

argv::MatrixArg::MatrixArg(const std::string& pName, const glm::mat4& pData)
	:AShaderArg(pName)
{
	mData = pData;
}

void argv::MatrixArg::upload(Program* pProgram)
{
	pProgram->setMatrix(mName, mData);
}

//---------------------------------

argv::TextureArg::TextureArg(const std::string& pName, int pTextureUnit, data::Texture* pTexture)
	:AShaderArg(pName)
{
	mData = pTextureUnit;
	mTexture = pTexture;
}

void argv::TextureArg::upload(Program* pProgram)
{
	mTexture->bind(mData);
	pProgram->setInt(mName, mData);
}

void argv::TextureArg::changeTexture(de::data::Texture* pTex)
{
	mTexture = pTex;
}

//-------------------------------
