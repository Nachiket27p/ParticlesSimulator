#include "vec3.h"

namespace particlesSimulator { namespace math {

	particlesSimulator::math::vec3::vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	particlesSimulator::math::vec3::vec3(const float& x, const float& y, const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3& particlesSimulator::math::vec3::add(const vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	vec3& particlesSimulator::math::vec3::subtract(const vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	vec3& particlesSimulator::math::vec3::multiply(const vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	vec3& particlesSimulator::math::vec3::divide(const vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	vec3& vec3::operator+=(const vec3& other)
	{
		return this->add(other);
	}

	vec3& vec3::operator-=(const vec3& other)
	{
		return this->subtract(other);
	}

	vec3& vec3::operator*=(const vec3& other)
	{
		return this->multiply(other);
	}

	vec3& vec3::operator/=(const vec3& other)
	{
		return this->divide(other);
	}

	bool vec3::operator==(const vec3& other)
	{
		return (this->x == other.x && this->y == other.y);
	}

	bool vec3::operator!=(const vec3& other)
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector)
	{
		stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

	vec3& operator+(vec3 vector, const vec3& other)
	{
		return vector.add(other);
	}

	vec3& operator-(vec3 vector, const vec3& other)
	{
		return vector.subtract(other);
	}

	vec3& operator*(vec3 vector, const vec3& other)
	{
		return vector.multiply(other);
	}

	vec3& operator/(vec3 vector, const vec3& other)
	{
		return vector.divide(other);
	}

}}

