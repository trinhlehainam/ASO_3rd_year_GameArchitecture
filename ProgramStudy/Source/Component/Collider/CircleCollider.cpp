#include "CircleCollider.h"

#include <DxLib.h>

#include "../../GameObject/Entity.h"
#include "../TransformComponent.h"

CircleCollider::CircleCollider(const std::shared_ptr<Entity>& owner):ICollider(owner)
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::SetCenterPos(const vec2f& pos)
{
	m_collider.Center = pos;
	const auto& transform = GetOwner()->GetComponent<TransformComponent>();
	ICollider::SetOffset(m_collider.Center - transform->Pos);
}

void CircleCollider::SetRadius(float radius)
{
	m_collider.Radius = radius;
}

Circle CircleCollider::GetCollider() const
{
	return m_collider;
}

void CircleCollider::Init()
{
}

void CircleCollider::Update(float deltaTime_s)
{
	const auto& transform = IComponent::GetOwner()->GetComponent<TransformComponent>();
	m_collider.Center = transform->Pos + m_offset;
}

void CircleCollider::Render()
{
#ifdef _DEBUG || DEBUG
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DxLib::DrawCircleAA(m_collider.Center.x, m_collider.Center.y, m_collider.Radius, 64, 0xff0000, 1);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
#endif
}

COLLIDER_TYPE CircleCollider::ColliderType()
{
	return COLLIDER_TYPE::CIRCLE;
}
