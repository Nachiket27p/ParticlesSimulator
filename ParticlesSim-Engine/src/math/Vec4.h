#pragma once
#include <iostream>

namespace particlesSimulator {
	namespace math {

		struct vec4 {
			float x, y, z, w;

			vec4();
			vec4(const float& x, const float& y, const float& z, const float& w);

			vec4& add(const vec4& other);
			vec4& subtract(const vec4& other);
			vec4& multiply(const vec4& other);
			vec4& divide(const vec4& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
			friend vec4& operator+(vec4 vector, const vec4& other);
			friend vec4& operator-(vec4 vector, const vec4& other);
			friend vec4& operator*(vec4 vector, const vec4& other);
			friend vec4& operator/(vec4 vector, const vec4& other);

			vec4& operator+=(const vec4& other);
			vec4& operator-=(const vec4& other);
			vec4& operator*=(const vec4& other);
			vec4& operator/=(const vec4& other);

			bool operator==(const vec4& other);
			bool operator!=(const vec4& other);

			float& operator[](int idx);
		};
	}
}
