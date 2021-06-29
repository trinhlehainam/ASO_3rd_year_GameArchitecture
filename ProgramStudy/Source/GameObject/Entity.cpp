#include "Entity.h"

#include "../Component/TransformComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/Collider/BoxCollider.h"

Entity::Entity():m_isActive(true)
{
	
}

Entity::Entity(std::string tag):m_isActive(true), m_tag(std::move(tag))
{
}

Entity::~Entity()
{
}

void Entity::SetActive(bool activeFlag)
{
	m_isActive = activeFlag;
}

void Entity::SetTag(std::string tag)
{
	m_tag = std::move(tag);
}

std::string Entity::GetTag() const
{
	return m_tag;
}

bool Entity::IsActive() const
{
	return m_isActive;
}

void Entity::Update(float deltaTime_s)
{
	for (const auto& component : m_components)
		component->Update(deltaTime_s);
}

void Entity::Render()
{
	for (const auto& component : m_components)
		component->Render();
}

template<typename T>
bool Entity::HasComponent()
{
	return m_componentMap.count(&typeid(T));
}

template<typename T>
std::shared_ptr<T> Entity::GetComponent()
{
	if (!HasComponent<T>()) return nullptr;
	return std::static_pointer_cast<T>(m_componentMap.at(&typeid(T)));
}
			
#define InstantiateFuncTemplate(component)\
template bool Entity::HasComponent<component>();\
template std::shared_ptr<component> Entity::GetComponent<>();\

#pragma region Specialization
template <> void Entity::AddComponent<TransformComponent>(const std::shared_ptr<Entity>& owner, const vec2f& pos);
#pragma endregion

#pragma region Instantiation
InstantiateFuncTemplate(TransformComponent);
InstantiateFuncTemplate(SpriteComponent);
InstantiateFuncTemplate(ICollider);
InstantiateFuncTemplate(BoxCollider);
#pragma endregion

