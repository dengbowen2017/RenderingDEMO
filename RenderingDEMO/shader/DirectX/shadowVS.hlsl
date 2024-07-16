struct VSInput
{
    float3 position : POSITION0;
};

struct VSOutput
{
    float4 position : SV_Position;
};

struct DirectionalLight
{
    float3 direction;
    float padding1;
    float3 intensity;
    float padding2;
    matrix spaceMatrix;
};

cbuffer PerFrame : register(b0)
{
    matrix projectionViewMatrix;
    float3 cameraPos;
    float padding1;
    DirectionalLight directionalLight;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput) 0;
    output.position = mul(directionalLight.spaceMatrix, float4(input.position, 1.0));
    return output;
}