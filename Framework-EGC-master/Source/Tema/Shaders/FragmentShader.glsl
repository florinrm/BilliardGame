#version 330

in vec3 frag_normal;
in vec2 tex_coord;

uniform sampler2D u_texture_0;
uniform int isUsedByRod;
uniform vec3 color;

layout(location = 0) out vec4 out_color;

void main()
{
	
	out_color = isUsedByRod == 0 ? texture(u_texture_0, tex_coord) : vec4(color, 1);
}