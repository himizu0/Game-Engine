#pragma once
#include <iostream>

namespace engine { namespace math {
	struct vec3 {
		float x, y, z;

		vec3(float x, float y, float z);

		friend float magnitude(const vec3& vector);
		friend vec3 normalize(const vec3& vector);
		friend float dot(const vec3& lett, const vec3& right);
		friend vec3 cross(const vec3& left, const vec3& right);

		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
		friend vec3 operator+(const vec3& left, const vec3& right);
		friend vec3 operator-(const vec3& left, const vec3& right);
		friend vec3 operator*(float scalar, const vec3& vector);
		friend vec3 operator*(const vec3& vector, float scalar);
		friend vec3 operator*(const vec3& left, const vec3& right);
		friend bool operator==(const vec3& left, const vec3& right);
		friend bool operator!=(const vec3& left, const vec3& right);

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator*=(float scalar);
	};
}}