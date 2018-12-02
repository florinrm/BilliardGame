#version 330

in vec3 frag_normal;
in vec2 tex_coord;

uniform sampler2D u_texture_0;
uniform int cue_cond;
uniform vec3 color;

layout(location = 0) out vec4 out_color;

void main()
{
	if (cue_cond == 0)
		out_color = texture(u_texture_0, tex_coord);
	else
		out_color = vec4(color, 1);
}