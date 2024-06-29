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

float3 phongLighting(float3 N, float3 L, float3 V, float3 baseColor)
{
    float3 reflectdir = reflect(-L, N);
    
    float3 ambient = 0.1;
    float3 diffuse = max(dot(L, N), 0.0f);
    float3 specular = pow(max(dot(V, reflectdir), 0.0), 32);

    return (ambient + diffuse + specular) * baseColor;
}

PSOutput main(PSInput input)
{
    PSOutput output = (PSOutput)0;
    float3 outColor = 0;
    
    float3 normaldir = normalize(input.normal);
    float3 viewdir = normalize(cameraPos - input.worldPos);
    float3 lightdir = 0;
    float3 baseColor = float3(1.0f, 1.0f, 1.0f);
    
    //// point lights
    //for (uint i = 0; i < pointLightNum; i++)
    //{
    //    lightdir = normalize(pointLights[i].position - input.worldPos);
    //    outColor += phongLighting(normaldir, lightdir, viewdir, baseColor) * pointLights[i].intensity;
    //}
        
    // directional light
    lightdir = normalize(-directionalLight.direction);
    outColor += phongLighting(normaldir, lightdir, viewdir, baseColor) * directionalLight.intensity;
    
    output.color = float4(outColor, 1.0f);
    return output;
}