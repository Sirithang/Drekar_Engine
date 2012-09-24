#include "io/AInput.h"

using namespace de::io;

AInput::AInput(const std::string& pName, const std::string& pType)
{
	mType = pType;
	mName = pName;
}

float AInput::getAxis(const std::string& pName) const
{
	std::map<std::string, float>::const_iterator it = mAxis.find(pName);
	if(it != mAxis.end())
	{
		return it->second;
	}

	return 0;
}