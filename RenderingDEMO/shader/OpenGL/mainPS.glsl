#version 430 core

in VSOutput
{
    vec3 worldPos;
    vec3 normal;
    vec4 lightSpacePos;
} psIn;

out vec4 fragColor;

struct DirectionalLight
{
    vec3 direction;
    float padding1;
    vec3 intensity;
    float padding2;
    mat4 spaceMatrix;
};

layout(std140, binding = 0) uniform Perframe
{
	mat4 projectViewMatrix;
    vec3 cameraPos;
    float padding1;
    DirectionalLight directionalLight;
};

layout(binding = 0) uniform sampler2D depthMap;

vec3 phongLighting(vec3 N, vec3 L, vec3 V, vec3 baseColor, float shadow)
{
    vec3 reflectdir = reflect(-L, N);
    
    vec3 ambient = vec3(0.1);
    vec3 diffuse = vec3(max(dot(L, N), 0.0f));
    vec3 specular = vec3(pow(max(dot(V, reflectdir), 0.0), 32));

    return (ambient + (1.0 - shadow) * (diffuse + specular)) * baseColor;
    //return (ambient + diffuse + specular) * baseColor;
}

float calculateShadow(vec4 lightSpacePos, vec3 norm, vec3 lightDir)
{
    vec3 projPos = lightSpacePos.xyz / lightSpacePos.w;
    vec2 projCoords = projPos.xy * 0.5f + 0.5f;
    float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);
    float shadow = 0.0f;
    vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    for (int x = -1; x <=1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            float pcfDepth = texture(depthMap, projCoords + vec2(x, y) * texelSize).r;
            shadow += projPos.z - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    if (projPos.z > 1.0)
    {
        shadow = 0.0;
    }

    return shadow;
}

void main()
{
    vec3 outColor = vec3(0);

    vec3 normalDir = normalize(psIn.normal);
    vec3 viewDir = normalize(cameraPos - psIn.worldPos);
    vec3 lightDir = vec3(0);
    vec3 baseColor = vec3(1.0f, 1.0f, 1.0f);
        
    // directional light
    lightDir = normalize(-directionalLight.direction);
    float shadow = calculateShadow(psIn.lightSpacePos, normalDir, lightDir);
    outColor += phongLighting(normalDir, lightDir, viewDir, baseColor, shadow) * directionalLight.intensity;

    fragColor = vec4(outColor, 1.0f);
}