#include "JoypadXInput.h"

JoypadXInput::JoypadXInput():
	Input(ArrayInputs_t{
	XINPUT_BUTTON_DPAD_UP,
	XINPUT_BUTTON_DPAD_DOWN,
	XINPUT_BUTTON_DPAD_LEFT,
	XINPUT_BUTTON_DPAD_RIGHT,
	XINPUT_BUTTON_A,
	XINPUT_BUTTON_B,
	XINPUT_BUTTON_X,
	XINPUT_BUTTON_Y
		})
{
	DxLib::GetJoypadXInputState(DX_INPUT_PAD1, &m_joypadInputs);
}

JoypadXInput::~JoypadXInput()
{
}

void JoypadXInput::Update()
{
	DxLib::GetJoypadXInputState(DX_INPUT_PAD1, &m_joypadInputs);

	m_currentState = (m_currentState + 1) % kMaxInputStates;

	for (auto id : INPUT_ID())
		SetInputState(id, m_joypadInputs.Buttons[m_inputs[static_cast<size_t>(id)]]);
}

INPUT_DEVICE_ID JoypadXInput::GetDeviceID()
{
	return INPUT_DEVICE_ID::JOYPAD;
}
