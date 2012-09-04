#include "core/Debug.h"

using namespace de;

Debug* Debug::sInstance = new Debug();


//-------------------------------------

Debug::Debug()
{
	
}

//--------------------------------------

void Debug::Log(std::string pInfo)
{
	std::cout<<pInfo<<std::endl;
}