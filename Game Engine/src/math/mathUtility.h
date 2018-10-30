#pragma once

#define UNION

#define PI 3.14159265359f
#define TWOPI 2.0f * PI
#define PIHALF 0.5f * PI
#define E  2.71828182845f

namespace engine { namespace math {
	inline float toRadians(float degrees) {
		return ((PI / 180.0f) * degrees);
	}
} }