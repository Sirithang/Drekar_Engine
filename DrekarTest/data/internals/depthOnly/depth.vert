#version 330 

uniform mat4 MATRIX_P; 
uniform mat4 MATRIX_V;
uniform mat4 MATRIX_M;

layout (location = 0) in vec3 inPosition;

void main() 
{ 
	vec4 pos = MATRIX_P * MATRIX_V * MATRIX_M * vec4(inPosition, 1.0);
	gl_Position = pos;
}