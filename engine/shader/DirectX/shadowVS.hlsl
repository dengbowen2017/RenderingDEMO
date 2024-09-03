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
    matrix projectionViewNoTransMatrix;
    float3 cameraPos;
    float padding1;
    DirectionalLight directionalLight;
};

cbuffer PerObject : register(b1)
{
    matrix modelMatrix;
};

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput) 0;
    output.position = mul(directionalLight.spaceMatrix, mul(modelMatrix, float4(input.position, 1.0)));
    return output;
}