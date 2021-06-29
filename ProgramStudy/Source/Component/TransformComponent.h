#pragma once
#include "IComponent.h"

#include "../Math/vec2.h"

class TransformComponent :
    public IComponent
{
public:
    explicit TransformComponent(const std::shared_ptr<Entity>& owner, const vec2f& pos);
    explicit TransformComponent(const std::shared_ptr<Entity>& owner, const vec2f& pos, float scale, float angle);
    ~TransformComponent();

public:
    vec2f Pos;
    float Scale;
    float Angle;

public:
    void Init() override;
    void Update(float deltaTime_s) override;
    void Render() override;

};

