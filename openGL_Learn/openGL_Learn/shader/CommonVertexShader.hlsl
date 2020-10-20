
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


out VS_OUT {
    vec3 worldPos;
    vec3 worldNormal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 model;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    vs_out.worldPos = vec3(model * vec4(aPos,1.0));
    vs_out.worldNormal = mat3(transpose(inverse(model))) * aNormal;  
    vs_out.TexCoords = aTexCoords;

    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.worldPos, 1.0);
}