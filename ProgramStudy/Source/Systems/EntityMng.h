#pragma once
#include "../GameObject/Entity.h"

class EntityMng
{
public:
	EntityMng();
	~EntityMng();

	std::shared_ptr<Entity> AddEntity(std::string tag);
	void AddEntity(const std::shared_ptr<Entity>& entity);
	const std::vector<std::shared_ptr<Entity>>& GetAllEntities() const;

	void Update(float deltaTime_s);
	void Render();
private:
	std::vector<std::shared_ptr<Entity>> m_entities;
};

