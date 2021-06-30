#include "Physics.h"

#include "../Math/MathHelper.h"
#include "../Math/vec2.h"
#include "../Math/segment2.h"

#include "../Component/Collider/BoxCollider.h"
#include "../Component/Collider/CircleCollider.h"

std::vector<std::weak_ptr<ICollider>> Physics::m_colliders;

bool Physics::RayCast(const vec2f& origin, const vec2f& dir, float maxDistance)
{
    segment2 seg{ origin, origin + unitVec(dir) * maxDistance };
    for (const auto& pCollider : m_colliders)
    {
        auto pCollider_checked = pCollider.lock();
        auto collider_type = pCollider_checked->ColliderType();
        switch (collider_type)
        {
        case COLLIDER_TYPE::BOX:
            {
                auto boxCollider = std::dynamic_pointer_cast<BoxCollider>(pCollider_checked);
                if (MathHelper::isOverlap(seg, boxCollider->GetCollider()))
                    return true;
            }
            break;
        case COLLIDER_TYPE::CIRCLE:
            {
                auto cirCollider = std::dynamic_pointer_cast<CircleCollider>(pCollider_checked);
                if (MathHelper::isOverlap(seg, cirCollider->GetCollider()))
                    return true;
            }
        break;
        default:
            break;
        }
           
    }
    return false;
}

void Physics::AddCollider(const std::shared_ptr<ICollider>& collider)
{
    m_colliders.push_back(collider);
}
