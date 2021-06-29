#include "Circle.h"

#include <algorithm>

Circle::Circle():Center(vec2f{}), Radius(0.0f) {}

Circle::Circle(const vec2f& center, float radius) : Center(center), Radius(radius) {}

void Circle::operator=(const Circle& other)
{
	Center = other.Center;
	Radius = other.Radius;
}

void Circle::operator=(Circle&& other) noexcept
{
	std::swap(Center, other.Center);
	std::swap(Radius, other.Radius);
}

Circle::~Circle() = default;
