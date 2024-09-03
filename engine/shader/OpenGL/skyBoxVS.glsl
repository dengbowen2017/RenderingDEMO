#version 430 core
layout (location = 0) in vec3 i_Position;

out vec3 texCoord;

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

void main()
{
    texCoord = i_Position;
    vec4 pos = projectViewNoTransMatrix * vec4(i_Position, 1.0);
    gl_Position = pos.xyww;
}