#include "vec4.h"

namespace engine { namespace math {
	vec4::vec4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w) {
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& vector) {
		return stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
	}

	vec4 operator+(const vec4& left, const vec4& right) {
		return vec4(
			left.x + right.x,
			left.y + right.y,
			left.z + right.z,
			left.w + right.w
		);
	}

	vec4 operator-(const vec4& left, const vec4& right) {
		return vec4(
			left.x - right.x,
			left.y - right.y,
			left.z - right.z,
			left.w - right.w
		);
	}

	vec4 operator*(float scalar, const vec4& vector) {
		return vec4(
			scalar * vector.x,
			scalar * vector.y,
			scalar * vector.z,
			scalar * vector.w
		);
	}

	vec4 operator*(const vec4& vector, float scalar) {
		return vec4(
			scalar * vector.x,
			scalar * vector.y,
			scalar * vector.z,
			scalar * vector.w
		);
	}

	float operator*(const vec4& left, const vec4& right) {
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}

	bool operator==(const vec4& left, const vec4& right) {
		return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
	}

	bool operator!=(const vec4& left, const vec4& right) {
		return !(left == right);
	}

	vec4& vec4::operator+=(const vec4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	vec4& vec4::operator-=(const vec4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	vec4& vec4::operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w += scalar;

		return *this;
	}
}}