#version 330 core

out vec4 Color;
in vec3 o_Position;

void main()
{
	Color = vec4(o_Position.x, o_Position.y, o_Position.z, 1.0f);
}