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
		class DE_EXPORT Texture : CountedObject<Texture>
		{
		protected:
			GLuint mID;

			unsigned int mWidth;
			unsigned int mHeight;

		public:
			Texture();

			virtual void create(unsigned int pWidth,unsigned int pHeight, GLint pInternalFormat, GLint pFormat, GLint pDataFormat);
		
			void release();

			unsigned int width() const;
			unsigned int height() const;
			GLuint		 ID() const;

			void bind(int pTextureUnit) const;
		};
	}
}

#endif