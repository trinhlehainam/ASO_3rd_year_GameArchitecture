#include "AnimationMng.h"

#include <sstream>

#include <rapidxml.hpp>

#include "../Utilities/StringHelper.h"
#include "ImageMng.h"

namespace
{
	const std::string kConnectTag = "_";
}

AnimationMng* AnimationMng::m_instance = nullptr;

void AnimationMng::Create()
{
	if (m_instance == nullptr)
		m_instance = new AnimationMng();
}
void AnimationMng::Destroy()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

AnimationMng& AnimationMng::Instance()
{
	if (m_instance == nullptr)
		Create();
	return *m_instance;
}

bool AnimationMng::LoadAnimationFromXML(const std::string& file)
{
	rapidxml::xml_document<> doc;
	auto content = StringHelper::LoadFileToStringBuffer(file);
	doc.parse<0>(&content[0]);

	auto pAminationList = doc.first_node();
	std::string listName;
	int celWidth = 0;
	int celHeight = 0;
	int celCount = 0;
	int texColumns = 0;
	for (auto pAttr = pAminationList->first_attribute(); pAttr; pAttr = pAttr->next_attribute())
	{
		if (strcmp(pAttr->name(), "name") == 0)
			listName = std::move(pAttr->value());
		else if (strcmp(pAttr->name(), "celwidth") == 0)
			celWidth = std::atoi(pAttr->value());
		else if (strcmp(pAttr->name(), "celheight") == 0)
			celHeight = std::atoi(pAttr->value());
		else if (strcmp(pAttr->name(), "celcount") == 0)
			celCount = std::atoi(pAttr->value());
		else if (strcmp(pAttr->name(), "columns") == 0)
			texColumns = std::atoi(pAttr->value());
	}
	m_durations_ms.reserve(m_durations_ms.size() + celCount);

	if (m_listMap.count(listName)) return false;
	auto& animationMap = m_listMap[listName];

	auto pImage = pAminationList->first_node("image");
	for (auto pAttr = pImage->first_attribute(); pAttr; pAttr = pAttr->next_attribute())
	{
		if (strcmp(pAttr->name(), "source") == 0)
		{
			auto& imgMng = ImageMng::Instance();
			imgMng.AddImage(pAttr->value(), listName);
		}
	}

	for (auto pAnimation = pAminationList->first_node("animation"); pAnimation; pAnimation = pAnimation->next_sibling())
	{
		std::string animKey;
		for (auto pAttr = pAnimation->first_attribute(); pAttr; pAttr = pAttr->next_attribute())
		{
			if (strcmp(pAttr->name(), "name") == 0)
			{
				animKey = listName + kConnectTag + pAttr->value();
				animationMap[animKey].texId = ImageMng::Instance().GetID(listName);
				animationMap[animKey].texColumns = texColumns;
				animationMap[animKey].celWidth = celWidth;
				animationMap[animKey].celHeight = celHeight;
			}
			else if (strcmp(pAttr->name(), "id") == 0)
				animationMap[animKey].celBaseId = std::atoi(pAttr->value());
			else if (strcmp(pAttr->name(), "count") == 0)
				animationMap[animKey].celCount = std::atoi(pAttr->value());
			else if (strcmp(pAttr->name(), "loop") == 0)
				animationMap[animKey].loop = std::atoi(pAttr->value());
		}

		// Add data in duration node to duration container (m_durations_ms)
		auto pDuration = pAnimation->first_node();
		std::stringstream data{ std::move(pDuration->value()) };
		while (!data.eof())
		{
			std::string line;
			data >> line;
			std::stringstream ssLine{ line };
			int duration = 0;
			while (ssLine >> duration)
			{
				m_durations_ms.push_back(duration);

				if (ssLine.peek() == ',')
					ssLine.ignore();
			}

		}
	}

	doc.clear();

	return true;
}

bool AnimationMng::HasAnimationList(const std::string& listKey)
{
	return m_listMap.count(listKey);
}

bool AnimationMng::HasAnimation(const std::string& listKey, const std::string& state)
{
	if (!m_listMap.count(listKey)) return false;

	return m_listMap[listKey].count(listKey + kConnectTag + state);
}

const Animation& AnimationMng::GetAnimation(const std::string& listKey, const std::string& state) const
{
	return m_listMap.at(listKey).at(listKey + kConnectTag + state);
}

int AnimationMng::GetDuration_ms(int durationIndex) const
{
	return m_durations_ms[durationIndex];
}

AnimationMng::AnimationMng() {}

AnimationMng::~AnimationMng() {}

// Avoid copy and move sematics
AnimationMng::AnimationMng(const AnimationMng&) {}
AnimationMng::AnimationMng(AnimationMng&&) noexcept {}
void AnimationMng::operator = (const AnimationMng&) {}
void AnimationMng::operator = (AnimationMng&&) noexcept {}