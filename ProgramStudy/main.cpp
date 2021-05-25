#include <DxLib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowTextW(L"1916021_TRINH LE HAI NAM");

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