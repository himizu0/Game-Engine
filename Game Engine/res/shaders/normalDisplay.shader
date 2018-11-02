#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec3 normal;
layout(location = 5) in float modelSlot;

out VS_OUT{
	vec3 normal;
} vs_out;

uniform mat4 u_vp;
uniform mat4 u_vpLightSpace;
uniform mat4 u_models[64];
uniform mat4 u_normals[64];

void main() {
	int mdlSlot = int(modelSlot + 0.1);

	gl_Position = u_vp * u_models[mdlSlot] * vec4(position, 1);
	vs_out.normal = mat3(u_normals[mdlSlot]) * normal;
}


#shader geometry
#version 460 core

layout(triangles) in;
layout(line_strip, max_vertices = 2) out;

in VS_OUT{
	vec3 normal;
} gs_in[];

const float magnitude = 100.0f;

void generateLine(int index){
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0f) * magnitude;
	EmitVertex();
	EndPrimitive();
}

void main(){
	generateLine(0); // First vertex normal
	generateLine(1); // Second vertex normal
	generateLine(2); // Third vertex normal
}


#shader fragment
#version 460 core

out vec4 color;

void main() {
	color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}