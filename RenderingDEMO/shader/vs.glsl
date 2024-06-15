#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;

out vec3 o_Color;

layout(std140, binding = 0) uniform Perframe
{
	mat4 proj_view_mat;
};

void main()
{
	o_Color = a_Color;
	gl_Position = proj_view_mat * vec4(a_Position, 1.0);
}