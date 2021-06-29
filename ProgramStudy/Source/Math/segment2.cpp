#include "segment2.h"

segment2::segment2() = default;

segment2::segment2(const vec2f& a, const vec2f& b):a(a),b(b)
{
}

segment2::segment2(const segment2&) = default;

//segment2::segment2(segment2&&) noexcept = default;

segment2& segment2::operator=(const segment2&) = default;

//segment2& segment2::operator=(segment2&&) noexcept = default;
