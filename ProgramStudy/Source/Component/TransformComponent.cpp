#include "TransformComponent.h"

TransformComponent::TransformComponent(const std::shared_ptr<Entity>& owner) :IComponent(owner), Scale{ 1.0f,1.0f }, Rotation(0.0f)
{
}

TransformComponent::TransformComponent(const std::shared_ptr<Entity>& owner, const vec2f& pos):
	IComponent(owner),
	Pos(pos),
	Scale{1.0f,1.0f},Rotation(0.0f)
{
}

TransformComponent::TransformComponent(const std::shared_ptr<Entity>& owner, const vec2f& pos, vec2f scale, float rotation):
	IComponent(owner),
	Pos(pos),
	Scale(scale), Rotation(rotation)
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
