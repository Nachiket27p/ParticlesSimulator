#version 460 core

layout(location = 0) out vec4 color;

uniform sampler2D textures[32];

in DATA
{
	vec4 color;
	float tid;
	vec2 uv;
} fs_in;

void main()
{
	//color = fs_in.color;

	vec4 texColor = fs_in.color;
	if(fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = texture(textures[tid], fs_in.uv);
	}
	color = texColor;
	
};
