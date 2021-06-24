#include "Triangle.h"

#include <cmath>
#include <algorithm>

#include <DxLib.h>

#ifdef max 
#undef max
#endif

#ifdef min 
#undef min
#endif

Triangle::Triangle(vec2f a, vec2f b, vec2f c, unsigned int color) :P{ a,b,c }, IShape(IShape::TYPE::TRIANGLE, color)
{
}

Triangle::Triangle(vec2f a, vec2f b, vec2f c, vec2f speed, unsigned int color) : P{ a,b,c }, IShape(IShape::TYPE::TRIANGLE, color)
{
	Speed = speed;
}

void Triangle::Draw()
{
	DxLib::DrawTriangleAA(P[0].x, P[0].y, P[1].x, P[1].y, P[2].x, P[2].y, Color, 1);
}

void Triangle::Draw(float scale)
{
	DxLib::DrawTriangleAA(P[0].x, P[0].y, P[1].x, P[1].y, P[2].x, P[2].y, Color, 1);
}

bool Triangle::ConstrainPosition(float width, float height)
{
	vec2f maxVec{ std::max({ P[0].x,P[1].x,P[2].x }),std::max({ P[0].y,P[1].y,P[2].y }) };
	vec2f minVec{ std::min({ P[0].x,P[1].x,P[2].x }),std::min({ P[0].y,P[1].y,P[2].y }) };

	vec2f n{};
	vec2f offset{};
	if (minVec.x <= 0.0f)
	{
		n = vec2f{ 1.0f,0.0f };
		offset.x = 0.0f - minVec.x;
	}
	else if (minVec.y <= 0.0f)
	{
		n = vec2f(0.0f, 1.0f);
		offset.y = 0.0f - minVec.y;
	}
	else if (maxVec.x >= width)
	{
		n = vec2f(-1.0f, 0.0f);
		offset.x = width - maxVec.x;
	}
	else if (maxVec.y >= height)
	{
		n = vec2f(0.0f, -1.0f);
		offset.y = height - maxVec.y;
	}

	if (n == 0.0f) return false;
	Speed = reflectionVec(Speed, n);

	for (auto& point : P)
		point += offset;

	return true;
}

void Triangle::Update(float deltaTime_s)
{
	for (auto& point : P)
		point += Speed * deltaTime_s;
}

void Triangle::SpecialAction(std::vector<std::unique_ptr<IShape>>& container)
{
	Color = 0xffd700;
	Speed = -Speed;
	for (auto& point : P)
		point += Speed * 0.05f;
}
