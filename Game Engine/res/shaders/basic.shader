#shader vertex
#version 460 core

layout(location = 0) in vec3 position;

uniform mat4 u_mvp;

void main() {
	gl_Position = u_mvp * vec4(position, 1);
}

#shader fragment
#version 460 core

out vec4 color;

void main() {
	color = vec4(1, 0, 0, 1);
}