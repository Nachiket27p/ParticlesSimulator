#version 430 core

layout(location = 0) out vec4 color;

uniform vec4 ufm_color;

in DATA
{
	//vec4 position;
	vec4 color;
} fs_in;

void main()
{
	//color = ufm_color;
	color = fs_in.color;
};
