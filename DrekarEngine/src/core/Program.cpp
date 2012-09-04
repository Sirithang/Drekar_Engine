#include "core/Program.h"
#include "core/Debug.h"

#include <glm/gtc/type_ptr.hpp>

using namespace de;
using namespace de::data;

Program::Program()
{
	mID = glCreateProgram();
}

//--------------------

void Program::release()
{
	glDeleteProgram(mID);
}

//--------------------

bool Program::addShader(const Shader& pShader)
{
	if(!pShader.isLoaded()) return false;

	glAttachShader(mID, pShader.getID());

	return true;
}

//--------------------

bool Program::compile()
{
	glLinkProgram(mID);
	int iLinkStatus;
	glGetProgramiv(mID, GL_LINK_STATUS, &iLinkStatus);
	mLinked = iLinkStatus == GL_TRUE;

	if(mLinked)
	{
		//-----retrieve all uniform to build the uniform map location
		int total = -1;
		glGetProgramiv( mID, GL_ACTIVE_UNIFORMS, &total ); 

		for(int i=0; i<total; ++i)  
		{
			int name_len=-1, num=-1;

			GLenum type = GL_ZERO;

			char name[100];

			glGetActiveUniform( mID, GLuint(i), sizeof(name)-1,
				&name_len, &num, &type, name );
			name[name_len] = 0;
			GLuint location = glGetUniformLocation( mID, name );

			mUniforms[name] = location;
		}
	}
	else
	{
		Debug::Log("Linking of program failed");
	}

	return mLinked;
}

//------------------

void Program::use()
{
	if(mLinked) glUseProgram(mID);
}

//------------------

void Program::setMatrix(const std::string& pName, const glm::mat4& pMat)
{
	if(mUniforms.count(pName) == 0)
	{
		Debug::Log(pName + " : unknown matrix uniform tried to be set");
		return;
	}

	glUniformMatrix4fv(mUniforms[pName], 1, GL_FALSE, glm::value_ptr(pMat)); 
}

//------------------

void Program::setVector4(const std::string& pName, const glm::vec4& pVec)
{
	if(mUniforms.count(pName) == 0)
	{
		Debug::Log(pName + " : unknown vector uniform tried to be set");
		return;
	}

	glUniform4fv(mUniforms[pName], 1, glm::value_ptr(pVec)); 
}

//---------------------

void Program::setFloat(const std::string& pName, const float pValue)
{
	if(mUniforms.count(pName) == 0)
	{
		Debug::Log(pName + " : unknown float uniform tried to be set");
		return;
	}

	glUniform1f(mUniforms[pName], pValue);
}

//--------------------

void Program::setInt(const std::string pName, const int pValue)
{
	if(mUniforms.count(pName) == 0)
	{
		Debug::Log(pName + " : unknown float uniform tried to be set");
		return;
	}

	glUniform1i(mUniforms[pName], pValue);
}