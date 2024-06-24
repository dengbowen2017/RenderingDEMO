struct VSInput
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float3 worldPos : POSITION0;
    float3 normal : NORMAL0;
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
    matrix projectionViewMatrix;
    float3 cameraPos;
    uint pointLightNum;
    PointLight pointLights[8];
    DirectionalLight directionalLight;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    output.position = mul(projectionViewMatrix, float4(input.position, 1.0));
    output.worldPos = input.position;
    output.normal = input.normal;
    return output;
}