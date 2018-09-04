#include "vec2.h"

namespace engine { namespace math {
	vec2::vec2(float x, float y)
		: x(x), y(y) {
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& vector) {
		return stream << "(" << vector.x << "," << vector.y << ")";
	}

	vec2 operator+(const vec2& left, const vec2& right) {
		return vec2(
			left.x + right.x,
			left.y + right.y
		);
	}

	vec2 operator-(const vec2& left, const vec2& right) {
		return vec2(
			left.x - right.x,
			left.y - right.y
		);
	}

	vec2 operator*(float scalar, const vec2& vector) {
		return vec2(
			scalar * vector.x,
			scalar * vector.y
		);
	}

	vec2 operator*(const vec2& vector, float scalar) {
		return vec2(
			scalar * vector.x,
			scalar * vector.y
		);
	}

	float operator*(const vec2& left, const vec2& right) {
		return left.x * right.x + left.y * right.y;
	}

	bool operator==(const vec2& left, const vec2& right) {
		return left.x == right.x && left.y == right.y;
	}

	bool operator!=(const vec2& left, const vec2& right) {
		return !(left == right);
	}

	vec2& vec2::operator+=(const vec2& other) {
		x += other.x;
		y += other.y;

		return *this;
	}

	vec2& vec2::operator-=(const vec2& other) {
		x -= other.x;
		y -= other.y;

		return *this;
	}

	vec2& vec2::operator*=(float scalar) {
		x *= scalar;
		y *= scalar;

		return *this;
	}
}}