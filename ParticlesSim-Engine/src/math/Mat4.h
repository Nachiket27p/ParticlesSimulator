#pragma once

#include "Math.h"
#include "Vec3.h"

namespace particlesSimulator {
	namespace math {

		struct mat4 {

			union {
				float elements[4 * 4] = {};
				vec4 colums[4];
			};

			mat4() {};
			mat4(const float diag);

			mat4& multiply(const mat4& other);

			static mat4 identity();

			static mat4 orthographic(const float left, const float right,
				const float bottom, const float top,
				const float near, const float far);

			static mat4 perspective(const float fov, const float aspectRatio,
				const float near, const float far);

			static mat4 translate(const vec3& translation);

			static mat4 scale(const vec3& scale);

			static mat4 rotate(float angle, const vec3& axis);

			friend mat4 operator*(mat4 matrix, const mat4& other);
			mat4& operator*=(const mat4& other);

			vec4& operator[](int col);

		};
	}
}
