#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <string>

#include "../Component/IComponent.h"
#include "../Input/Input.h"

class Entity
{
public:
	Entity();
	explicit Entity(std::string tag);
	~Entity();

	void SetActive(bool activeFlag);
	void SetTag(std::string tag);

	std::string GetTag() const;
	bool IsActive() const;

	void Update(float deltaTime_s);
	void Render();

	template<typename T>
	void AddComponent(const std::shared_ptr<Entity>& owner);

	template<typename T>
	bool HasComponent();

	template<typename T>
	std::shared_ptr<T> GetComponent();

private:
	std::vector<std::shared_ptr<IComponent>> m_components;
	// type_info's data deleted DEFAULT constructor
	// type_info can be only instantiated by typeid
	// -> point to type_info after it's created
	std::unordered_map<const type_info*, std::shared_ptr<IComponent>> m_componentMap;
	bool m_isActive;
	std::string m_tag;
};

