#ifndef DE_RENDERBUFFER_H
#define DE_RENDERBUFFER_H

#include "export.h"
#include "core/CountedObject.h"
#include "data/Texture.h"
#include <gl/glew.h>

#include <list>

namespace de
{
	class DE_EXPORT RenderBuffer
	{
	protected:
		unsigned int mWidth;
		unsigned int mHeight;

		GLuint		 mID;

		int			mCurrentAttachementMax;

		std::list<data::Texture*> mTextures;

	public:
		RenderBuffer();
		~RenderBuffer();

		/**
		* \brief if pCreateDefault is true, we create a default color attachement and a defaut depth renderbuffer
		*/
		void init(unsigned int pWidth, unsigned int pHeight, bool pCreateDefault = true);

		/**
		* \brief pAttachement is the OpenGL enum that definie the attachement.
		*/
		void addTexture(data::Texture* pTexture, GLint pAttachement = -1);

		void bind()		const;
		void unbind()	const;

		const std::list<data::Texture*>& getTextures() const;
	};
}

#endif