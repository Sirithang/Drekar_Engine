#include "data/Shader.h"
#include "core/Debug.h"

#include <string>
#include <fstream>
#include <streambuf>

using namespace de::data;


Shader::Shader()
{
	mIsLoaded = false;
	mType = -1;
	mErrorLog = "";
	mShaderID = -1;
}

Shader::Shader(Shader::ShaderType pType)
{
	init(pType);
}

//----------------------------------------

Shader::~Shader()
{
	glDeleteShader(mShaderID);
}

//--------------------------------------

void Shader::init(Shader::ShaderType pType)
{
	mIsLoaded = false;
	mErrorLog = "";

	mShaderID = glCreateShader((GLenum) pType);
	mType = pType;
}

//---------------------------------------

bool Shader::isLoaded() const
{
	return mIsLoaded;
}

GLuint Shader::getID() const
{
	return mShaderID;
}

//-----------------------------------------

bool Shader::loadShader(std::string pCode)
{
	const char *c_str = pCode.c_str();
	glShaderSource(mShaderID, 1, &c_str, NULL);
	glCompileShader(mShaderID);

	int lCompilationStatus;
	glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &lCompilationStatus);

	if(lCompilationStatus == GL_FALSE)
	{
		mErrorLog = getShaderLog();
		return false;
	}

	mIsLoaded = true;

	return true;
}

//----------------------------------------

bool Shader::loadShaderFromFile(std::string pPath)
{
	std::ifstream t(pPath, std::ios::in);

	if(!t.is_open())
	{
		Debug::Log("Cannot open file");
	}

	std::string str;

	t.seekg(0, std::ios::end);   
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());

	return loadShader(str);
}


//******************************************************

std::string Shader::getShaderLog()
{
    int infologLength = 0;

    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(mShaderID, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(mShaderID, infologLength, &charsWritten, infoLog);

        std::string log = infoLog;

		Debug::Log(log);

        free(infoLog);

        return log;
    }

    return "<Blank Log>";
}
