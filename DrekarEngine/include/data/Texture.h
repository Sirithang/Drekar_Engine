#ifndef DE_TEXTURE_H
#define DE_TEXTURE_H

#include "export.h"
#include "core/CountedObject.h"
#include <gl/glew.h>

namespace de
{
	namespace data
	{
		/**
		* \brief base class for texture (Image or renderbuffer)
		*/
		class DE_EXPORT Texture
		{
		protected:
			GLuint mID;

			unsigned int mWidth;
			unsigned int mHeight;

		public:
			Texture();
			~Texture();

			virtual void create(unsigned int pWidth,unsigned int pHeight);

			/**
			* \brief initialize the texture to an undefined texture of the formats given. Usefull for RenderTarget purpose!
			*/
			void init(GLint pInternalFormat, GLint pFormat, GLint pDataFormat);

			unsigned int width() const;
			unsigned int height() const;
			GLuint		 ID() const;

			void bind(int pTextureUnit) const;

			void setParameter(GLuint pParameter, GLuint pValue);
		};
	}
}

#endif