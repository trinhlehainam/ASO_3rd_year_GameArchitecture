#include "TransformComponent.h"

TransformComponent::TransformComponent(const std::shared_ptr<Entity>& owner, const vec2f& pos):
	IComponent(owner),
	Pos(pos),
	Scale(1.0f),
	Angle(0.0f)
{
}

TransformComponent::TransformComponent(const std::shared_ptr<Entity>& owner, const vec2f& pos, float scale, float angle):
	IComponent(owner),
	Pos(pos),
	Scale(scale), Angle(angle)
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::Init()
{
}

void TransformComponent::Update(float deltaTime_s)
{

}

void TransformComponent::Render()
{
}
