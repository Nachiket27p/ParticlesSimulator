#include "Vec2.h"

namespace particlesSimulator { namespace math {

	particlesSimulator::math::vec2::vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	particlesSimulator::math::vec2::vec2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	vec2& particlesSimulator::math::vec2::add(const vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	vec2& particlesSimulator::math::vec2::subtract(const vec2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	vec2& particlesSimulator::math::vec2::multiply(const vec2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	vec2& particlesSimulator::math::vec2::divide(const vec2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	vec2& vec2::operator+=(const vec2& other)
	{
		return this->add(other);
	}

	vec2& vec2::operator-=(const vec2& other)
	{
		return this->subtract(other);
	}

	vec2& vec2::operator*=(const vec2& other)
	{
		return this->multiply(other);
	}

	vec2& vec2::operator/=(const vec2& other)
	{
		return this->divide(other);
	}

	bool vec2::operator==(const vec2& other)
	{
		return (this->x == other.x && this->y == other.y);
	}

	bool vec2::operator!=(const vec2& other)
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& vector)
	{
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

	vec2& operator+(vec2 vector, const vec2& other)
	{
		return vector.add(other);
	}

	vec2& operator-(vec2 vector, const vec2& other)
	{
		return vector.subtract(other);
	}

	vec2& operator*(vec2 vector, const vec2& other)
	{
		return vector.multiply(other);
	}

	vec2& operator/(vec2 vector, const vec2& other)
	{
		return vector.divide(other);
	}

}}

