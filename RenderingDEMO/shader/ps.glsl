#version 430 core

in vec3 o_Position;
in vec3 o_Normal;

out vec4 fragColor;

struct PointLight
{
    vec3 position;
    float a;
    vec3 intensity;
    float b;
};

struct DirectionalLight
{
    vec3 direction;
    float padding1;
    vec3 intensity;
    float padding2;
};

layout(std140, binding = 0) uniform Perframe
{
	mat4 projectViewMatrix;
    vec3 cameraPos;
    uint pointLightNum;
    PointLight pointLights[8];
    DirectionalLight directionalLight;
};

vec4 phongLighting(vec3 pos, vec3 norm, PointLight light)
{
    vec3 normaldir = normalize(norm);
    vec3 lightdir = normalize(light.position - pos);
    vec3 viewdir = normalize(cameraPos - pos);
    vec3 reflectdir = reflect(-lightdir, normaldir);

    vec3 ambient = 0.1 * light.intensity;
    vec3 diffuse = max(dot(lightdir, normaldir), 0.0) * light.intensity;
    vec3 specular = pow(max(dot(viewdir, reflectdir), 0.0), 32) * light.intensity;

    vec3 objectcolor = vec3(1.0, 0.5, 0.31);
    return vec4((ambient + diffuse + specular) * objectcolor, 1.0);
}

void main()
{
    // remember to initialize out value
    fragColor = vec4(0);

    for(uint i = 0; i < pointLightNum; i++)
    {
        fragColor += phongLighting(o_Position, o_Normal, pointLights[i]);
    }
}