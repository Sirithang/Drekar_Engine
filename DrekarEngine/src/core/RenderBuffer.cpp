#include "core/RenderBuffer.h"

using namespace de;

RenderBuffer::RenderBuffer()
{
	mWidth = 0;
	mHeight = 0;
}

//----------------------------

RenderBuffer::~RenderBuffer()
{
	glDeleteFramebuffers(1, &mID);
}

//----------------------------

void RenderBuffer::init(unsigned int pWidth, unsigned int pHeight)
{
	mWidth = pWidth;
	mHeight = pHeight;

	glGenFramebuffers(1, &mID);

	glBindFramebuffer(GL_FRAMEBUFFER, mID);

	//-------------- we create the default buffer + depth

	data::Texture* lBuffer = new de::data::Texture();
	lBuffer->create(pWidth, pHeight);
	lBuffer->init( GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);

	mTextures.push_back(lBuffer);

	//----------- depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pWidth, pHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	//-------- binding
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, lBuffer->ID(), 0);
 
	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	mCurrentAttachementMax = 0;
}

//---------------------------

void RenderBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, mID);
}

//-------------------------

void RenderBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//------------------------

const std::list<data::Texture*>& RenderBuffer::getTextures() const
{
	return mTextures;
}

//----------------------

void RenderBuffer::addTexture(data::Texture* pTexture)
{
	mTextures.push_back(pTexture);
	mCurrentAttachementMax += 1;

	glBindFramebuffer(GL_FRAMEBUFFER, mID);

	//-------- binding
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mCurrentAttachementMax, pTexture->ID(), 0);
 
	// Set the list of draw buffers.
	GLenum* DrawBuffers = new GLenum[mCurrentAttachementMax+1];
	for(int i = 0; i < mCurrentAttachementMax+1; i++)
	{
		DrawBuffers[i] = GL_COLOR_ATTACHMENT0+i;
	}
	glDrawBuffers(mCurrentAttachementMax+1, DrawBuffers); // "1" is the size of DrawBuffers


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}