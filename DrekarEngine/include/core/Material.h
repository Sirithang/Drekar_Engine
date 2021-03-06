#ifndef DE_MATERIAL_H
#define DE_MATERIAL_H

#include "core/Program.h"
#include "core/AssetDatabase.h"
#include "data/Texture.h"

#include <list>
#include <cstdint>

namespace de
{
	
	namespace argv
	{
		class AShaderArg;
	}

	class DE_EXPORT Material : public ILoadableAsset
	{
	protected:

		static std::list<int16_t>	sFreeIDs;
		static int16_t				sIDCounter;

		static std::map<int16_t, Material*> sMaterials;

		std::list<int>	mFreeUnit; // count free texture unit
		
		Program* mProgram;
		
		int16_t mID;

		std::map<std::string, argv::AShaderArg*> mArguments; // list of all user defined argument to pass to shader

		std::list<data::Texture*> mTexture;

	public:

		Material();
		~Material();
		
		void setProgram(Program* pProgram);

		/**
		*	\brief Add or set a texture to this mat. if pInstantUpload == true, it upload to the program the texture immediatly
		*/
		void addTexture(const std::string& pName, data::Texture* pTexture, bool pInstantUpload = false); 

		Program* program() const;

		/**
		* \brief this setup the material (bind program, push texture to it etc...)
				 If pForCurrentCam == true (default), it will bind current cam matrix to it too.
		*/
		void setup(bool pForCurrentCam = true);

		void fromFile(const std::string& pFile);

		int16_t getID();


		static Material* getMaterialFromID(uint16_t pID);
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
			data::Texture*	mTexture;
			int				mData;

		public:
			TextureArg(const std::string& pName, int pTextureUnit, data::Texture* pTexture);
			void upload(Program* pProgram);

			void changeTexture(de::data::Texture* pTex);
		};

		//----------------------------------------------
	}
}

#endif