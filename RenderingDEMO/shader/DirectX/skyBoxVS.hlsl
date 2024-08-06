struct VSInput
{
    float3 position : POSITION0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float3 texCoord : TEXCOORD0;
};

struct DirectionalLight
{
    float3 direction;
    float padding1;
    float3 intensity;
    float padding2;
    matrix lightSpaceMatrix;
};

cbuffer PerFrame : register(b0)
{
    matrix projectionViewMatrix;
    matrix projectionViewNoTransMatrix;
    float3 cameraPos;
    float padding1;
    DirectionalLight directionalLight;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput) 0;
    float4 pos = mul(projectionViewNoTransMatrix, float4(input.position, 1.0));
    output.position = pos.xyww;
    output.texCoord = input.position;
    return output;
}