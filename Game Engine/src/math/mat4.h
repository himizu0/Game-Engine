#pragma once

#include <iostream>
#include <immintrin.h>
#include "vec3.h"
#include "vec4.h"
#include "mathUtility.h"

namespace engine { namespace math {
	struct mat4 {
#ifdef UNION
		union {
			__declspec(align(16)) float elements[4][4];
			__m128 columnRegisters[4];
		};
#else
		float elements[4][4];
#endif

		mat4() = default;
		mat4(float diagonal);

		static mat4 identity();
		static mat4 translate(const vec3& translation);
		static mat4 rotate(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);
		static mat4 orthographic(float left, float right, float top, float bottom, float near, float far);
		static mat4 perspective(float fov, float aspect, float near, float far);
		static mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up);

		friend mat4 transpose(const mat4& matrix);
		friend mat4 inverseTranspose(const mat4& matrix);	//TODO: Make this better! (to many flops)

		friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);
		friend mat4 operator*(const mat4& left, const mat4& right);
		friend vec4 operator*(const mat4& matrix, const vec4& vector);
		friend vec3 operator*(const mat4& matrix, const vec3& vector);
		
		float& operator()(unsigned int row, unsigned int column);
		const float& operator()(unsigned int row, unsigned int column) const;
		mat4& operator/=(float scalar);
	};
}}