#include "io/MouseInput.h"

#include <gl/glfw.h>

using namespace de::io;

MouseInput::MouseInput(const std::string& pName)
	: AInput(pName, "MouseInput")
{
	mAxis["mouseX"]			= 0;
	mAxis["mouseY"]			= 0;
	mAxis["leftButton"]		= 0;
	mAxis["rightButton"]	= 0;
	mAxis["middleButton"]	= 0;

	//--- init

	int x,y;
	glfwGetMousePos(&x,&y);

	mAxis["mouseX"] = x;
	mAxis["mouseY"] = y;

	mAxis["leftButton"] = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS? 1.0f : 0.0f;
	mAxis["rightButton"] = glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS? 1.0f : 0.0f;
	mAxis["middleButton"] = glfwGetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS? 1.0f : 0.0f;
}

//-----------------------------------------------------

void MouseInput::update()
{
	int x,y;
	glfwGetMousePos(&x,&y);

	mAxis["mouseX"] = x;
	mAxis["mouseY"] = y;

	mAxis["leftButton"] = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS? 1.0f : 0.0f;
	mAxis["rightButton"] = glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS? 1.0f : 0.0f;
	mAxis["middleButton"] = glfwGetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS? 1.0f : 0.0f;
}