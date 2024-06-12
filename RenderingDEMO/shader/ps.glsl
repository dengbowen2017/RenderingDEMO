#version 330 core

in vec3 o_Color;

out vec4 Color;

void main()
{
	Color = vec4(o_Color, 1.0f);
}