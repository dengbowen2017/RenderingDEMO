struct PSInput
{
    float4 position : SV_Position;
    float3 worldPos : POSITION0;
    float3 normal : NORMAL0;
};

struct PSOutput
{
    float4 color: SV_Target0;
};

struct PointLight
{
    float3 position;
    float a;
    float3 intensity;
    float b;
};

struct DirectionalLight
{
    float3 direction;
    float padding1;
    float3 intensity;
    float padding2;
};

cbuffer PerFrame : register(b0)
{
    matrix viewProjection;
    float3 cameraPos;
    uint pointLightNum;
    PointLight pointLights[8];
    DirectionalLight directionalLight;
};

float4 phongLighting(PSInput input, PointLight light)
{
    float3 normaldir = normalize(input.normal);
    float3 lightdir = normalize(light.position - input.worldPos);
    float3 viewdir = normalize(cameraPos - input.worldPos);
    float3 reflectdir = reflect(-lightdir, normaldir);
    
    float3 ambient = 0.1 * light.intensity;
    float3 diffuse = max(dot(lightdir, normaldir), 0.0f) * light.intensity;
    //float3 specular = pow(max(dot(halfdir, normaldir), 0.0f), 4.0f) * light.intensity;
    float3 specular = pow(max(dot(viewdir, reflectdir), 0.0), 32) * light.intensity;
    
    float3 objectcolor = float3(1.0f, 0.5f, 0.31f);
    return float4((ambient + diffuse + specular) * objectcolor, 1.0f);
}

PSOutput main(PSInput input)
{
    PSOutput output = (PSOutput)0;
    
    for (uint i = 0; i < pointLightNum; i++)
    {
        output.color += phongLighting(input, pointLights[i]);
    }
    
    return output;
}