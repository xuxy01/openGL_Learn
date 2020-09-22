#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;

out vec3 outUV;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    outUV = pos;
    vec4 tempPos = projection * view * vec4(pos, 1.0);
    gl_Position = tempPos.xyww;
}