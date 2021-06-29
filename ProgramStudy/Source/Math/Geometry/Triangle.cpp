#include "Triangle.h"

#include <algorithm>

Triangle::Triangle() = default;

Triangle::Triangle(vec2f a, vec2f b, vec2f c) :Point{ a,b,c }
{
}

void Triangle::operator=(const Triangle& other)
{
	Point = other.Point;
}

void Triangle::operator=(Triangle&& other) noexcept
{
	std::swap(Point, other.Point);
}

Triangle::~Triangle() = default;
