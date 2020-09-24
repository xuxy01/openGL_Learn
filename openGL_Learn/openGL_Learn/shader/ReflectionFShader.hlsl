
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 worldPos;
in vec3 worldNormal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform vec3 viewPos;

uniform samplerCube skybox;



void main()
{
    float ambient = 0.2;

    vec3 norm = normalize(worldNormal);
    //直射光


    vec3 viewDir = normalize( worldPos.xyz - viewPos );

    vec3 reflectionDir = reflect(viewDir, normalize(worldNormal));
    reflectionDir = refract(viewDir, normalize(worldNormal),  1.309);
    vec3 color = texture(skybox,reflectionDir).rgb * texture(texture_diffuse1, TexCoords).rgb;

    FragColor = vec4(color , 1.0f);
}