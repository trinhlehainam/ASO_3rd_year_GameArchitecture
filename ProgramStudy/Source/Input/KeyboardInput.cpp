#include "KeyboardInput.h"

#include <DxLib.h>

namespace
{
	constexpr int kMaxKeyNum = 256;
	std::array<char, kMaxKeyNum> gKeyStates;
}


KeyboardInput::KeyboardInput():Input(ArrayInputs_t{ 
	KEY_INPUT_UP,
	KEY_INPUT_DOWN,
	KEY_INPUT_LEFT,
	KEY_INPUT_RIGHT,
	KEY_INPUT_Z,
	KEY_INPUT_X,
	KEY_INPUT_C,
	KEY_INPUT_P })
{
}

KeyboardInput::~KeyboardInput()
{
}

void KeyboardInput::Update()
{
	DxLib::GetHitKeyStateAll(gKeyStates.data());

	m_currentState = (m_currentState + 1) % kMaxInputStates;

	for (auto id : INPUT_ID())
		SetInputState(id, gKeyStates[m_inputs[static_cast<size_t>(id)]]);
}

INPUT_DEVICE_ID KeyboardInput::GetDeviceID()
{
	return INPUT_DEVICE_ID::KEYBOARD;
}
