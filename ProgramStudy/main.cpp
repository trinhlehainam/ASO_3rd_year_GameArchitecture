#include <iostream>
#include <sstream>
#include <iomanip>

#include <DxLib.h>

namespace
{
	constexpr int kScreenWidth = 800;
	constexpr int kScreenHeight = 600;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowText(L"1916021_TRINH LE HAI NAM");
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(kScreenWidth, kScreenHeight, 32);

	if (DxLib::DxLib_Init() == -1)
		return -1;

	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	
	while (!DxLib::ProcessMessage() && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		DxLib::ClearDrawScreen();
		DxLib::ScreenFlip();
	}

	DxLib::DxLib_End();

	return 0;
}