#version 330 

smooth in vec3 theNormal;
smooth in vec2 theDepth;

layout(location = 0) out vec4 outputColor; 
layout(location = 1) out vec4 outputNormal;
layout(location = 2) out vec4 outputDepth;

void main() 
{ 
   outputColor = vec4(1,1,1,0.1);//vec4(1.0, 1.0, 1.0, 1.0);
   outputNormal = vec4((theNormal + 1) * 0.5, 4);
   outputDepth.r = theDepth.x / theDepth.y;
}