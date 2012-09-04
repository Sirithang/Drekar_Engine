#include <core/Engine.h>
#include <data/Shader.h>

#include "MyScreen.h"

#include <iostream>

#include <windows.h>

int main(int argc, char** argv)
{
	HGLRC context = wglGetCurrentContext();

	de::Engine::initialize();

	de::Engine::pushScreen(new MyScreen());

	de::Engine::loop();


	return 0;
}