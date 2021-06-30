#include "SpriteComponent.h"

#include <DxLib.h>

#include "../_debug/_DebugConOut.h"
#include "../Math/MathHelper.h"

#include "../Systems/AnimationMng.h"
#include "../GameObject/Entity.h"
#include "TransformComponent.h"

SpriteComponent::SpriteComponent(const std::shared_ptr<Entity>& owner):
	IComponent(owner), m_transform(owner->GetComponent<TransformComponent>()),
	m_currentDurationId(0), m_timer_ms(0), m_loopCount(0),
	m_updateFunc(&SpriteComponent::UpdateSleep)
{
}

SpriteComponent::~SpriteComponent()
{
}

bool SpriteComponent::PickAnimationList(const std::string& listKey)
{
	auto& AnimMng = AnimationMng::Instance();
	if (!AnimMng.HasAnimationList(listKey)) return false;
	m_listKey = listKey;
	return true;
}

bool SpriteComponent::Play(const std::string& state)
{
	return Play(m_listKey, state);
}

bool SpriteComponent::Play(const std::string& listKey, const std::string& state)
{
	auto& AnimMng = AnimationMng::Instance();
	
	// Check function's arguments before assign to member variables
	if (!AnimMng.HasAnimation(listKey, state)) return false;
	if (IsPlaying(listKey, state)) return true;
	m_listKey = listKey;
	m_state = state;
	//

	auto& animation = AnimMng.GetAnimation(m_listKey, m_state);
	m_currentDurationId = animation.celBaseId;
	m_timer_ms = AnimMng.GetDuration_ms(m_currentDurationId);

	switch (animation.loop)
	{
	case -1:
		m_updateFunc = &SpriteComponent::UpdateInfinite;
		break;
	default:
		m_updateFunc = &SpriteComponent::UpdateLoop;
		m_loopCount = animation.loop;
		break;
	}
	return true;
}

bool SpriteComponent::IsPlaying(const std::string& listKey, const std::string& state)
{
	return m_listKey == listKey && m_state == state;
}

void SpriteComponent::Init()
{
}

void SpriteComponent::Update(float deltaTime_s)
{
	(this->*m_updateFunc)(deltaTime_s);
}

void SpriteComponent::UpdateInfinite(float deltaTime_s)
{
	if (m_timer_ms <= 0)
	{
		auto& animMng = AnimationMng::Instance();
		const auto& animtion = animMng.GetAnimation(m_listKey, m_state);
		m_currentDurationId = (m_currentDurationId - animtion.celBaseId + 1) % animtion.celCount + animtion.celBaseId;
		m_timer_ms = animMng.GetDuration_ms(m_currentDurationId);
	}

	m_timer_ms -= static_cast<int>(deltaTime_s / MathHelper::kMsToSecond);
}

void SpriteComponent::UpdateLoop(float deltaTime_s)
{
	auto& animMng = AnimationMng::Instance();
	const auto& animation = animMng.GetAnimation(m_listKey, m_state);;

	if (m_timer_ms <= 0)
	{
		++m_currentDurationId;
		m_timer_ms = animMng.GetDuration_ms(m_currentDurationId);
	}

	if (m_currentDurationId >= (animation.celBaseId + animation.celCount))
	{
		--m_loopCount;
		m_currentDurationId = animation.celBaseId;
		m_timer_ms = animMng.GetDuration_ms(m_currentDurationId);
	}

	if (m_loopCount < 0)
	{
		// Last durationId of current animation
		m_currentDurationId = animation.celBaseId + animation.celCount - 1;
		m_updateFunc = &SpriteComponent::UpdateSleep;
		return;
	}

	m_timer_ms -= static_cast<int>(deltaTime_s / MathHelper::kMsToSecond);
}

void SpriteComponent::UpdateSleep(float deltaTime_s)
{
}

void SpriteComponent::Render()
{
	auto& animMng = AnimationMng::Instance();
	const auto& transform = m_transform.lock();
	const auto& animation = animMng.GetAnimation(m_listKey, m_state);
	auto sourceX = (m_currentDurationId % animation.texColumns) * animation.celWidth;
	auto sourceY = (m_currentDurationId / animation.texColumns) * animation.celHeight;

	// TODO: Implement pivot(rotation center) variable
	DxLib::DrawRectRotaGraphFast3F(transform->Pos.x, transform->Pos.y,
		sourceX, sourceY, animation.celWidth, animation.celHeight,
		32.0f, 32.0f,
		transform->Scale.x, transform->Scale.y, transform->Rotation, animation.texId, 1);
		
}