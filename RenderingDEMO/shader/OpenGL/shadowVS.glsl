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
    vec3 cameraPos;
    float padding1;
    DirectionalLight directionalLight;
};

void main()
{
    gl_Position = directionalLight.spaceMatrix * vec4(aPos, 1.0);
}