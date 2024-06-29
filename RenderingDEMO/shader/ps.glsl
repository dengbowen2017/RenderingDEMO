#version 430 core

in VSOutput
{
    vec3 worldPos;
    vec3 normal;
} psIn;

out vec4 fragColor;

struct PointLight
{
    vec3 position;
    float a;
    vec3 intensity;
    float b;
};

struct DirectionalLight
{
    vec3 direction;
    float padding1;
    vec3 intensity;
    float padding2;
};

layout(std140, binding = 0) uniform Perframe
{
	mat4 projectViewMatrix;
    vec3 cameraPos;
    uint pointLightNum;
    PointLight pointLights[8];
    DirectionalLight directionalLight;
};

vec3 phongLighting(vec3 N, vec3 L, vec3 V, vec3 baseColor)
{
    vec3 reflectdir = reflect(-L, N);
    
    vec3 ambient = vec3(0.1);
    vec3 diffuse = vec3(max(dot(L, N), 0.0f));
    vec3 specular = vec3(pow(max(dot(V, reflectdir), 0.0), 32));

    return (ambient + diffuse + specular) * baseColor;
}

void main()
{
    fragColor = vec4(0);
    vec3 outColor = vec3(0);

    vec3 normaldir = normalize(psIn.normal);
    vec3 viewdir = normalize(cameraPos - psIn.worldPos);
    vec3 lightdir = vec3(0);
    vec3 baseColor = vec3(1.0f, 1.0f, 1.0f);
    
//    // point lights
//    for (uint i = 0; i < pointLightNum; i++)
//    {
//        lightdir = normalize(pointLights[i].position - psIn.worldPos);
//        outColor += phongLighting(normaldir, lightdir, viewdir, baseColor) * pointLights[i].intensity;
//    }
        
    // directional light
    lightdir = normalize(-directionalLight.direction);
    outColor += phongLighting(normaldir, lightdir, viewdir, baseColor) * directionalLight.intensity;
    
    fragColor = vec4(outColor, 1.0f);
}