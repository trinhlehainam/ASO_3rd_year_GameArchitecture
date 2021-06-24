#pragma once
#include "IShape.h"

#include <memory>
#include <vector>

class Cloud :
    public IShape
{
public:
    explicit Cloud(vec2f pos, vec2f speed);
    ~Cloud();

    bool ConstrainPosition(float width, float height) override;
    void Update(float deltaTime_s) override;
    void SpecialAction(std::vector<std::unique_ptr<IShape>>& container) override;
    void Draw() override;
    void Draw(float scale) override;

    std::vector<std::unique_ptr<IShape>> Elements;
};

