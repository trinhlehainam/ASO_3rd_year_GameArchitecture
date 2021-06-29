#pragma once
#include "Input.h"

class KeyboardInput : public Input
{
public:
	KeyboardInput();
	~KeyboardInput();
public:
	void Update() override;
	INPUT_DEVICE_ID GetDeviceID() override;
};

