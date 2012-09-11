#ifndef DE_PROGRAM_H
#define DE_PROGRAM_H

#include "export.h"
#include "data/Shader.h"

#include <glm/glm.hpp>
#include <map>

namespace de
{
	class DE_EXPORT Program
	{
	protected:
		int			mID;
		bool		mLinked;

		std::map<std::string, int>	mUniforms;

	public:
		Program();
		~Program();

		bool addShader(const data::Shader& pShader);
		bool compile();

		/**
		* \brief this immediatly set matrix uniform. NOTE :this DO NOT use the program, use() must be called BEFORE
		*/
		void setMatrix(const std::string& pName,const glm::mat4& pMatrix);


		void setVector4(const std::string& pName, const glm::vec4& pVec);

		void setFloat(const std::string& pName, const float pValue);

		void setInt(const std::string pName, const int pValue);

		void use();
	};
}

#endif