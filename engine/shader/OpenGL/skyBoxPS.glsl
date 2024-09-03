#version 430 core
in vec3 texCoord;

out vec4 fragColor;

layout(binding = 0) uniform samplerCube cubeMap;

void main()
{
	fragColor = texture(cubeMap, texCoord);
}