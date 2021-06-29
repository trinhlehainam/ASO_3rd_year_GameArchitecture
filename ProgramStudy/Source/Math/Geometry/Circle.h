#pragma once
#include "../vec2.h"

struct Circle
{
    Circle();
    Circle(const vec2f& center, float radius);
    Circle(const Circle&) = default;
    Circle(Circle&&) noexcept = default;
    void operator = (const Circle&);
    void operator = (Circle&&) noexcept;
    ~Circle();

    vec2f Center;
    float Radius;
};

