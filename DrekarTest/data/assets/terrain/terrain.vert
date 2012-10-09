#version 330 

uniform mat4 MATRIX_P; 
uniform mat4 MATRIX_V;
uniform mat4 MATRIX_M;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUV;

smooth out vec3 theNormal;
smooth out vec2 theUv;
smooth out vec2 theDepth;
smooth out float slope;

void main() 
{ 
	mat4 MVP = MATRIX_P * MATRIX_V * MATRIX_M;
	gl_Position = MVP * vec4(inPosition, 1.0);

	slope = clamp(abs(dot(inNormal.xyz, vec3(0,1,0))), 0.0, 1.0);

	theNormal = (inverse(transpose(MATRIX_M)) * vec4(inNormal.xyz, 0.0)).xyz;

	theDepth = gl_Position.zw;
	theUv = inUV;
}