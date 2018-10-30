#include "mat4.h"
#include "mathUtility.h"

#define SHUFFLE_PARAM(x, y, z, w) \
	((x) | ((y) << 2) | ((z) << 4) | ((z) << 6))

#define _mm_replicate_x_ps(v) \
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(0, 0, 0, 0))

#define _mm_replicate_y_ps(v) \
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(1, 1, 1, 1))

#define _mm_replicate_z_ps(v) \
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(2, 2, 2, 2))

#define _mm_replicate_w_ps(v) \
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(3, 3, 3, 3))


namespace engine { namespace math {

	mat4::mat4(float diagonal) {
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				elements[i][j] = (i == j) * diagonal;
	}

	mat4 mat4::identity() {
		return mat4(1);
	}

	mat4 mat4::translate(const vec3& translation) {
		mat4 result(1);

		result(0, 3) = translation.x;
		result(1, 3) = translation.y;
		result(2, 3) = translation.z;

		return result;
	}

	mat4 mat4::rotate(float angle, const vec3& axis) {
		mat4 result(1);

		const float r = toRadians(angle);
		const float c = cos(r);
		const float s = sin(r);
		const float omc = 1.0f - c;

		const vec3 a = normalize(axis);
		const float& x = a.x;
		const float& y = a.y;
		const float& z = a.z;

		result(0, 0) = c + x * x * omc;
		result(1, 0) = y * x * omc + z * s;
		result(2, 0) = z * x * omc - y * s;

		result(0, 1) = x * y * omc - z * s;
		result(1, 1) = c + y * y * omc;
		result(2, 1) = z * y * omc + x * s;

		result(0, 2) = x * z * omc + y * s;
		result(1, 2) = y * z * omc - x * s;
		result(2, 2) = c + z * z * omc;

		return result;
	}

	mat4 mat4::scale(const vec3& scale) {
		mat4 result(1);

		result(0, 0) = scale.x;
		result(1, 1) = scale.y;
		result(2, 2) = scale.z;

		return result;
	}

	mat4 mat4::scale(float scale) {
		mat4 result(1);

		result(0, 0) = scale;
		result(1, 1) = scale;
		result(2, 2) = scale;

		return result;
	}

	mat4 mat4::orthographic(float left, float right, float top, float bottom, float near, float far) {
		mat4 result(1);

		result(0, 0) = 2.0f / (right - left);
		result(1, 1) = 2.0f / (top - bottom);
		result(2, 2) = 2.0f / (near - far);

		result(0, 3) = (left + right) / (left - right);
		result(1, 3) = (bottom + top) / (bottom - top);
		result(2, 3) = (near + far) / (near - far);

		return result;
	}

	mat4 mat4::perspective(float fov, float aspect, float near, float far) {
		mat4 result(0);

		const float q = 1.0f / tan(math::toRadians(fov) / 2.0f);

		result(0, 0) = q / aspect;
		result(1, 1) = q;
		result(2, 2) = (near + far) / (near - far);
		result(3, 2) = -1.0f;
		result(2, 3) = 2.0f * near * far / (near - far);

		return result;
	}

	mat4 mat4::lookAt(const vec3& eye, const vec3& center, const vec3& up) {
		mat4 result(1);

		const vec3 f(normalize(center - eye));
		const vec3 s(normalize(cross(f, up)));
		const vec3 u(cross(s, f));

		result(0, 0) = s.x;
		result(0, 1) = s.y;
		result(0, 2) = s.z;

		result(1, 0) = u.x;
		result(1, 1) = u.y;
		result(1, 2) = u.z;

		result(2, 0) = -f.x;
		result(2, 1) = -f.y;
		result(2, 2) = -f.z;

		result(0, 3) = -dot(s, eye);
		result(1, 3) = -dot(u, eye);
		result(2, 3) = dot(f, eye);

		return result;
	}

	mat4 transpose(const mat4& matrix) {
		mat4 result(1);

		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				result(i, j) = matrix(j, i);

		return result;
	}

	mat4 inverseTranspose(const mat4& matrix) {
		//TODO: Make this better! (to many flops) (zmmintrin)
		const float subFactor00 = matrix(2, 2) * matrix(3, 3) - matrix(3, 2) * matrix(2, 3);
		const float subFactor01 = matrix(2, 1) * matrix(3, 3) - matrix(3, 1) * matrix(2, 3);
		const float subFactor02 = matrix(2, 1) * matrix(3, 2) - matrix(3, 1) * matrix(2, 2);
		const float subFactor03 = matrix(2, 0) * matrix(3, 3) - matrix(3, 0) * matrix(2, 3);
		const float subFactor04 = matrix(2, 0) * matrix(3, 2) - matrix(3, 0) * matrix(2, 2);
		const float subFactor05 = matrix(2, 0) * matrix(3, 1) - matrix(3, 0) * matrix(2, 1);
		const float subFactor06 = matrix(1, 2) * matrix(3, 3) - matrix(3, 2) * matrix(1, 3);
		const float subFactor07 = matrix(1, 1) * matrix(3, 3) - matrix(3, 1) * matrix(1, 3);
		const float subFactor08 = matrix(1, 1) * matrix(3, 2) - matrix(3, 1) * matrix(1, 2);
		const float subFactor09 = matrix(1, 0) * matrix(3, 3) - matrix(3, 0) * matrix(1, 3);
		const float subFactor10 = matrix(1, 0) * matrix(3, 2) - matrix(3, 0) * matrix(1, 2);
		const float subFactor11 = matrix(1, 1) * matrix(3, 3) - matrix(3, 1) * matrix(1, 3);
		const float subFactor12 = matrix(1, 0) * matrix(3, 1) - matrix(3, 0) * matrix(1, 1);
		const float subFactor13 = matrix(1, 2) * matrix(2, 3) - matrix(2, 2) * matrix(1, 3);
		const float subFactor14 = matrix(1, 1) * matrix(2, 3) - matrix(2, 1) * matrix(1, 3);
		const float subFactor15 = matrix(1, 1) * matrix(2, 2) - matrix(2, 1) * matrix(1, 2);
		const float subFactor16 = matrix(1, 0) * matrix(2, 3) - matrix(2, 0) * matrix(1, 3);
		const float subFactor17 = matrix(1, 0) * matrix(2, 2) - matrix(2, 0) * matrix(1, 2);
		const float subFactor18 = matrix(1, 0) * matrix(2, 1) - matrix(2, 0) * matrix(1, 1);
								  
		mat4 result(0);
		result(0, 0) = +(matrix(1, 1) * subFactor00 - matrix(1, 2) * subFactor01 + matrix(1, 3) * subFactor02);
		result(0, 1) = -(matrix(1, 0) * subFactor00 - matrix(1, 2) * subFactor03 + matrix(1, 3) * subFactor04);
		result(0, 2) = +(matrix(1, 0) * subFactor01 - matrix(1, 1) * subFactor03 + matrix(1, 3) * subFactor05);
		result(0, 3) = -(matrix(1, 0) * subFactor02 - matrix(1, 1) * subFactor04 + matrix(1, 2) * subFactor05);
		
		result(1, 0) = -(matrix(0, 1) * subFactor00 - matrix(0, 2) * subFactor01 + matrix(0, 3) * subFactor02);
		result(1, 1) = +(matrix(0, 0) * subFactor00 - matrix(0, 2) * subFactor03 + matrix(0, 3) * subFactor04);
		result(1, 2) = -(matrix(0, 0) * subFactor01 - matrix(0, 1) * subFactor03 + matrix(0, 3) * subFactor05);
		result(1, 3) = +(matrix(0, 0) * subFactor02 - matrix(0, 1) * subFactor04 + matrix(0, 2) * subFactor05);
		
		result(2, 0) = +(matrix(0, 1) * subFactor06 - matrix(0, 2) * subFactor07 + matrix(0, 3) * subFactor08);
		result(2, 1) = -(matrix(0, 0) * subFactor06 - matrix(0, 2) * subFactor09 + matrix(0, 3) * subFactor10);
		result(2, 2) = +(matrix(0, 0) * subFactor11 - matrix(0, 1) * subFactor09 + matrix(0, 3) * subFactor12);
		result(2, 3) = -(matrix(0, 0) * subFactor08 - matrix(0, 1) * subFactor10 + matrix(0, 2) * subFactor12);
		
		result(3, 0) = -(matrix(0, 1) * subFactor13 - matrix(0, 2) * subFactor14 + matrix(0, 3) * subFactor15);
		result(3, 1) = +(matrix(0, 0) * subFactor13 - matrix(0, 2) * subFactor16 + matrix(0, 3) * subFactor17);
		result(3, 2) = -(matrix(0, 0) * subFactor14 - matrix(0, 1) * subFactor16 + matrix(0, 3) * subFactor18);
		result(3, 3) = +(matrix(0, 0) * subFactor15 - matrix(0, 1) * subFactor17 + matrix(0, 2) * subFactor18);
				   
		const float determinant =
			  matrix(0, 0) * result(0, 0)
			+ matrix(0, 1) * result(0, 1)
			+ matrix(0, 2) * result(0, 2)
			+ matrix(0, 3) * result(0, 3);

		result /= determinant;

		return result;
	}
	
	std::ostream& operator<<(std::ostream& stream, const mat4& matrix) {
		return stream << "row1: (" << matrix(0, 0) << ", " << matrix(0, 1) << ", " << matrix(0, 2) << ", " << matrix(0, 3) << ")" << std::endl
			<< "row2: (" << matrix(1, 0) << ", " << matrix(1, 1) << ", " << matrix(1, 2) << ", " << matrix(1, 3) << ")" << std::endl
			<< "row3: (" << matrix(2, 0) << ", " << matrix(2, 1) << ", " << matrix(2, 2) << ", " << matrix(2, 3) << ")" << std::endl
			<< "row4: (" << matrix(3, 0) << ", " << matrix(3, 1) << ", " << matrix(3, 2) << ", " << matrix(3, 3) << ")";
	}

	mat4 operator*(const mat4& left, const mat4& right) {
#ifdef UNION
		mat4 result;

		for (unsigned int i = 0; i < 4; i++) {
			result.columnRegisters[i] = _mm_mul_ps(_mm_replicate_x_ps(right.columnRegisters[i]), left.columnRegisters[0]);
			result.columnRegisters[i] = _mm_add_ps(result.columnRegisters[i], _mm_mul_ps(_mm_replicate_y_ps(right.columnRegisters[i]), left.columnRegisters[1]));
			result.columnRegisters[i] = _mm_add_ps(result.columnRegisters[i], _mm_mul_ps(_mm_replicate_z_ps(right.columnRegisters[i]), left.columnRegisters[2]));
			result.columnRegisters[i] = _mm_add_ps(result.columnRegisters[i], _mm_mul_ps(_mm_replicate_w_ps(right.columnRegisters[i]), left.columnRegisters[3]));
		}

		return result;
#else
		__m128 leftColumns[4];
		leftColumns[0] = _mm_load_ps(left.elements[0]);
		leftColumns[1] = _mm_load_ps(left.elements[1]);
		leftColumns[2] = _mm_load_ps(left.elements[2]);
		leftColumns[3] = _mm_load_ps(left.elements[3]);

		__m128 rightColumns[4];
		rightColumns[0] = _mm_load_ps(right.elements[0]);
		rightColumns[1] = _mm_load_ps(right.elements[1]);
		rightColumns[2] = _mm_load_ps(right.elements[2]);
		rightColumns[3] = _mm_load_ps(right.elements[3]);

		__m128 resultColumns[4];

		for (unsigned int i = 0; i < 4; i++) {
			resultColumns[i] = _mm_mul_ps(_mm_replicate_x_ps(rightColumns[i]), leftColumns[0]);
			resultColumns[i] = _mm_add_ps(resultColumns[i], _mm_mul_ps(_mm_replicate_y_ps(rightColumns[i]), leftColumns[1]));
			resultColumns[i] = _mm_add_ps(resultColumns[i], _mm_mul_ps(_mm_replicate_z_ps(rightColumns[i]), leftColumns[2]));
			resultColumns[i] = _mm_add_ps(resultColumns[i], _mm_mul_ps(_mm_replicate_w_ps(rightColumns[i]), leftColumns[3]));
		}

		mat4 result;
		_mm_store_ps(result.elements[0], resultColumns[0]);
		_mm_store_ps(result.elements[1], resultColumns[1]);
		_mm_store_ps(result.elements[2], resultColumns[2]);
		_mm_store_ps(result.elements[3], resultColumns[3]);
		return result;
#endif
	}

	vec4 operator*(const mat4& matrix, const vec4& vector) {
#ifdef UNION
		__m128 vectorRegister = _mm_load_ps(&vector.x);
		__m128 resultRegister;

		resultRegister = _mm_mul_ps(_mm_replicate_x_ps(vectorRegister), matrix.columnRegisters[0]);
		resultRegister = _mm_add_ps(resultRegister, _mm_mul_ps(_mm_replicate_y_ps(vectorRegister), matrix.columnRegisters[1]));
		resultRegister = _mm_add_ps(resultRegister, _mm_mul_ps(_mm_replicate_z_ps(vectorRegister), matrix.columnRegisters[2]));
		resultRegister = _mm_add_ps(resultRegister, _mm_mul_ps(_mm_replicate_w_ps(vectorRegister), matrix.columnRegisters[3]));

		vec4 result;
		_mm_store_ps(&result.x, resultRegister);
		return result;
#else
		__m128 vectorRegister = _mm_load_ps(&vector.x);

		__m128 matrixColumns[4];
		matrixColumns[0] = _mm_load_ps(&matrix(0, 0));
		matrixColumns[1] = _mm_load_ps(&matrix(0, 1));
		matrixColumns[2] = _mm_load_ps(&matrix(0, 2));
		matrixColumns[3] = _mm_load_ps(&matrix(0, 3));

		__m128 resultRegister;

		resultRegister = _mm_mul_ps(_mm_replicate_x_ps(vectorRegister), matrixColumns[0]);
		resultRegister = _mm_add_ps(resultRegister, _mm_mul_ps(_mm_replicate_y_ps(vectorRegister), matrixColumns[1]));
		resultRegister = _mm_add_ps(resultRegister, _mm_mul_ps(_mm_replicate_z_ps(vectorRegister), matrixColumns[2]));
		resultRegister = _mm_add_ps(resultRegister, _mm_mul_ps(_mm_replicate_w_ps(vectorRegister), matrixColumns[3]));

		vec4 result;
		_mm_store_ps(&result.x, resultRegister);
		return result;
#endif
	}

	vec3 operator*(const mat4& matrix, const vec3& vector) {
		return vec3(
			matrix(0, 0) * vector.x + matrix(0, 1) * vector.y + matrix(0, 2) * vector.z + matrix(0, 3),
			matrix(1, 0) * vector.x + matrix(1, 1) * vector.y + matrix(1, 2) * vector.z + matrix(1, 3),
			matrix(2, 0) * vector.x + matrix(2, 1) * vector.y + matrix(2, 2) * vector.z + matrix(2, 3)
		);
	}

	mat4& mat4::wipeTranslation() {
		(*this)(0, 3) = 0;
		(*this)(1, 3) = 0;
		(*this)(2, 3) = 0;

		return *this;
	}
	
	float& mat4::operator()(unsigned int row, unsigned int column) {
		return elements[column][row];
	}

	const float& mat4::operator()(unsigned int row, unsigned int column) const {
		return elements[column][row];
	}

	mat4& mat4::operator/=(float scalar) {
		for (unsigned int i = 0; i < 4; i++)
			for (unsigned int j = 0; j < 4; j++)
				elements[i][j] /= scalar;

		return *this;
	}
} }