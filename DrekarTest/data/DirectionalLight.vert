#version 330 

layout (location = 0) in vec3 inPosition;
layout (location = 2) in vec2 inUv;

smooth out vec2 texcoord;

void main() 
{ 
	gl_Position = vec4(inPosition, 1.0);
	texcoord	= inUv;
}