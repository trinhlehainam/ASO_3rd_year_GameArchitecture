#include "BoxCollider.h"

#include <DxLib.h>

#include "../../GameObject/Entity.h"
#include "../TransformComponent.h"

BoxCollider::BoxCollider(const std::shared_ptr<Entity>& owner, const AABBf& boxInfo):ICollider(owner),Collider(boxInfo)
{
    const auto& transform = owner->GetComponent<TransformComponent>();
    ICollider::SetOffset(Collider.Pos - transform->Pos);
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Init()
{
    
}

void BoxCollider::Update(float deltaTime_s)
{
    const auto& transform = IComponent::GetOwner()->GetComponent<TransformComponent>();
    Collider.Pos = transform->Pos + m_offset;
}

void BoxCollider::Render()
{
#ifdef _DEBUG || DEBUG
    DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
    DxLib::DrawBoxAA(Collider.Pos.x, Collider.Pos.y, Collider.Pos.x + Collider.Size.x, Collider.Pos.y + Collider.Size.y, 0xff0000, 1);
    DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
#endif
}

COLLIDER_TYPE BoxCollider::ColliderType()
{
    return COLLIDER_TYPE::BOX;
}
