#include "IComponent.h"

IComponent::IComponent(const std::shared_ptr<Entity>& owner) :m_owner(owner) {}

IComponent::~IComponent() = default;

void IComponent::SetOwner(const std::shared_ptr<Entity>&owner)
{
    m_owner = owner;
}

bool IComponent::IsOwnerExist()
{
    return !m_owner.expired();
}

std::shared_ptr<Entity> IComponent::GetOwner()
{
    return m_owner.lock();
}
