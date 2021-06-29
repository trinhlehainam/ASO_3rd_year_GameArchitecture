#pragma once
#include "Input.h"

#include <DxLib.h>

class JoypadXInput: public Input
{
public:
	JoypadXInput();
	~JoypadXInput();
public:
	void Update() override;
	INPUT_DEVICE_ID GetDeviceID() override;
private:
	XINPUT_STATE m_joypadInputs;
};

