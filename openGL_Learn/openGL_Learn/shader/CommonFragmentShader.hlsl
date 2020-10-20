
#version 330 core
out vec4 FragColor;


in VS_OUT {
    vec3 worldPos;
    vec3 worldNormal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform vec3 viewPos;

uniform sampler2D shadowMap;

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

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth  = texture(shadowMap, projCoords.xy).r;

    float currentDepth = projCoords.z;
    float bias = 0.005;
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    return shadow;
}

void main()
{
    float ambient = 0.2;

    vec3 norm = normalize(fs_in.worldNormal);
    //直射光
    vec3 lightDir = normalize(-directLight.direction);

    //点光源
    //vec3 lightDir = normalize(spotLight.position - worldPos.xyz);
    //float distance = length(spotLight.position - worldPos.xyz);
    //float attenuation = 1.0/(spotLight.constant +spotLight.linear*distance + spotLight.quadratic * distance*distance );

    //聚光灯
    //vec3 lightDir = normalize(spotLight.position - worldPos.xyz);
    //float theta = dot(lightDir , normalize(-spotLight.direction));
    //float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    //float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    //float distance = length(spotLight.position - worldPos.xyz);
    //float attenuation = 1.0/(spotLight.constant +spotLight.linear*distance + spotLight.quadratic * distance*distance );

    float diffuse = max(dot(lightDir, norm)/2 + 0.5, 0);

    //vec3 color = (ambient+ diffuse)*intensity* attenuation* spotLight.lightColor * texture(texture_diffuse1, TexCoords).rgb;

    vec3 viewDir = normalize(viewPos - fs_in.worldPos.xyz);

    vec3 halfDir  = normalize(lightDir + viewDir);
    float specular = pow(max(dot(halfDir, norm), 0), 16);

    float shadow  =  ShadowCalculation(fs_in.FragPosLightSpace);
    vec3 color = (ambient +  (1.0 - shadow) * (diffuse+specular))*  directLight.lightColor * texture(texture_diffuse1, fs_in.TexCoords).rgb;

    //vec3 color = (ambient + (1.0 - shadow) * (diffuse+specular)) *  directLight.lightColor;

    FragColor = vec4(color  , 1.0f);
}