#include "data/Texture2D.h"

#include <gli/gli.hpp>
#include <gli/gtx/loader.hpp>

using namespace de::data;

void Texture2D::fromFile(const std::string& pPath)
{
	gli::texture2D texture = gli::load(pPath);

	create(texture[0].dimensions().x, texture[0].dimensions().y);

	GLuint format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	if(texture.format() == gli::format::DXT5)
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;

	for(gli::texture2D::level_type Level = 0; Level < texture.levels(); ++Level) 
	{ 
		glCompressedTexImage2D( 
			GL_TEXTURE_2D, 
			GLint(Level), 
			format, 
			GLsizei(texture[Level].dimensions().x), 
			GLsizei(texture[Level].dimensions().y), 
			0, 
			GLsizei(texture[Level].capacity()), 
			texture[Level].data()); 
	} 

}