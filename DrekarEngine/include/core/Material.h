#ifndef DE_MATERIAL_H
#define DE_MATERIAL_H

#include "core/Program.h"
#include "data/Texture.h"

#include <list>

namespace de
{
	
	namespace argv
	{
		class AShaderArg;
	}

	class DE_EXPORT Material
	{
	protected:
		std::list<int>	mFreeUnit; // count free texture unit
		
		Program mProgram;

		std::map<std::string, argv::AShaderArg*> mArguments; // list of all user defined argument to pass to shader

		std::list<data::Texture> mTexture;

	public:
		
		void setProgram(Program pProgram);
		void addTexture(const std::string& pName, const data::Texture& pTexture); 

		Program program() const;

		/**
		* \brief this setup the material (bind program, push texture to it etc...
		*/
		void setup();


	};


	namespace argv
	{
		//--------Shader argument class (allow unified binding)

		class AShaderArg
		{
		protected:
			std::string mName;
		public:
			AShaderArg(const std::string& pName);
			virtual void upload(Program* pProgram) = 0;
		};

		//******

		class Vec4Arg : public AShaderArg
		{
		protected:
			glm::vec4 mData;

		public:
			Vec4Arg(const std::string& pName, glm::vec4 pData);
			void upload(Program* pProgram);
		};

		//******

		class MatrixArg : public AShaderArg
		{
		protected:
			glm::mat4 mData;

		public:
			MatrixArg(const std::string& pName, const glm::mat4& pData);
			void upload(Program* pProgram);
		};

		//*********

		class TextureArg : public AShaderArg
		{
		protected:
			data::Texture	mTexture;
			int				mData;

		public:
			TextureArg(const std::string& pName, int pTextureUnit, const data::Texture& pTexture);
			void upload(Program* pProgram);
		};

		//----------------------------------------------
	}
}

#endif