#include "Cloud.h"

#include <DxLib.h>

#include "../Math/MathHelper.h"

#include "Circle.h"

Cloud::Cloud(vec2f pos, vec2f speed):IShape(IShape::TYPE::CLOUD, pos, speed, 0xFFFFFFFF)
{
	auto radius = MathHelper::randf(50.0f,100.0f);
	vec2f startPos{ pos.x - radius, pos.y };
	for (int i = 0; i < 3; ++i)
	{
		Elements.push_back(std::make_unique<Circle>(startPos, speed, radius, Color));
		radius = MathHelper::randf(50.0f, 100.0f);
		startPos.x += radius;
	}
}

Cloud::~Cloud()
{
}

bool Cloud::ConstrainPosition(float width, float height)
{
	for (const auto& elem : Elements)
	{
		if (elem->ConstrainPosition(width, height))
		{
			Speed = elem->Speed;
			Color = DxLib::GetColor(rand() * 255, rand() * 255, rand() * 255);
			for (const auto& element : Elements)
				element->Color = Color;
			return true;
		}
	}

	return false;
}

void Cloud::Update(float deltaTime_s)
{
	for (const auto& element : Elements)
		element->Speed = Speed;

	for (const auto& element : Elements)
		element->Update(deltaTime_s);
}

void Cloud::SpecialAction(std::vector<std::unique_ptr<IShape>>& container)
{
}

void Cloud::Draw()
{
	for (const auto& element : Elements)
		element->Draw();
}

void Cloud::Draw(float scale)
{
}
