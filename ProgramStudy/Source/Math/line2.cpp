#include "line2.h"

line2::line2() = default;

line2::line2(const vec2f& base, const vec2f& dir):base(base),dir(dir)
{
}

line2::line2(const line2&) = default;

//line2::line2(line2&&) noexcept = default;

line2& line2::operator=(const line2&) = default;

//line2& line2::operator=(line2&&) noexcept = default;
