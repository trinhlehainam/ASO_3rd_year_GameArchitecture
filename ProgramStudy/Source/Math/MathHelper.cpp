#include "MathHelper.h"

#include <cmath>
#include <algorithm>
#include <array>

#include "../Math/line2.h"
#include "../Math/segment2.h"
#include "../Geometry/AABB.h"
#include "../Geometry/Circle.h"
#include "../Geometry/Triangle.h"

namespace MathHelper
{
	const float kBiasF = 0.001f;
	const double kBiasD = 0.0001;

	const float kMsToSecond = 1 / 1000.0f;
}

namespace MathHelper
{
	float randf(float num)
	{
		return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / num));
	}

	float randf(float min, float max)
	{
		return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}

	template<typename T>
	bool isEqual(T a, T b)
	{
		return a == b;
	}

	template<typename T>
	T clamp(T value, T min, T max)
	{
		return std::max(min,std::min(max, value));
	}

#pragma region Specialization
	template <>
	bool isEqual(float a, float b)
	{
		return std::fabsf(a - b) <= kBiasF;
	}

	template <>
	bool isEqual(double a, double b)
	{
		return std::abs(a - b) <= kBiasD;
	}

#pragma endregion


#pragma region InstantiateFuncTemplate
	template bool isEqual(int, int);
	template bool isEqual(unsigned int, unsigned int);
	template bool isEqual(short, short);

	template float clamp(float, float, float);
	template double clamp(double, double, double);
	
#pragma endregion
};

namespace MathHelper
{
	bool isEquivalent(const line2& a, const line2& b)
	{
		if (!isParallelVec(a.dir, b.dir))
			return false;

		return isParallelVec(a.base - b.base, a.dir);
	}

	bool isOnSameSide(const line2& l, const segment2& s)
	{
		auto orthoVec = orthogonalVec(l.dir);
		return dot(orthoVec, s.a - l.base) * dot(orthoVec, s.b - l.base) > 0.0f;
	}

	range projectSegmentRange(const segment2& s, const vec2f& onto)
	{
		auto ontoUnit = onto / std::sqrt(dot(onto,onto));

		range r;
		r.min = dot(s.a, onto);
		r.max = dot(s.a, onto);
		std::sort(&r.min, &r.max);

		return r;
	}

	bool isOverlap(const Circle& a, const Circle& b)
	{
		auto d = a.Pos - b.Pos;
		auto r = a.Radius + b.Radius;
		return d * d <= r * r;
	}

	bool isOverlap(const Circle& cir, const AABB& rect)
	{
		auto closet_point = clampVec(cir.Pos, rect.Pos, rect.Pos + rect.Size);
		auto d = closet_point - cir.Pos;
		return d * d <= cir.Radius * cir.Radius;
	}

	bool isOverlap(const AABB& rect, const Circle& cir)
	{
		return isOverlap(cir, rect);
	}

	bool isOverlap(const AABB& a, const AABB& b)
	{
		auto aLeft = a.Pos.x;
		auto aRight = a.Pos.x + a.Size.x;
		auto aTop = a.Pos.y;
		auto aBottom = a.Pos.y + a.Size.y;

		auto bLeft = b.Pos.x;
		auto bRight = b.Pos.x + b.Size.x;
		auto bTop = b.Pos.y;
		auto bBottom = b.Pos.y + b.Size.y;

		return isOverlap(aLeft, aRight, bLeft, bRight) && isOverlap(aTop, aBottom, bTop, bBottom);
	}

	bool isOverlap(const Triangle& a, const Triangle& b)
	{
		// Create segments from triangle
		std::array<segment2, 3> a_segments, b_segments;
		for (int i = 0; i < 3; ++i)
		{
			auto i_next = (i + 1) % 3;
			a_segments[i].a = a.P[i];
			a_segments[i].b = a.P[i_next];
		}
		for (int i = 0; i < 3; ++i)
		{
			auto i_next = (i + 1) % 3;
			b_segments[i].a = b.P[i];
			b_segments[i].b = b.P[i_next];
		}
		//

		for (const auto& a_segment : a_segments)
		{
			for (const auto& b_segment : b_segments)
			{
				if (isOverlap(a_segment, b_segment))
					return true;
			}
		}

		return false;
	}

	bool isOverlap(const line2& a, const line2& b)
	{
		if (!isParallelVec(a.dir, b.dir))
			return true;
		return isEquivalent(a, b);
	}

	bool isOverlap(const segment2& a, const segment2& b)
	{
		line2 axisA{ a.a, a.b - a.a };
		if(isOnSameSide(axisA, b))
			return false;
		
		line2 axisB{ b.a, b.b - b.a };
		if (isOnSameSide(axisB, a))
			return false;

		if (!isParallelVec(axisA.dir, axisB.dir))
			return true;

		return isOverlap(projectSegmentRange(a, axisA.dir), projectSegmentRange(b, axisA.dir));
	}

	bool isOverlap(float minA, float maxA, float minB, float maxB)
	{
		return maxA >= minB && maxA <= maxB;
	}

	bool isOverlap(const range& a, const range& b)
	{
		return isOverlap(a.min, a.max, b.min, b.max);
	}

}
