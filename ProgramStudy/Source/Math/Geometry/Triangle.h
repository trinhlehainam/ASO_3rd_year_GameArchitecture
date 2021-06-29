#pragma once
#include <array>

#include "../vec2.h"

struct Triangle
{
	Triangle();
	Triangle(vec2f a, vec2f b, vec2f c);
	Triangle(const Triangle&) = default;
	Triangle(Triangle&&) noexcept = default;
	void operator = (const Triangle&);
	void operator = (Triangle&&) noexcept;
	~Triangle();

	std::array<vec2f,3> Point;
};

