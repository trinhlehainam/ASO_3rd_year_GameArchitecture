#pragma once
#include "ICollider.h"
#include "../../Math/Geometry/AABB.h"

class BoxCollider :
    public ICollider
{
public:
    explicit BoxCollider(const std::shared_ptr<Entity>& owner, const AABBf& boxInfo);
    ~BoxCollider();
public:
    void Init() override final;
    void Update(float deltaTime_s) override final;
    void Render() override final;
    COLLIDER_TYPE ColliderType() override final;
public:
    AABBf Collider;
};

