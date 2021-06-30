#include "BoxCollider.h"

#include <DxLib.h>

#include "../../GameObject/Entity.h"
#include "../TransformComponent.h"

BoxCollider::BoxCollider(const std::shared_ptr<Entity>& owner):ICollider(owner)
{
}

BoxCollider::BoxCollider(const std::shared_ptr<Entity>& owner, const AABBf& boxInfo):ICollider(owner),m_collider(boxInfo)
{
    const auto& transform = owner->GetComponent<TransformComponent>();
    ICollider::SetOffset(m_collider.Origin - transform->Pos);
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::SetOrigin(const vec2f& origin)
{
    m_collider.Origin = origin;
    const auto& transform = GetOwner()->GetComponent<TransformComponent>();
    ICollider::SetOffset(m_collider.Origin - transform->Pos);
}

void BoxCollider::SetSize(const vec2f& size)
{
    m_collider.Size = size;
}

vec2f BoxCollider::GetOrigin() const
{
    return m_collider.Origin;
}

vec2f BoxCollider::GetSize() const
{
    return m_collider.Size;
}

AABBf BoxCollider::GetCollider() const
{
    return m_collider;
}

void BoxCollider::Init()
{
}

void BoxCollider::Update(float deltaTime_s)
{
    const auto& transform = IComponent::GetOwner()->GetComponent<TransformComponent>();
    m_collider.Origin = transform->Pos + m_offset;
}

void BoxCollider::Render()
{
#ifdef _DEBUG || DEBUG
    DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
    DxLib::DrawBoxAA(m_collider.Origin.x, m_collider.Origin.y, m_collider.Origin.x + m_collider.Size.x, m_collider.Origin.y + m_collider.Size.y, 0xff0000, 1);
    DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
#endif
}

COLLIDER_TYPE BoxCollider::ColliderType()
{
    return COLLIDER_TYPE::BOX;
}
