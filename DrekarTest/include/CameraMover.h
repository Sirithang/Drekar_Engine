#ifndef CAMERAMOVER_H
#define CAMERAMOVER_H

#include "core/AComponent.h"
#include "core/InputManager.h"

#include <glm/glm.hpp>

class CameraMover : public de::AComponent
{
protected:
	de::io::AInput* mKeyboard;
	de::io::AInput* mMouse;

	glm::vec2		mLastMousePos;

public:
	void init();
	void update();
};

#endif