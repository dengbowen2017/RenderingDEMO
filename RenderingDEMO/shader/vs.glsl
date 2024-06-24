#version 430 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec3 i_Normal;

out vec3 o_Position;
out vec3 o_Normal;

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

void main()
{
	gl_Position = projectViewMatrix * vec4(i_Position, 1.0);
	o_Position = i_Position;
	o_Normal = i_Normal;
}