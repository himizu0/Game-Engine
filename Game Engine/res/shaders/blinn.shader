#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in float diffuseSlot;
layout(location = 4) in float specularSlot;
layout(location = 5) in float modelSlot;

out vec2 v_texCoord;
out vec3 v_position;
out vec3 v_fragPosition;
out vec3 v_lightSpaceFragPosition;
out vec3 v_normal;
out float v_diffuseSlot;
out float v_specularSlot;

layout (std140, binding = 0) uniform u_matrices{
	mat4 u_vp;
	mat4 u_vpLightSpace;
};

layout (std140, binding = 1) uniform u_modelMatrices{
	mat4 u_models[64];
	mat4 u_normals[64];
};

void main() {
	int mdlSlot = int(modelSlot + 0.1);

	gl_Position = u_vp * u_models[mdlSlot] * vec4(position, 1);
	v_texCoord = texCoord;
	v_position = position;
	v_fragPosition = vec3(u_models[mdlSlot] * vec4(position, 1));
	v_lightSpaceFragPosition = vec3(u_vpLightSpace * vec4(v_fragPosition, 1));
	v_normal = mat3(u_normals[mdlSlot]) * normal;
	v_diffuseSlot = diffuseSlot;
	v_specularSlot = specularSlot;
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

in vec2 v_texCoord;
in vec3 v_position;
in vec3 v_fragPosition;
in vec3 v_lightSpaceFragPosition;
in vec3 v_normal;
in float v_diffuseSlot;
in float v_specularSlot;

out vec4 color;

uniform vec3 u_viewPosition;
uniform sampler2D u_depthmap;
uniform sampler2D u_textures[31];
uniform Light u_light;

void main() {
	int diffuseSlot = int(v_diffuseSlot + 0.1);
	int specularSlot = int(v_specularSlot + 0.1);

	vec3 ambient = vec3(texture(u_textures[diffuseSlot], v_texCoord)) * u_light.ambient;

	vec3 normal = normalize(v_normal);
	//vec3 lightDir = normalize(u_light.position - v_fragPosition);
	vec3 lightDir = normalize(vec3(1, 1, 1));
	vec3 diffuse = max(dot(normal, lightDir), 0) * vec3(texture(u_textures[diffuseSlot], v_texCoord)) * u_light.diffuse;

	vec3 viewDir = normalize(u_viewPosition - v_fragPosition);
	vec3 halfDir = normalize(viewDir + lightDir);
	vec3 specular = pow(max(dot(halfDir, normal), 0), 8) * vec3(texture(u_textures[specularSlot], v_texCoord)) * u_light.specular;

	vec3 projCoords = v_lightSpaceFragPosition * 0.5 + 0.5;
	float closestDepth = texture(u_depthmap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float shadow = currentDepth > closestDepth ? 0.0f : 1.0f;

	float distance = length(v_fragPosition - u_light.position);
	color = vec4(1.0f * (diffuse + specular) / (1 + 0.0014f * distance + 0.000007f * distance * distance), texture(u_textures[diffuseSlot], v_texCoord).w);
	color.x = ambient.x + (floor(color.x * 5) / 5);
	color.y = ambient.y + (floor(color.y * 5) / 5);
	color.z = ambient.z + (floor(color.z * 5) / 5);

	//color = texture(u_depthmap, projCoords.xy);
}