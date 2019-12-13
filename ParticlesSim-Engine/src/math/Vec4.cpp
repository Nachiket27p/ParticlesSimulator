#include "vec4.h"

namespace particlesSimulator {
	namespace math {

		particlesSimulator::math::vec4::vec4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		particlesSimulator::math::vec4::vec4(const float& x, const float& y, const float& z, const float& w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4& particlesSimulator::math::vec4::add(const vec4& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		vec4& particlesSimulator::math::vec4::subtract(const vec4& other)
		{
			x -= other.x;
			y -= other.y;
			w -= other.w;
			z -= other.z;

			return *this;
		}

		vec4& particlesSimulator::math::vec4::multiply(const vec4& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;

			return *this;
		}

		vec4& particlesSimulator::math::vec4::divide(const vec4& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;

			return *this;
		}

		vec4& vec4::operator+=(const vec4& other)
		{
			return this->add(other);
		}

		vec4& vec4::operator-=(const vec4& other)
		{
			return this->subtract(other);
		}

		vec4& vec4::operator*=(const vec4& other)
		{
			return this->multiply(other);
		}

		vec4& vec4::operator/=(const vec4& other)
		{
			return this->divide(other);
		}

		bool vec4::operator==(const vec4& other)
		{
			return (this->x == other.x && this->y == other.y);
		}

		bool vec4::operator!=(const vec4& other)
		{
			return !(*this == other);
		}

		float& vec4::operator[](int idx)
		{
			switch (idx)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			}
		}

		std::ostream& operator<<(std::ostream& stream, const vec4& vector)
		{
			stream << "vec4: (" << vector.x << ", " << vector.y << ", "
				<< vector.z << ", " << vector.w << ")";
			return stream;
		}

		vec4& operator+(vec4 vector, const vec4& other)
		{
			return vector.add(other);
		}

		vec4& operator-(vec4 vector, const vec4& other)
		{
			return vector.subtract(other);
		}

		vec4& operator*(vec4 vector, const vec4& other)
		{
			return vector.multiply(other);
		}

		vec4& operator/(vec4 vector, const vec4& other)
		{
			return vector.divide(other);
		}

	}
}

