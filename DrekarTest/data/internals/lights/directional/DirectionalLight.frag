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

	vec4 worldpos = _InvertVP * position;
	worldpos.xyz /= worldpos.w;

	//Compute position in Light Clip space

	vec4 lightPix = _VPLight * vec4(worldpos.xyz, 1.0);
	lightPix.xyz /= lightPix.w;

	vec2 lightTex = vec2(lightPix.x* 0.5 + 0.5, lightPix.y* 0.5 + 0.5);

	float pixDepth = lightPix.z * 0.5 + 0.5;
	float lightDepth = texture2D(_ShadowMap, lightTex.xy).x;

	float visibility = 1.0;
	if(pixDepth > lightDepth)
	{
		visibility = 0.0;
	}

	

	vec3 reflectionVector = normalize(reflect(_LightDirection.xyz, normal.xyz)).xyz;
	vec3 pixelToCam = normalize(_CamPos.xyz-worldpos.xyz);

	float spec =  specIntensity * pow( clamp(dot(reflectionVector, pixelToCam), 0.0, 1.0), normal.w);

	outputColor = vec4(_LightColor.xyz * max(0.0, dot(unpacked, -_LightDirection.xyz)) * visibility, spec);
}