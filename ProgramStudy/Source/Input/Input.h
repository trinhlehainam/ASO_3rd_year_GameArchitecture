#pragma once
#include <bitset>
#include <array>

#include "InputID.h"

namespace
{
	constexpr int kMaxInputStates = 2;
}

enum class INPUT_DEVICE_ID
{
	KEYBOARD,
	JOYPAD
};

class Input
{
public:
	using ArrayInputs_t = std::array<int, static_cast<size_t>(INPUT_ID::MAX)>;
	using InputState_t = std::bitset<static_cast<size_t>(INPUT_ID::MAX)>;
public:
	Input();
	explicit Input(ArrayInputs_t);
	virtual ~Input();
public:
	virtual void Update() = 0;
	virtual INPUT_DEVICE_ID GetDeviceID() = 0;
public:
	void SetInput(INPUT_ID id, int DX_KEY_INPUT);
	void SetInputState(INPUT_ID id, bool state);
public:
	bool IsPressed(INPUT_ID id) const;
	bool IsJustPressed(INPUT_ID id) const;
	bool IsReleased(INPUT_ID id) const;
	bool IsJustReleased(INPUT_ID id) const;
private:
	int PreviousState() const;

protected:
	ArrayInputs_t m_inputs;
	std::array<InputState_t, kMaxInputStates> m_inputStates;
	int m_currentState;
};

