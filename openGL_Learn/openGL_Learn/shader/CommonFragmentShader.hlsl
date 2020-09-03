#version 330 core

out vec4 fragColor;

in vec3 outColor;
in vec2 outUV;

uniform sampler2D texture0;

uniform float time;
uniform vec4 baseColor;

void main()
{
	vec4 texColor = texture(texture0, outUV);
	fragColor =  vec4(outColor*sin(time), 1.0);
	//fragColor = texColor ;
}