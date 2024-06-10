struct PSInput
{
    float4 position: SV_Position;
};

struct PSOutput
{
    float4 color: SV_Target0;
};

PSOutput main(PSInput input)
{
    PSOutput output = (PSOutput)0;
    output.color = float4(0.7, 0.3, 0.2, 1.0);
    return output;
}