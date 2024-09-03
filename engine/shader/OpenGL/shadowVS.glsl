#version 430 core
layout (location = 0) in vec3 aPos;

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
    mat4 projectViewNoTransMatrix;
    vec3 cameraPos;
    float padding1;
    DirectionalLight directionalLight;
};

layout(std140, binding = 1) uniform PerObject
{
    mat4 modelMatrix;
};

void main()
{
    gl_Position = directionalLight.spaceMatrix * modelMatrix * vec4(aPos, 1.0);
}