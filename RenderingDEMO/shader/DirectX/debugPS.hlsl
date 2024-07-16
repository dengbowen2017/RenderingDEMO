struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
};

struct PSOutput
{
    float4 color : SV_Target0;
};

sampler depthMapSampler : register(s0);

Texture2D depthMap : register(t0);

// temp
float2 reverseTexCoord(float2 texcoord)
{
    return float2(texcoord.x, 1.0f - texcoord.y);
}

PSOutput main(PSInput input)
{
    PSOutput output = (PSOutput) 0;
    output.color = depthMap.Sample(depthMapSampler, reverseTexCoord(input.uv));    
    return output;
}