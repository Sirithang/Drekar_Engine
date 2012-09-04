#ifndef DE_INTERNALDATA_H
#define DE_INTERNALDATA_H

/*-----------------------------------------
	This file contains "embedded" data with
	the engine(like G-Buffer shader)
*----------------------------------------*/

const char* gClearMRTVert =	"#version 330\n"
							"layout (location = 0) in vec3 inPosition;\n"
							"void main()\n"
							"{\n"
							"gl_Position = vec4(inPosition, 1.0);\n"
							"}\n";

const char* gCleanMRTFrag =	"#version 330\n"
							"layout(location = 0) out vec4 outputColor;\n"
							"layout(location = 1) out vec4 outputNormal;\n"
							"layout(location = 2) out vec4 outputDepth;\n"
							"void main()\n" 
							"{\n"
							"outputColor = vec4(0,0,0,0);\n"
							"outputNormal = vec4(0.5, 0.5, 0.5, 0.0);\n"
							"outputDepth = vec4(1.0, 0, 0, 0);\n"
							"}\n";
#endif