#version 330 core

out vec4 FragColor;

in vec3  outUV;

uniform samplerCube skybox;
//uniform sampler2D skybox;

void main()
{
    FragColor = texture(skybox, outUV);
    //FragColor = vec4(outUV,1.0);
}