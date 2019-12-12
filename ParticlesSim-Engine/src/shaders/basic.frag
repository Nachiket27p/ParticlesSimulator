#version 430 core

layout(location = 0) out vec4 color;

uniform vec4 ufm_color;
uniform vec2 light_pos;

in vec4 pos;

void main()
{
	float intensity = 1.0 / length(pos.xy - light_pos);
	color = ufm_color * intensity;
};
