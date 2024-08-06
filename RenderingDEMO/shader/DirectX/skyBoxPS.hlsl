struct PSInput
{
    float4 position : SV_Position;
    float3 texCoord : TEXCOORD0;
};

struct PSOutput
{
    float4 color : SV_Target0;
};

sampler cubeMapSampler : register(s0);
TextureCube cubeMap : register(t0);

PSOutput main(PSInput input)
{
    PSOutput output = (PSOutput) 0;
    output.color = cubeMap.Sample(cubeMapSampler, input.texCoord);
    return output;
}