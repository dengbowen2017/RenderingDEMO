struct PSInput
{
    float4 position : SV_Position;
    float3 worldPos : POSITION0;
    float3 normal : NORMAL0;
    float2 texcoord : TEXCOORD0;
    float4 lightSpacePos : POSITION1;
};

struct PSOutput
{
    float4 color: SV_Target0;
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

sampler depthMapSampler : register(s0);
sampler diffuseMapSampler : register(s1);

Texture2D depthMap : register(t0);
Texture2D diffuseMap : register(t1);

float3 phongLighting(float3 N, float3 L, float3 V, float3 baseColor, float shadow)
{
    float3 reflectdir = reflect(-L, N);
    
    float3 ambient = 0.1;
    float3 diffuse = max(dot(L, N), 0.0f);
    float3 specular = pow(max(dot(V, reflectdir), 0.0), 32);

    return (ambient + (1.0 - shadow) * (diffuse + specular)) * baseColor;
}

float calculateShadow(float4 lightSpacePos, float3 norm, float3 lightDir)
{
    float3 projPos = lightSpacePos.xyz / lightSpacePos.w;
    float projCoordX = projPos.x * 0.5 + 0.5;
    float projCoordY = 1.0 - (projPos.y * 0.5 + 0.5);
    float2 projCoords = float2(projCoordX, projCoordY);
    float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);
    //float depth = depthMap.Sample(depthMapSampler, projCoords);
    //float shadow = projPos.z - bias > depth ? 1.0 : 0.0;
    float shadow = 0;
    float2 texelSize = 0;
    depthMap.GetDimensions(texelSize.x, texelSize.y);
    texelSize = 1.0 / texelSize;
    
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            float pcfDepth = depthMap.Sample(depthMapSampler, projCoords + float2(x, y) * texelSize).r;
            shadow += projPos.z - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    if (projPos.z > 1.0)
    {
        shadow = 0.0;
    }
    
    return shadow;
}

PSOutput main(PSInput input)
{
    PSOutput output = (PSOutput)0;
    float3 outColor = 0;
    
    float3 normalDir = normalize(input.normal);
    float3 viewDir = normalize(cameraPos - input.worldPos);
    float3 lightDir = 0;
    //float3 baseColor = float3(1.0f, 1.0f, 1.0f);
    float3 baseColor = diffuseMap.Sample(diffuseMapSampler, input.texcoord);
    
    // directional light
    lightDir = normalize(-directionalLight.direction);
    float shadow = calculateShadow(input.lightSpacePos, normalDir, lightDir);
    outColor += phongLighting(normalDir, lightDir, viewDir, baseColor, shadow) * directionalLight.intensity;
    
    output.color = float4(outColor, 1.0f);
    return output;
}