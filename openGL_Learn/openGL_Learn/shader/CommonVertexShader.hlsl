#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;

out vec3 outColor;
out vec2 outUV;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	//gl_Position = projection * view * model * vec4(pos, 1.0);
    gl_Position =    projection * view *model*  vec4(pos, 1.0) ;
	outColor = color;
	outUV = uv;
}