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

	pressed = false;
	lOrien = 0;

	InputManager::addInputSource(new io::KeyboardInput("Keyboard"));
	InputManager::addInputSource(new io::MouseInput("Mouse"));

	renderer::Renderer::current()->setAmbient(glm::vec3(0.1, 0.1, 0.1));
	//renderer::Renderer::current()->setAmbient(glm::vec3(1, 1, 1));

	//--------------------- Create field of object

	/*for(int i = 0; i <= 10; i++)
	{
		for(int j = 0; j <= 10; j++)
		{
			GameObject* obj = new GameObject();

			obj->fromAsset("data/assets/alien/alien.asset");

			obj->transform()->setPosition(glm::vec3(i*15, 5, j*15));
			//obj->transform()->setScale(glm::vec3(0.01f,0.01f,0.01f));
		}
	}*/

	//--------------------- Camera

	Camera* cam = (Camera*)lCam.addComponent(new Camera());
	cam->setClipPlane(glm::vec2(0.1f, 1000.0f));
	//cam->setOrtho(true);
	//cam->setOrthoHalfSize(100);

	lCam.transform()->setPosition(glm::vec3(50, 50, 50));
	lCam.transform()->setRotation(glm::quat(glm::vec3(glm::radians(45.0f), 0, 0)));

	lCam.addComponent(new CameraMover());

	//--------------------- ADD A LIGHTS
	
	de::GameObject* lLight;// = new de::GameObject();

	const int range = 200;

	de::GameObject* parentObj = new de::GameObject("ParentGameObject");
	parentObj->transform()->setPosition(glm::vec3(100, 0, 100));
	lLightObjs.push_back(parentObj);

	for(int i = 0; i < 0; i++)
	{
		lLight = new de::GameObject();

		lLight->transform()->setParent(parentObj->transform());

		de::component::PointLight* lpts = (de::component::PointLight*)lLight->addComponent(new de::component::PointLight());
		lLight->transform()->setLocalPosition(glm::vec3(rand()%range - range/2,  rand()%10  ,rand()%range - range/2));
		lpts->setColor(glm::vec3(1,1,1));
		
		lpts->setIntensity((rand()%50) * 0.01f);
	}

	mLight = new de::GameObject();
	Light* compLight = (Light*)mLight->addComponent(new de::component::DirectionalLight());
	compLight->setColor(glm::vec3(1.0f,1.0f,1.0f));

	lOrien = -45.0f;
	//mLight->transform()->setRotation(glm::quat(glm::vec3(45.0f, 0.0f, 0.0f)));
	

	GameObject* terrainObj = new GameObject("terrain");
	terrainObj->transform()->setPosition(glm::vec3(100, 0, 100));
	terrainObj->fromAsset("data/assets/village/village.asset");

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

	if(input->getAxis("R") > 0.1f)
	{
		lOrien += 20.0f * de::GameTime::deltaTime();
	}

	if(input->getAxis("F1") > 0.2f && !pressed)
	{
		AssetDatabase::reload<Material>("data/internals/lights/point/PointLight.mat");
		pressed = true;
	}
	else
		pressed = false;

	mLight->transform()->setRotation(glm::quat(glm::vec3(glm::radians(lOrien), 0, 0)));

	std::list<de::GameObject*>::iterator lIt = lLightObjs.begin();

	while(lIt != lLightObjs.end())
	{
		(*lIt)->transform()->setRotation(glm::quat(glm::vec3(0, -lAngle, 0)));
		lIt++;
	}

}