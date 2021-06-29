#include "Input.h"

#include <DxLib.h>


Input::Input():
	m_currentState(0)
{
}

Input::Input(ArrayInputs_t inputs):m_inputs(std::move(inputs)), m_currentState(0)
{
}

Input::~Input()
{
}

void Input::SetInput(INPUT_ID id, int DX_KEY_INPUT)
{
	m_inputs[static_cast<size_t>(id)] = DX_KEY_INPUT;
}

void Input::SetInputState(INPUT_ID id, bool state)
{
	m_inputStates[m_currentState].set(static_cast<size_t>(id), state);
}

bool Input::IsPressed(INPUT_ID id) const
{
	return m_inputStates[m_currentState][static_cast<size_t>(id)] == 1;
}

bool Input::IsJustPressed(INPUT_ID id) const
{
	return m_inputStates[m_currentState][static_cast<size_t>(id)] == 1 &&
		m_inputStates[PreviousState()][static_cast<size_t>(id)] == 0;
}

bool Input::IsReleased(INPUT_ID id) const
{
	return m_inputStates[m_currentState][static_cast<size_t>(id)] == 0;
}

bool Input::IsJustReleased(INPUT_ID id) const
{
	return m_inputStates[m_currentState][static_cast<size_t>(id)] == 0 &&
		m_inputStates[PreviousState()][static_cast<size_t>(id)] == 1;
}

int Input::PreviousState() const
{
	return ((m_currentState - 1 ) + kMaxInputStates) % kMaxInputStates;
}
