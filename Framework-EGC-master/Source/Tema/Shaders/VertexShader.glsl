#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 animate_direction;
uniform int cue_shader;
uniform int en_animation;
uniform float time;

out vec3 frag_normal;
out vec3 frag_color;
out vec2 tex_coord;

float displacement = 0;

void main()
{
	frag_color = v_color;
	tex_coord = v_texture_coord;
	frag_normal = v_normal;
	if (cue_shader == 1){
		if (en_animation == 1) {
			displacement = abs(0.15 * sin(2 * time));
			gl_Position = Projection * View * Model * vec4(v_position + animate_direction * displacement * 2, 1.0);
		} else {
			gl_Position = Projection * View * Model * vec4(v_position + animate_direction * displacement, 1.0);
		}
	
	} else {
		gl_Position = Projection * View * Model * vec4(v_position, 1.0);
	}
	
}