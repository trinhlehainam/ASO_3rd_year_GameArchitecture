#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include <DxLib.h>

#include "Math/vec2.h"

namespace
{
	constexpr int kScreenWidth = 800;
	constexpr int kScreenHeight = 600;
}

void DrawRectAA(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int color, float Thickness);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowText(L"1916021_TRINH LE HAI NAM");
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(kScreenWidth, kScreenHeight, 32);

	if (DxLib::DxLib_Init() == -1)
		return -1;

	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	std::vector<int> hTextures;
	std::vector<vec2f> vertices;
	int groundTex = DxLib::LoadGraph(L"Assets/Textures/ground.png");

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
	
	vertices.emplace_back(100.0f, 68.0f);
	vertices.emplace_back(132.0f, 68.0f);
	vertices.emplace_back(132.0f, 100.0f);
	vertices.emplace_back(100.0f, 100.0f);

	constexpr size_t block_size = 32;
	int count = 720 / block_size;
	constexpr float sin_amp = 50.0f;
	constexpr float base_y = 240.0f;
	
	int base_angle = 0;
	while (!DxLib::ProcessMessage() && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		DxLib::ClearDrawScreen();

		float x = 0.0f;
		float y = base_y;
		vec2f currentPos(static_cast<float>(x), static_cast<float>(y));
		vec2f lastDeltaVec, nextDeltaVec;;
		
		for (int i = 0; i < count; ++i)
		{
			float nextX = i * block_size;
			float frequency_radian = (float)(0.5f * nextX + base_angle) / 180.0f * DX_PI;
			float nextY = sin_amp * sinf(frequency_radian);
			
			auto deltaVec = unitVec(vec2f{ (float)block_size, (float)nextY }) * static_cast<float>(block_size);
			auto nextPos = currentPos + deltaVec;

			nextX = (i+1) * block_size;
			frequency_radian = (float)(0.5f * nextX + base_angle) / 180.0f * DX_PI;
			nextY = sin_amp * sinf(frequency_radian);
			nextDeltaVec = (i + 1) < count ?unitVec(vec2f{ (float)block_size, (float)nextY }) * static_cast<float>(block_size):
				vec2f{};

			vec2f leftPos, rightPos;
			if (lastDeltaVec != 0.0f || nextDeltaVec != 0.0f)
			{
				leftPos = currentPos + unitVec(orthogonalVec(deltaVec) + orthogonalVec(lastDeltaVec)) * static_cast<float>(block_size);
				rightPos = nextPos + unitVec(orthogonalVec(deltaVec) + orthogonalVec(nextDeltaVec)) * static_cast<float>(block_size);
			}
			else
			{
				leftPos = currentPos + orthogonalVec(deltaVec);
				rightPos = nextPos + orthogonalVec(deltaVec);
			}
				
			DxLib::DrawModiGraphF(currentPos.x, currentPos.y,
				nextPos.x, nextPos.y,
				rightPos.x, rightPos.y,
				leftPos.x, leftPos.y,
				groundTex,
				1);
			DrawRectAA(currentPos.x, currentPos.y,
				nextPos.x, nextPos.y,
				rightPos.x, rightPos.y,
				leftPos.x, leftPos.y,
				0xffffff, 2.0f);

			currentPos = nextPos;
			lastDeltaVec = deltaVec;
		}

		base_angle = (base_angle + 1) % 720;
		DxLib::ScreenFlip();
	}

	for (auto& hTexture : hTextures)
		DxLib::DeleteGraph(hTexture);

	DxLib::DxLib_End();

	return 0;
}

void DrawRectAA(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int color, float Thickness)
{
	DxLib::DrawLineAA(x1, y1, x2, y2, color, Thickness);
	DxLib::DrawLineAA(x2, y2, x3, y3, color, Thickness);
	DxLib::DrawLineAA(x3, y3, x4, y4, color, Thickness);
	DxLib::DrawLineAA(x4, y4, x1, y1, color, Thickness);
}