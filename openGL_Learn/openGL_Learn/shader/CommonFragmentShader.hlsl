
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 worldPos;
in vec3 worldNormal;

uniform sampler2D texture_diffuse1;

struct DirectLight {
    vec3 lightColor;
    vec3 direction;
}; 

struct PointLight {
    vec3 position;  

    vec3 lightColor;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 lightColor;

    float constant;
    float linear;
    float quadratic;
};


uniform DirectLight directLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;


void main()
{
    float ambient = 0.2;

    vec3 norm = normalize(worldNormal);
    //直射光
    //vec3 lightDir = normalize(worldPos-directLight.direction);

    //点光源
    //vec3 lightDir = normalize(spotLight.position - worldPos.xyz);
    //float distance = length(spotLight.position - worldPos.xyz);
    //float attenuation = 1.0/(spotLight.constant +spotLight.linear*distance + spotLight.quadratic * distance*distance );

    //聚光灯
    vec3 lightDir = normalize(spotLight.position - worldPos.xyz);
    float theta = dot(lightDir , normalize(-spotLight.direction));
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    float distance = length(spotLight.position - worldPos.xyz);
    float attenuation = 1.0/(spotLight.constant +spotLight.linear*distance + spotLight.quadratic * distance*distance );

    float diffuse = max(dot(lightDir, norm)/2 + 0.5, 0);

    vec3 color = (ambient+ diffuse)*intensity* attenuation* spotLight.lightColor * texture(texture_diffuse1, TexCoords).rgb;

    FragColor = vec4(color, 1.0f);
}