#include "vec3.h"

namespace engine { namespace math {
	vec3::vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float magnitude(const vec3& vector) {
		return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}

	vec3 normalize(const vec3& vector) {
		const float oom = 1.0f / magnitude(vector);

		return oom * vector;
	}

	float dot(const vec3& left, const vec3& right) {
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	vec3 cross(const vec3& left, const vec3& right) {
		return vec3(
			left.y * right.z - left.z * right.y,		
			left.z * right.x - left.x * right.z,		
			left.x * right.y - left.y * right.x	
		);
	}

	vec3& vec3::normalize() {
		const float oom = 1.0f / magnitude(*this);

		x /= oom;
		y /= oom;
		z / oom;

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
		return stream << "(" << vector.x << "," << vector.y << ", " << vector.z << ")";
	}

	vec3 operator+(const vec3& left, const vec3& right) {
		return vec3(
			left.x + right.x,
			left.y + right.y,
			left.z + right.z
		);
	}

	vec3 operator-(const vec3& left, const vec3& right) {
		return vec3(
			left.x - right.x,
			left.y - right.y,
			left.z - right.z
		);
	}

	vec3 operator*(float scalar, const vec3& vector) {
		return vec3(
			scalar * vector.x,
			scalar * vector.y,
			scalar * vector.z
		);
	}

	vec3 operator*(const vec3& vector, float scalar) {
		return vec3(
			scalar * vector.x,
			scalar * vector.y,
			scalar * vector.z
		);
	}

	vec3 operator*(const vec3& left, const vec3& right) {
		return vec3(
			left.x * right.x, 
			left.y * right.y, 
			left.z * right.z
		);
	}

	bool operator==(const vec3& left, const vec3& right) {
		return left.x == right.x && left.y == right.y && left.z == right.z;
	}

	bool operator!=(const vec3& left, const vec3& right) {
		return !(left == right);
	}


	vec3 vec3::operator-() {
		return vec3{
			-x,
			-y,
			-z
		};
	}

	vec3& vec3::operator+=(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	vec3& vec3::operator-=(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	vec3& vec3::operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}
}}