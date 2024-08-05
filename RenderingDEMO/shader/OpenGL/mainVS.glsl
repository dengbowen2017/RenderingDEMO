#version 430 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec3 i_Normal;
layout(location = 2) in vec2 i_TexCoord;

out VSOutput
{
    vec3 worldPos;
    vec3 normal;
    vec2 texcoord;
    vec4 lightSpacePos;
} vsOut;

struct DirectionalLight
{
    vec3 direction;
    float padding1;
    vec3 intensity;
    float padding2;
    mat4 spaceMatrix;
};

layout(std140, binding = 0) uniform Perframe
{
	mat4 projectViewMatrix;
    vec3 cameraPos;
    float padding1;
    DirectionalLight directionalLight;
};

void main()
{
	gl_Position = projectViewMatrix * vec4(i_Position, 1.0);
    vsOut.worldPos = i_Position;
    vsOut.normal = i_Normal;
    vsOut.texcoord = i_TexCoord;
    vsOut.lightSpacePos = directionalLight.spaceMatrix * vec4(i_Position, 1.0);
}