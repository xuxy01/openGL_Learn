
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec4 worldPos;
out vec3 worldNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    worldPos = model * vec4(aPos + aNormal*0.1,1.0);
    worldNormal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos + aNormal*0.5, 1.0);
}