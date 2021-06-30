#include "Player.h"

#include "../Systems/ImageMng.h"
#include "../Systems/Physics.h"

#include "Entity.h"
#include "../Input/KeyboardInput.h"
#include "../Input/JoypadXInput.h"
#include "../Component/TransformComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/Collider/BoxCollider.h"
#include "../Component/Collider/CircleCollider.h"

namespace
{
	int color = 0;
	vec2f dir;
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(INPUT_DEVICE_ID deviceId)
{
	auto& imageMng = ImageMng::Instance();
	imageMng.AddImage("knight", "Assets/Textures/knight 1 axe.png");

	m_entity = std::make_shared<Entity>("knight");
	switch (deviceId)
	{
	case INPUT_DEVICE_ID::KEYBOARD:
		m_input = std::make_unique<KeyboardInput>();
		break;
	case INPUT_DEVICE_ID::JOYPAD:
		m_input = std::make_unique<JoypadXInput>();
		break;
	}

	m_entity->AddComponent<TransformComponent>(m_entity);
	auto transform = m_entity->GetComponent<TransformComponent>();
	transform->Pos = vec2f{ 100.0f,100.0f };
	transform->Scale = vec2f{ 1.5f,1.5f };
	m_entity->AddComponent<SpriteComponent>(m_entity);
	auto sprite = m_entity->GetComponent<SpriteComponent>();
	sprite->PickAnimationList("knight");
	sprite->Play("Idle");
	// m_entity->AddComponent<CircleCollider>(m_entity);
	// auto collider = m_entity->GetComponent<CircleCollider>();
	// collider->SetCenterPos(vec2f{ 100.0f, 100.0f });
	// collider->SetRadius(32.0f);
}

void Player::Update(float deltaTime_s)
{
	m_input->Update();
	auto speed = vec2f{ 0.0f,0.0f };

	const auto& transform = m_entity->GetComponent<TransformComponent>();
	const auto& sprite = m_entity->GetComponent<SpriteComponent>();

	if (m_input->IsPressed(INPUT_ID::UP))
		speed.y = -100.0f;
	else if (m_input->IsPressed(INPUT_ID::DOWN))
		speed.y = 100.0f;
	else if (m_input->IsPressed(INPUT_ID::LEFT))
		speed.x = -100.0f;
	else if (m_input->IsPressed(INPUT_ID::RIGHT))
		speed.x = 100.0f;
	transform->Pos += speed * deltaTime_s;

	if (speed != 0.0f)
	{
		dir = unitVec(speed);
		color = Physics::RayCast(transform->Pos, dir, 50.0f) ? 0xff0000 : 0x00ff00;
	}

	if (speed.x != 0.0f || speed.y != 0.0f)
		sprite->Play("Run");
	else
		sprite->Play("Idle");
}

void Player::Render()
{
	const auto& transform = m_entity->GetComponent<TransformComponent>();
	vec2f origin{ transform->Pos };
	vec2f end = origin + dir * 50.0f;
	DxLib::DrawLineAA(origin.x, origin.y, end.x, end.y, color, 2.0f);
}

std::shared_ptr<Entity> Player::GetEntity() const
{
	return m_entity;
}
