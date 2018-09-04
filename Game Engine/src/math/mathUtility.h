#pragma once

#define UNION

#define PI 3.14159265359
#define E  2.71828182845

namespace engine { namespace math {
	inline float toRadians(float degrees) {
		return (PI / 180.0f * degrees);
	}
} }