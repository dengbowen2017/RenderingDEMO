#version 330 core

layout(location = 0) in vec3 a_Position;
out vec3 o_Position;

void main()
{
	o_Position = a_Position;
	gl_Position = vec4(a_Position, 1.0);
}