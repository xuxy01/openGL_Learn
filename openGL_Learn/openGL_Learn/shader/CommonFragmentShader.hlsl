#version 330 core

out vec4 fragColor;

in vec3 outColor;

uniform float time;

uniform vec4 baseColor;

void main()
{
	fragColor = vec4(outColor*sin(time), 1.0);
}