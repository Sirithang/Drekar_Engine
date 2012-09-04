#include "core/Material.h"

using namespace de;

Program Material::program() const
{
	return mProgram;
}

//-------------------------------

void Material::setup()
{
	mProgram.use();

	std::map<std::string, argv::AShaderArg*>::iterator lIt = mArguments.begin();
	while(lIt != mArguments.end())
	{
		(*lIt).second->upload(&mProgram);
		lIt++;
	}
}

//---------------------

void Material::setProgram(Program pProgram)
{
	mProgram = pProgram;

	mFreeUnit.clear();
	for(int i = 0; i < 8;i++)
	{
		mFreeUnit.push_back(i);
	}
}

//---------------------

void Material::addTexture(const std::string& pName, const data::Texture& pTexture)
{
	mTexture.push_back(pTexture);

	int id = mFreeUnit.front();
	mFreeUnit.pop_front();

	mArguments[pName] = new argv::TextureArg(pName, id, pTexture);
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

argv::TextureArg::TextureArg(const std::string& pName, int pTextureUnit, const data::Texture& pTexture)
	:AShaderArg(pName)
{
	mData = pTextureUnit;
	mTexture = pTexture;
}

void argv::TextureArg::upload(Program* pProgram)
{
	mTexture.bind(mData);
	pProgram->setInt(mName, mData);
}

//-------------------------------