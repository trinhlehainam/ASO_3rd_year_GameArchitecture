#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include <DxLib.h>

#include "Source/Math/vec2.h"

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

	std::vector<int> hTextures;

	for (int i = 0; i < 6; ++i)
	{
		std::wostringstream wsstream;
		wsstream << L"Assets/Textures/adventurer-run-";
		wsstream << std::setfill(L'0') << std::setw(2) <<  i;
		wsstream << L".png";

		hTextures.push_back(DxLib::LoadGraph(wsstream.str().c_str()));
	}
	
	vec2f pos{ 100.0f,100.0f };
	vec2f size;
	DxLib::GetGraphSizeF(hTextures[0], &size.x, &size.y);
	size.x *= 4.0f;
	size.y *= 4.0f;
	int currentFrame = 0;
	int currentTextureIdx = 0;

	while (!DxLib::ProcessMessage() && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		DxLib::ClearDrawScreen();
		DxLib::DrawRotaGraphF(pos.x, pos.y, 1.0f , 0.0f, hTextures[(++currentFrame/10) % 6], 0);
		DxLib::ScreenFlip();
	}

	for (auto& hTexture : hTextures)
		DxLib::DeleteGraph(hTexture);

	DxLib::DxLib_End();

	return 0;
}