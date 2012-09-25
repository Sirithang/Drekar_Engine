#include <core/Engine.h>
#include <GL/glew.h>
#include <gl/glfw.h>

#include "data/Shader.h"
#include "data/Mesh.h"
#include "core/Program.h"
#include "core/GameTime.h"
#include "core/Helpers.h"
#include "core/InputManager.h"

#include <windows.h>

using namespace de;

Engine* Engine::sInstance = 0;

Engine::Engine(int pWidth, int pHeight, bool pFullscreen)
	:mWidth(pWidth), mHeight(pHeight), mFullscreen(pFullscreen)
{
	mRunning = true;

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwInit();
	glfwOpenWindow(mWidth, mHeight, 8, 8, 8, 8, 24, 8, GLFW_WINDOW);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	InputManager::init();

	//glEnable(GL_CULL_FACE);
}

//-------------------------------------

Engine::~Engine()
{
	glfwTerminate();
}

//-------------------------------------

void Engine::initialize(int pWidth, int pHeight, bool pFullscreen)
{
	sInstance = new Engine(pWidth, pHeight, pFullscreen);
	glewInit();
	GameTime::init();

	Helpers::sInstance = new Helpers();
}

//---------------------------------------

void Engine::loop()
{
	while(sInstance->mRunning)
	{
		GameTime::tick();

		InputManager::update();

		//------ init recently pushed screens
		std::list<AScreen*>::iterator lIt = sInstance->mInitScreens.begin();
		while(lIt != sInstance->mInitScreens.end())
		{
			(*lIt)->mRenderer.setup();
			(*lIt)->init();
			sInstance->mScreens.push_front(*lIt);
			lIt++;
		}
		sInstance->mInitScreens.clear();

		//------ delete screens popped
		lIt = sInstance->mDeleteScreens.begin();
		while(lIt != sInstance->mDeleteScreens.end())
		{
			delete (*lIt);
			lIt++;
		}
		sInstance->mDeleteScreens.clear();

		//------ update and render all screens
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::list<AScreen*> lScreen = sInstance->mScreens;
		lIt = lScreen.begin();
		while(lIt != lScreen.end())
		{
			(*lIt)->mRenderer.setup();

			(*lIt)->update();
			(*lIt)->internalUpdate();

			(*lIt)->draw();
			(*lIt)->internalDraw();

			(*lIt)->mRenderer.render();

			lIt++;
		}

		glfwSwapBuffers();

		sInstance->mRunning = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
	}
}

//------------------------------------------------

void Engine::pushScreen(AScreen* pScreen)
{
	if(pScreen == nullptr)
		return;

	sInstance->mInitScreens.push_front(pScreen);
}

//-----------------------------------------------

AScreen* Engine::popScreen()
{
	if(sInstance->mScreens.size() == 0)
		return nullptr;

	AScreen* lScreen = sInstance->mScreens.front();
	sInstance->mScreens.pop_front();
	sInstance->mDeleteScreens.push_front(lScreen);

	return lScreen;
}

//----------------------------------------------

int Engine::width()
{
	return sInstance->mWidth;
}

int Engine::height()
{
	return sInstance->mHeight;
}