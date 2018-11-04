#pragma once

#include "mathUtility.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

namespace engine { namespace math {
	float magnitude(const vec3& vector);
	vec3 normalize(const vec3& vector);
	vec3 cross(const vec3& left, const vec3& right);

	mat4 transpose(const mat4& matrix);
	mat4 inverseTranspose(const mat4& matrix);
} }