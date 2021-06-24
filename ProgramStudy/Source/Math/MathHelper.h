#pragma once

namespace MathHelper
{
	// Floating point numbers are rarely exact the same.
	// -> Two floating point numbers are equal when they are in range of below bias
	extern const float kBiasF;
	extern const double kBiasD;
	//

	extern const float kMsToSecond;
}

namespace MathHelper
{
	float randf(float num);
	float randf(float min, float max);
	template<typename T> bool isEqual(T a, T b);
	template<typename T> T clamp(T value, T min, T max);
};

// Value of 2 points in one axis
struct range
{
	float min, max;
};

class IShape;
class AABB;
class Circle;
class Triangle;
struct line2;
struct segment2;

namespace MathHelper
{
	bool isEquivalent(const line2& a, const line2& b);
	// Check two points of segment line on the same side that seperated by line
	bool isOnSameSide(const line2& l, const segment2& s);

	bool isOverlap(float minA, float maxA, float minB, float maxB);
	bool isOverlap(const range& a, const range& b);
	bool isOverlap(const line2& a, const line2& b);
	bool isOverlap(const segment2& a, const segment2& b);

	bool isOverlap(const Circle& a, const Circle& b);
	bool isOverlap(const Circle& cir, const AABB& rect);
	bool isOverlap(const AABB& rect, const Circle& cir);
	bool isOverlap(const AABB& a, const AABB& b);
	bool isOverlap(const Triangle& a, const Triangle& b);
}

