#pragma once
#include "IShape.h"

#include <array>

class Triangle :
    public IShape
{
public:
	explicit Triangle(vec2f a, vec2f b, vec2f c, unsigned int color);
	explicit Triangle(vec2f a, vec2f b, vec2f c, vec2f speed, unsigned int color);

	bool ConstrainPosition(float width, float height) override;
	void Update(float deltaTime_s) override;
	void Draw() override;
	void Draw(float scale) override;
	void SpecialAction(std::vector<std::unique_ptr<IShape>>& container) override;

	std::array<vec2f,3> P;
};

