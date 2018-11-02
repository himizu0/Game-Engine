#shader vertex
#version 460 core

layout(location = 0) in vec3 position;


out VS_OUT {
	vec3 texCoords;
} vs_out;

uniform mat4 u_skyboxvp;	//This intentionally is not the ubo u_vp
							//Note that the view matrix for the skybox lacks translation entries 
							//The last column of the view matrix therefore must be (0,0,0,1)

void main() {
	vec4 pos = u_skyboxvp * vec4(position, 1);
	gl_Position = pos.xyww;
	vs_out.texCoords = position;
}

#shader fragment
#version 460 core

in VS_OUT{
	vec3 texCoords;
} fs_in;

out vec4 color;

uniform samplerCube u_texture;

void main(){
	color = texture(u_texture, fs_in.texCoords);
}