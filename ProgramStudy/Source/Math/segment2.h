#pragma once
#include "vec2.h"

struct segment2
{
	segment2();
	segment2(const vec2f& a, const vec2f& b);
	segment2(const segment2& other);
	segment2(segment2&& other) noexcept = default;
	segment2& operator = (const segment2& other);
	segment2& operator = (segment2&& other) noexcept = default;

	vec2f a, b;
};

