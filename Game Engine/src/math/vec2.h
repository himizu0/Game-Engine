#pragma once
#include <iostream>

namespace engine { namespace math {
	struct vec2 {
		float x, y;

		vec2(float x, float y);

		friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
		friend vec2 operator+(const vec2& left, const vec2& right);
		friend vec2 operator-(const vec2& left, const vec2& right);
		friend vec2 operator*(float scalar, const vec2& vector);
		friend vec2 operator*(const vec2& vector, float scalar);
		friend float operator*(const vec2& left, const vec2& right);
		friend bool operator==(const vec2& left, const vec2& right);
		friend bool operator!=(const vec2& left, const vec2& right);

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(float scalar);
	};
} }