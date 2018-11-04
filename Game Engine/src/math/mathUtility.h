#pragma once

#define UNION

#define pi 3.14159265359f
#define e  2.71828182845f

namespace engine { namespace math {
	inline float toRadians(float degrees) {
		return ((pi / 180.0f) * degrees);
	}
} }