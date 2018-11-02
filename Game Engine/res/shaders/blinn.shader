#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in float diffuseSlot;
layout(location = 4) in float specularSlot;
layout(location = 5) in float modelSlot;

out VS_OUT{
	vec2 texCoord;
	vec3 position;
	vec3 fragPosition;
	vec3 normal;
	float diffuseSlot;
	float specularSlot;
} vs_out;

uniform mat4 u_vp;

layout(std140, binding = 0) uniform u_modelMatrices{
	mat4 u_models[64];
	mat4 u_normals[64];
};

void main() {
	int mdlSlot = int(modelSlot + 0.1);

	gl_Position = u_vp * u_models[mdlSlot] * vec4(position, 1);
	vs_out.texCoord = texCoord;
	vs_out.position = position;
	vs_out.fragPosition = vec3(u_models[mdlSlot] * vec4(position, 1));
	vs_out.normal = mat3(u_normals[mdlSlot]) * normal;
	vs_out.diffuseSlot = diffuseSlot;
	vs_out.specularSlot = specularSlot;
}


#shader fragment
#version 460 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in VS_OUT{
	vec2 texCoord;
	vec3 position;
	vec3 fragPosition;
	vec3 normal;
	float diffuseSlot;
	float specularSlot;
} fs_in;

out vec4 color;

uniform vec3 u_viewPosition;
uniform sampler2D u_textures[32];
uniform Light u_light1;
uniform Light u_light2;

vec4 calculateLighting(Light light) {
	int diffuseSlot = int(fs_in.diffuseSlot + 0.1);
	int specularSlot = int(fs_in.specularSlot + 0.1);

	vec3 ambient = vec3(texture(u_textures[diffuseSlot], fs_in.texCoord)) * light.ambient;

	vec3 normal = normalize(fs_in.normal);
	vec3 lightDir = normalize(light.position - fs_in.fragPosition);
	vec3 diffuse = max(dot(normal, lightDir), 0) * vec3(texture(u_textures[diffuseSlot], fs_in.texCoord)) * light.diffuse;

	vec3 viewDir = normalize(u_viewPosition - fs_in.fragPosition);
	vec3 halfDir = normalize(viewDir + lightDir);
	vec3 specular = pow(max(dot(halfDir, normal), 0), 8) * vec3(texture(u_textures[specularSlot], fs_in.texCoord)) * light.specular;

	float distance = length(fs_in.fragPosition - light.position);
	vec4 lightingColor = vec4(ambient + (diffuse + specular) / (1 + 0.0014f * distance + 0.000007f * distance * distance), texture(u_textures[diffuseSlot], fs_in.texCoord).w);

	return lightingColor;
}

void main() {
	color = calculateLighting(u_light1);
	color += calculateLighting(u_light2);

	color = (floor(color * 3) / 3) +.05f;
}