#version 330 

uniform sampler2D _Albedo;
uniform sampler2D _Normal;
uniform sampler2D _Depth;

uniform mat4	_InvertP;
uniform vec4	_LightPos;
uniform vec4	_LightColor;
uniform float	_Radius;

smooth in vec4 texcoord;

layout(location = 0) out vec4 outputColor; 

void main() 
{ 
	vec2 trueTexCoord = ((texcoord.xy / texcoord.w) + 1) * 0.5;

	float	specIntensity = texture2D(_Albedo, trueTexCoord).a;
	vec4	normal = texture2D(_Normal, trueTexCoord);
	vec3	unpacked = normal.xyz * 2 - 1;

	float depth = texture2D(_Depth, trueTexCoord).r;

	vec4 position;
	position.x = texcoord.x/texcoord.w;
	position.y = texcoord.y/texcoord.w;
	position.z = depth;
	position.w = 1.0f;

	position = _InvertP * position;
	position.xyz /= position.w;

	vec3 lightDir = _LightPos.xyz - position.xyz;
	vec3 nLightDir = normalize(lightDir);

	vec3 reflectionVector = normalize(reflect(-nLightDir, normal.xyz));
	vec3 pixelToCam = normalize(-position.xyz);

	float attenuation = clamp(1.0 - length(lightDir)/_Radius, 0.0, 1.0); 
	float spec =  specIntensity * pow( clamp(dot(reflectionVector, pixelToCam), 0.0, 1.0), normal.w);

	outputColor = attenuation * vec4(_LightColor.xyz * max(0.0, dot(unpacked, nLightDir.xyz)), spec);
}