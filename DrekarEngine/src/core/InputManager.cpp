#include "core/InputManager.h"
#include "core/Debug.h"
#include "io/AInput.h"

using namespace de;
using namespace de::io;

InputManager* InputManager::sInstance = nullptr;

void InputManager::init()
{
	sInstance = new InputManager();
}

//***********************************

void InputManager::update()
{
	std::map<std::string, io::AInput*>::iterator it = sInstance->mInputs.begin();

	while(it != sInstance->mInputs.end())
	{
		it->second->update();
		it++;
	}
}

//***********************************


io::AInput* InputManager::getInputFromType(const std::string& pType)
{
	std::map<std::string, io::AInput*>::iterator it = sInstance->mInputs.begin();

	while(it != sInstance->mInputs.end())
	{
		if(it->second->mType == pType)
		{
			return it->second;
		}
		it++;
	}

	return nullptr;
}

//***********************************

io::AInput* InputManager::getInputFromName(const std::string& pName)
{
	if(sInstance->mInputs.count(pName) > 0)
		return sInstance->mInputs[pName];

	return nullptr;
}

//***********************************

io::AInput* InputManager::addInputSource(io::AInput* pInput)
{
	if(sInstance->mInputs.count(pInput->mName) > 0)
	{
		Debug::Log(std::string("There is already an input called : ") + pInput->mName + ". This input wasn't added to the list.");
		return pInput;
	}

	sInstance->mInputs[pInput->mName] = pInput;
	return pInput;
}

//***********************************

void InputManager::removeInputSource(io::AInput* pInput)
{
	if(sInstance->mInputs.count(pInput->mName) > 0)
	{
		sInstance->mInputs.erase(pInput->mName);
	}
}