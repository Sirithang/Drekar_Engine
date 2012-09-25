#include "MyScreen.h"
#include "CameraMover.h"

#include "component/MeshRenderer.h"
#include "core/Material.h"
#include "core/GameTime.h"
#include "data/Texture2D.h"
#include "core/InputManager.h"
#include "io/KeyboardInput.h"
#include "io/MouseInput.h"

#include <time.h>

#include <gl/glew.h>

using namespace de;
using namespace de::data;
using namespace de::component;

void MyScreen::init()
{
	srand(time(NULL));

	InputManager::addInputSource(new io::KeyboardInput("Keyboard"));
	InputManager::addInputSource(new io::MouseInput("Mouse"));

	//--------------------- Create field of object

	for(int i = -2; i <= 2; i++)
	{
		for(int j = -2; j <= 2; j++)
		{
			GameObject* obj = new GameObject();

			obj->fromAsset("data/assets/head.asset");

			obj->transform()->setPosition(glm::vec3(i*15, 0, j*15));
		}
	}

	//--------------------- Camera

	Camera* cam = (Camera*)lCam.addComponent(new Camera());
	lCam.transform()->setPosition(glm::vec3(0, 80, -70));
	lCam.transform()->setRotation(glm::quat(glm::vec3(45, 0, 0)));

	lCam.addComponent(new CameraMover());

	//--------------------- ADD A LIGHTS
	
	de::GameObject* lLight = new de::GameObject();

	for(int i = 0; i < 1; i++)
	{
		de::GameObject* parentObj = new de::GameObject("ParentGameObject");
		lLight = new de::GameObject();

		lLightObjs.push_back(parentObj);
		lLight->transform()->setParent(parentObj->transform());

		de::component::PointLight* lpts = (de::component::PointLight*)lLight->addComponent(new de::component::PointLight());
		lLight->transform()->setLocalPosition(glm::vec3(rand()%50 - 25,rand()%50 - 25,rand()%50 - 25));
		lpts->setColor(glm::vec3(1.0f,1.0f,1.0f));
	}

	lLight = new de::GameObject();
	lLight->addComponent(new de::component::DirectionalLight());
	lLight->transform()->setRotation(glm::quat(glm::vec3(glm::radians(90.0f), 0, 0)));

	lAngle = 0;
}

void MyScreen::draw()
{

}

//--------------------------

void MyScreen::update()
{

	io::AInput* input = InputManager::getInputFromName("Keyboard");

	if(input->getAxis(" ") > 0.1f)
	{
		lAngle += 0.6f * de::GameTime::deltaTime();
	}

	std::list<de::GameObject*>::iterator lIt = lLightObjs.begin();

	while(lIt != lLightObjs.end())
	{
		(*lIt)->transform()->setRotation(glm::quat(glm::vec3(0, -lAngle, 0)));
		lIt++;
	}

}