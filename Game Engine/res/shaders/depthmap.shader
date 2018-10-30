#shader vertex
#version 460 core

in layout(location = 0) vec3 position;
in layout(location = 5) float modelSlot;

layout(std140, binding = 0) uniform u_matrices{
	mat4 u_vp;
	mat4 u_vpLightSpace;
};

layout(std140, binding = 1) uniform u_modelMatrices{
	mat4 u_models[64];
	mat4 u_normals[64];
};


void main() {
	int mdlSlot = int(modelSlot + 0.1);

	gl_Position = u_vp * u_models[mdlSlot] * vec4(position, 1);
}


#shader fragment
#version 460 core

out vec4 color;

void main() {
	color = vec4(1, 0, 1, 1);
}