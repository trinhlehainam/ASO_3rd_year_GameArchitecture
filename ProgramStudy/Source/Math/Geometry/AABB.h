#pragma once
#include "../vec2.h"

template <typename T>
struct AABB
{
	AABB();
	AABB(const vec2<T>& pos, const vec2<T>& size);
	AABB(const AABB&) = default;
	AABB(AABB&&) noexcept = default;
	void operator = (const AABB&);
	void operator = (AABB&&) noexcept;
	~AABB();

	vec2<T> Origin;
	vec2<T> Size;
};

using AABBi = AABB<int>;
using AABBf = AABB<float>;
using AABBd = AABB<double>;

