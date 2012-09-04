#include "data/Texture.h"

using namespace de::data;

Texture::Texture()
{
}

//------------------------------

void Texture::create(unsigned int pWidth, unsigned int pHeight, GLint pInternalFormat, GLint pFormat, GLint pDataFormat)
{
	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	mWidth = pWidth;
	mHeight = pHeight;

	glTexImage2D(GL_TEXTURE_2D, 0, pInternalFormat, pWidth, pHeight, 0, pFormat, pDataFormat, 0);

	//--- by default we set nearest filtering, to accomodate easily with RT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Texture::release()
{
	glDeleteTextures(1, &mID);
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