#shader vertex
#version 460 core

layout(location = 0) in vec3 position;

uniform mat4 u_mvp = mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

void main() {
	gl_Position = u_mvp * vec4(position, 1);
}

#shader fragment
#version 460 core

out vec4 color;

uniform vec4 u_color = vec4(.95, .95, .95, 1);

void main() {
	color = u_color;
}