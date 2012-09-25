#ifndef CAMERAMOVER_H
#define CAMERAMOVER_H

#include "core/AComponent.h"
#include "core/InputManager.h"

class CameraMover : public de::AComponent
{
protected:
	de::io::AInput* mInput;

public:
	void init();
	void update();
};

#endif