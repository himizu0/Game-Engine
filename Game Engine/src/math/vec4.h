#pragma once
#include <iostream>

namespace engine { namespace math {
	struct vec4 {
		float x, y, z, w;

		vec4() = default;
		vec4(float x, float y, float z, float w);

		friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
		friend vec4 operator+(const vec4& left, const vec4& right);
		friend vec4 operator-(const vec4& left, const vec4& right);
		friend vec4 operator*(float scalar, const vec4& vector);
		friend vec4 operator*(const vec4& vector, float scalar);
		friend float operator*(const vec4& left, const vec4& right);
		friend bool operator==(const vec4& left, const vec4& right);
		friend bool operator!=(const vec4& left, const vec4& right);

		vec4& operator+=(const vec4& other);
		vec4& operator-=(const vec4& other);
		vec4& operator*=(float scalar);
	};
}}