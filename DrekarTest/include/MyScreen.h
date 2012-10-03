#ifndef MYSCREEN_H
#define MYSCREEN_H

#include "core/AScreen.h"

#include <core/Program.h>
#include <core/Gameobject.h>
#include <data/Mesh.h>
#include <data/Shader.h>
#include "component/Camera.h"

class MyScreen : public de::AScreen
{
protected:
	de::data::Shader lFirst;
	de::data::Shader lSecond;
	de::Program lProg;
	de::Material lMat;
	de::data::Mesh lMesh;

	de::GameObject lCam;

	std::list<de::GameObject*> lLightObjs;
	std::list<de::GameObject*> lObject;

	float	lAngle;
	bool	pressed;

public:
	void init();
	void draw();
	void update();
};

#endif