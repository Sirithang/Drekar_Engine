#include "MyScreen.h"

#include "component/MeshRenderer.h"
#include "core/Material.h"
#include "core/GameTime.h"

#include <gl/glew.h>

void MyScreen::init()
{
	lFirst.init(de::data::Shader::VERTEX);
	lSecond.init(de::data::Shader::PIXEL);
	lFirst.loadShaderFromFile("data/vertex.vert");
	lSecond.loadShaderFromFile("data/fragment.frag");

	lProg.addShader(lFirst);
	lProg.addShader(lSecond);
	lProg.compile();
	//lProg.use();

	de::Material* lMat = new de::Material();
	lMat->setProgram(lProg);

	de::component::MeshRenderer* lrenderer = (de::component::MeshRenderer*)lObj.addComponent(new de::component::MeshRenderer());
	lrenderer->setMaterial(lMat);

	de::GameObject*			lCamObj = new de::GameObject();
	lCam = (de::component::Camera*)lCamObj->addComponent(new de::component::Camera());

	lMesh.loadFromFile("data/output.mesh");
	lMesh.uploadToVRAM();

	lrenderer->setMesh(lMesh);

	lObj.transform()->setPosition(glm::vec3(0, 0, 0));

	lCamObj->transform()->setPosition(glm::vec3(0, 5, -40));

	//--------------------- ADD A LIGHTS
	
	de::GameObject* lLight = new de::GameObject();
	/*de::component::DirectionalLight* lcomplight = (de::component::DirectionalLight*)lLight->addComponent(new de::component::DirectionalLight());
	lLight->transform()->setRotation(glm::quat(glm::vec3( -45 * 3.14f * 180.0f, -45 * 3.14f * 180.0f,0)));
	lLight->transform()->setRotation(glm::quat(glm::vec3(0, 45 * 3.14f * 180.0f, 0)));

	lcomplight->setColor(glm::vec3(0.8,0.5,0.4));*/

	//------------------ Second Mesh

	/*de::component::MeshRenderer*	lMeshRenderer	= (de::component::MeshRenderer*)lObj2.addComponent(new de::component::MeshRenderer());

	lObj2.transform()->setPosition(glm::vec3(-12, 0, 0));

	de::data::Mesh mesh;
	mesh.loadFromFile("data/mesh2.mesh");
	mesh.uploadToVRAM();

	lMeshRenderer->setMesh(mesh);
	lMeshRenderer->setMaterial(lMat);*/

	//-----------------
	//mRoot.addChild(lLight);


    lLight = new de::GameObject();
	de::component::PointLight* lpts = (de::component::PointLight*)lLight->addComponent(new de::component::PointLight());
	//lLight->transform()->setRotation(glm::quat(glm::vec3(0, -45 * 3.14f * 180.0f, 0)));
	lLight->transform()->setPosition(glm::vec3(0, 10,0));
	lpts->setColor(glm::vec3(0,0,1));

	//-------------------

	mRoot.addChild(&lObj);
	mRoot.addChild(lCamObj);
	mRoot.addChild(lLight);
	mRoot.addChild(&lObj2);

	lAngle = 0;
}

void MyScreen::draw()
{
	/*lProg.use();

	glm::mat4 lMV = glm::translate(glm::mat4(), glm::vec3(0,0,-4));
	lMV = glm::rotate(lMV, glm::radians(lAngle), glm::vec3(0,1,0));
	

	glm::mat4 lP = glm::perspective(60.0f, 4.0f/3.0f, 0.01f, 100.0f);

	lProg.setMatrix("projectionMatrix", lP);
	lProg.setMatrix("modelViewMatrix", lMV);

	lMesh.draw();*/
}

//--------------------------

void MyScreen::update()
{
	lAngle += 0.6f * de::GameTime::deltaTime();
	lObj.transform()->setRotation(glm::quat(glm::vec3(0, lAngle, 0)));
	lObj2.transform()->setRotation(glm::quat(glm::vec3(lAngle, 0,0)));
}