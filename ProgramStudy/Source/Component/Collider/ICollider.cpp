#include "ICollider.h"

ICollider::ICollider(const std::shared_ptr<Entity>& owner):IComponent(owner),m_isEnable(true)
{
}

ICollider::~ICollider()
{
}

void ICollider::SetEnable(bool enableFlag)
{
	m_isEnable = enableFlag;
}

void ICollider::SetOffset(float offsetX, float offsetY)
{
	m_offset.x = offsetX;
	m_offset.y = offsetY;
}

void ICollider::SetOffset(const vec2f& offset)
{
	m_offset = offset;
}

bool ICollider::IsEnable() const
{
	return m_isEnable;
}

vec2f ICollider::GetOffset() const
{
	return m_offset;
}
