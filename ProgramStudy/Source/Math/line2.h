#pragma once
#include "vec2.h"

struct line2
{
	line2();
	line2(const vec2f& base, const vec2f& dir);
	line2(const line2& other);
	line2(line2&& other) noexcept = default;
	line2& operator = (const line2& other);
	line2& operator = (line2&& other) noexcept = default;

	vec2f base;
	vec2f dir;
};



