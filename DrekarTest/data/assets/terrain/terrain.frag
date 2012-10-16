#version 330 

smooth in vec3 theNormal;
smooth in vec2 theUv;
smooth in vec2 theDepth;

smooth in float slope;

uniform sampler2D _GrassTex;
uniform sampler2D _RockTex;

layout(location = 0) out vec4 outputColor; 
layout(location = 1) out vec4 outputNormal;
layout(location = 2) out vec4 outputDepth;

void main() 
{
	vec4 grass = texture2D(_GrassTex, theUv);
	vec4 rock = texture2D(_RockTex, theUv);

	float data = smoothstep(0.8, 1.0, slope);

	outputColor = vec4(mix(rock, grass, data).xyz, 0.0);
	outputNormal = vec4((theNormal + 1) * 0.5, 4);
	outputDepth.r = theDepth.x / theDepth.y;
}