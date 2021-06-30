#include "EntityMng.h"

EntityMng::EntityMng()
{
}

EntityMng::~EntityMng()
{
}

std::shared_ptr<Entity> EntityMng::AddEntity(std::string tag)
{
	auto entity = std::make_shared<Entity>(std::move(tag));
	m_entities.push_back(entity);
	return entity ;
}

void EntityMng::AddEntity(const std::shared_ptr<Entity>& entity)
{
	m_entities.push_back(entity);
}

const std::vector<std::shared_ptr<Entity>>& EntityMng::GetAllEntities() const
{
	return m_entities;
}

void EntityMng::Update(float deltaTime_s)
{
	for (const auto& entity : m_entities)
		entity->Update(deltaTime_s);
}

void EntityMng::Render()
{
	for (const auto& entity : m_entities)
		entity->Render();
}
