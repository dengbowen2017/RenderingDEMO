struct VSInput
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float2 texcoord : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float3 worldPos : POSITION0;
    float3 normal : NORMAL0;
    float2 texcoord : TEXCOORD0;
    float4 lightSpacePos : POSITION1;
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

cbuffer PerObject : register(b1)
{
    matrix modelMatrix;
};

float2 reverseTexCoord(float2 texcoord)
{
    return float2(texcoord.x, 1.0f - texcoord.y);
}

VSOutput main(VSInput input)
{
    VSOutput output = (VSOutput)0;
    
    output.worldPos = mul(modelMatrix, float4(input.position, 1.0));
    
    output.normal = mul(modelMatrix, input.normal);
    output.texcoord = input.texcoord;
    
    output.position = mul(projectionViewMatrix, float4(output.worldPos, 1.0));
    output.lightSpacePos = mul(directionalLight.lightSpaceMatrix, float4(output.worldPos, 1.0));
    return output;
}