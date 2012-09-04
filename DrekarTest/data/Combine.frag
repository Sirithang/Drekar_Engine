#version 330 

uniform sampler2D _Albedo;
uniform sampler2D _Light;

smooth in vec2 texcoord;

out vec4 outputColor;

void main() 
{ 
	vec4 albedo	= texture2D(_Albedo, texcoord);
	vec4 light	= texture2D(_Light, texcoord);

	outputColor = albedo * vec4(light.rgb, 1.0) + light.a;
}