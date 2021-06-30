#pragma once
#include "ICollider.h"
#include "../../Math/Geometry/Circle.h"

class CircleCollider : public ICollider
{
public:
	explicit CircleCollider(const std::shared_ptr<Entity>& owner);
	~CircleCollider();

	void SetCenterPos(const vec2f& pos);
	void SetRadius(float radius);

	Circle GetCollider() const;

public:
	void Init() override;
	void Update(float deltaTime_s) override;
	void Render() override;
	COLLIDER_TYPE ColliderType() override;
private:
	Circle m_collider;
};

