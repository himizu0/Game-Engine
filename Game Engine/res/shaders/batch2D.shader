#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texSlot;

out vec2 v_texCoord;
out float v_texSlot;

uniform mat4 u_mvp;

void main() {
	gl_Position = u_mvp * vec4(position, 1);
	v_texCoord = texCoord;
	v_texSlot = texSlot;
}


#shader fragment
#version 460 core

in vec2 v_texCoord;
in float v_texSlot;

out vec4 color;

uniform sampler2D u_textures[32];

void main() {
	int texSlot = int(v_texSlot + 0.1f);

	color = texture(u_textures[texSlot], v_texCoord);
}