#pragma once
#include "IComponent.h"

#include "../Math/vec2.h"

class TransformComponent :
    public IComponent
{
public:
    explicit TransformComponent(const std::shared_ptr<Entity>& owner);
    explicit TransformComponent(const std::shared_ptr<Entity>& owner, const vec2f& pos);
    explicit TransformComponent(const std::shared_ptr<Entity>& owner, const vec2f& pos, vec2f scale, float rotation);
    ~TransformComponent();

public:
    vec2f Pos;
    vec2f Scale;
    float Rotation;

public:
    void Init() override;
    void Update(float deltaTime_s) override;
    void Render() override;

};

