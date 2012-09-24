#include "core/Gameobject.h"
#include "core/ComponentFactory.h"
#include "core/Debug.h"

#include "jsmn/jsmn.h"

#include <fstream>

using namespace de;

std::list<GameObject*> GameObject::sGameObjects;

GameObject::GameObject(std::string pName)
{
	mName = pName;

	mTransform = new component::Transform();
	addComponent(mTransform);

	sGameObjects.push_back(this);
}

//-----------------------------------------


GameObject::~GameObject()
{
	std::list<AComponent*>::iterator lIt = mComponents.begin();
	while(lIt != mComponents.end())
	{
		delete (*lIt);
		lIt++;
	}

	mComponents.clear();

	sGameObjects.remove(this);
}

//----------------------

void GameObject::internalUpdate()
{
	std::list<AComponent*>::iterator lIt = mComponents.begin();
	while(lIt != mComponents.end())
	{
		(*lIt)->update();
		lIt++;
	}
}

//---------------------

void GameObject::internalDraw()
{
	std::list<AComponent*>::iterator lIt = mComponents.begin();
	while(lIt != mComponents.end())
	{
		(*lIt)->preDraw();
		lIt++;
	}
}

//--------------------

void GameObject::update()
{

}

//--------------------

void GameObject::draw()
{

}

//-------------------

AComponent* GameObject::addComponent(AComponent* pComponent)
{
	mComponents.push_back (pComponent);
	pComponent->mOwner = this;
	pComponent->init();

	return pComponent;
}

//------------------

void GameObject::fromAsset(const std::string pFile)
{
	std::ifstream file;

	file.open(pFile, std::ios::in);

	if(!file.is_open())
	{
		Debug::Log("Can't open file : "+pFile);
		return;
	}

	std::string str;

	file.seekg(0, std::ios::end);   
	str.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());

	file.close();

	jsmn_parser parser;
	jsmn_init(&parser);

	jsmntok_t tokens[256];
	jsmnerr_t r = jsmn_parse(&parser, str.c_str(), tokens, 256);

	if(r != JSMN_SUCCESS )
	{
		Debug::Log("Erreur parson JSON\n");
		return;
	}

	//------ JSON loaded, pasing

	int i = 0;
	while(tokens[i].start != -1)
	{
		if(tokens[i].type == JSMN_OBJECT)
		{
			i++;
		}
		else
		{
			if( tokens[i].type == JSMN_STRING && tokens[i+1].type == JSMN_OBJECT)
			{//we arrive at a new component
				std::string type(str, tokens[i].start, tokens[i].end - tokens[i].start);

				AComponent* component = ComponentFactory::createInstance(type);

				component->fromJSON(std::string(str, tokens[i+1].start, tokens[i+1].end - tokens[i+1].start));

				addComponent(component);

				i++;
				i += tokens[i].size;
			}
			else
				i++;
		}
	}
}