#include "data/Texture.h"

using namespace de::data;

Texture::Texture()
{
	mID = -1;
}

//------------------------------

Texture::~Texture()
{
	glDeleteTextures(1, &mID);
}

//------------------------------

void Texture::create(unsigned int pWidth, unsigned int pHeight)
{
	if(mID == -1)
	{
		glGenTextures(1, &mID);
	}
	
	glBindTexture(GL_TEXTURE_2D, mID);

	mWidth = pWidth;
	mHeight = pHeight;
}

//-----------------------------

void Texture::init(GLint pInternalFormat, GLint pFormat, GLint pDataFormat)
{
	glBindTexture(GL_TEXTURE_2D, mID);
	glTexImage2D(GL_TEXTURE_2D, 0, pInternalFormat, mWidth, mHeight, 0, pFormat, pDataFormat, 0);

	//--- by default we set nearest filtering, to accomodate easily with RT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

//------------------------------

void Texture::setParameter(GLuint pParameter, GLuint pValue)
{
	glTexParameteri(GL_TEXTURE_2D, pParameter, pValue);
}

//------------------------------

unsigned int Texture::width() const
{
	return mWidth;
}

//-----------------------------

unsigned int Texture::height() const
{
	return mHeight;
}

//-----------------------------

GLuint Texture::ID() const
{
	return mID;
}

///----------------------------

void Texture::bind(int pTextureUnit) const
{
	glActiveTexture(GL_TEXTURE0+pTextureUnit);
	glBindTexture(GL_TEXTURE_2D, mID);
}