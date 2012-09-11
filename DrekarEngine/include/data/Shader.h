#ifndef DE_SHADER_H
#define DE_SHADER_H

#include "export.h"
#include "core/CountedObject.h"

#include <string>
#include <gl/glew.h>

namespace de
{

	/**
	\namespace data

	\brief the namespace of all data that lives in memory.
	*/
	namespace data
	{
		/**
		* \class Shader
		*
		* \brief Encapsulate a shader. Simply allow simple loading from file
		*
		*/
		class DE_EXPORT Shader
		{
		protected:
			GLuint		mShaderID;
			bool		mIsLoaded;
			int			mType;

			std::string mErrorLog;

		public:

			/**
			* \brief This simply redefine OpenGL shader type (avoid to include OpenGL stuff)
			*/
			enum ShaderType {	VERTEX	 = GL_VERTEX_SHADER,
								PIXEL	 = GL_FRAGMENT_SHADER,
								GEOMETRY = GL_GEOMETRY_SHADER };


			/**
			* \brief create an uninitialize shader. Init it with init(shadertype);
			*/
			Shader();

			/**
			* \brief Create an empty shader (need to be initialized with some code later)
			* \param[in] pType can be fed an OpenGL enum, as ShaderType is only a redefinition of those. 
			*/
			Shader(ShaderType pType);

			~Shader();


			void init(ShaderType pType);

			//---accessor/gettor

			bool	isLoaded() const;
			GLuint	getID() const;
			//----

			bool loadShader(std::string pCode);
			bool loadShaderFromFile(std::string pPath);

			std::string getShaderLog();
		};
	}
}

#endif