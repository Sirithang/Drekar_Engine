#version 330 

uniform sampler2D _Albedo;
uniform sampler2D _Normal;
uniform sampler2D _Depth;

uniform sampler2D _ShadowMap;

uniform mat4 _InvertVP;
uniform vec4 _LightDirection;
uniform vec4 _LightColor;
uniform vec4 _CamPos;

uniform mat4 _VPLight;

smooth in vec2 texcoord;

layout(location = 0) out vec4 outputColor; 

void main() 
{ 
	float	specIntensity = texture2D(_Albedo, texcoord).a;
	vec4	normal = texture2D(_Normal, texcoord);
	vec3	unpacked = normal.xyz * 2 - 1;

	float depth = texture2D(_Depth, texcoord).r;

	vec4 position;
	position.x = texcoord.x * 2.0f - 1.0f;
	position.y = texcoord.y * 2.0f - 1.0f;
	position.z = depth;
	position.w = 1.0f;

	position = _InvertVP * position;
	position.xyz /= position.w;

	//Compute position in Light Clip space

	vec4 lightPix = _VPLight * vec4(position.xyz, 1.0);
	vec2 lightTex = ((lightPix.xy/lightPix.w) + 1) * 0.5;

	float pixDepth = lightPix.z/lightPix.w;
	float lightDepth = texture2D(_ShadowMap, lightTex.xy).x;

	float visibility = 1.0;
	if(pixDepth > (lightDepth * 2.0 - 1))
	{
		visibility = 0.0f;
	}

	vec3 reflectionVector = normalize(reflect(_LightDirection.xyz, normal.xyz)).xyz;
	vec3 pixelToCam = normalize(_CamPos.xyz-position.xyz);

	float spec =  specIntensity * pow( clamp(dot(reflectionVector, pixelToCam), 0.0, 1.0), normal.w);

	outputColor = vec4(_LightColor.xyz * max(0.0, dot(unpacked, -_LightDirection.xyz)) * visibility, spec);
}