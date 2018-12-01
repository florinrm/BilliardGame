#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform int rodIsUsingShader, animationEnabeled;
uniform vec3 animationDirection;
uniform float time;

out vec3 frag_normal;
out vec3 frag_color;
out vec2 tex_coord;

float moving = 0;

void main()
{
	frag_normal = v_normal;
	frag_color = v_color;
	tex_coord = v_texture_coord;
	if(rodIsUsingShader == 1){
		if(animationEnabeled == 1){
			moving = abs( 0.15 * sin(2 * time));
			gl_Position = Projection * View * Model * vec4(v_position + animationDirection * moving * 2, 1.0);
		}else{
			gl_Position = Projection * View * Model * vec4(v_position  + animationDirection * moving, 1.0);
		}
	
	}else{
		gl_Position = Projection * View * Model * vec4(v_position, 1.0);
	}
	
}
