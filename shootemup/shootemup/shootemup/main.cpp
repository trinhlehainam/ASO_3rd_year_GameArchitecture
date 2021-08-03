#include<cmath>
#include<algorithm>

#include<DxLib.h>

#include"Geometry.h"
#include"HomingShot.h"

///�����蔻��֐�
///@param posA A�̍��W
///@param radiusA A�̔��a
///@param posB B�̍��W
///@param radiusB B�̔��a
bool IsHit(const Position2& posA, float radiusA, const Position2& posB,  float radiusB) {
	auto dif = posB - posA;
	auto d = radiusA + radiusB;
	return Dot(dif, dif) <= d * d;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("�e������`");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//�w�i�p
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/arrow_short.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	struct Bullet {
		Position2 pos;//���W
		Vector2 vel;//���x
		bool isActive = false;//�����Ă邩�`�H
	};

	//�e�̔��a
	float bulletRadius = 5.0f;

	//���@�̔��a
	float playerRadius = 10.0f;
	float enemyRadius = 20.0f;

	//�K����256���炢����Ƃ�
	Bullet bullets[256];
	HomingShot homming[5];

	Position2 enemypos(320,25);//�G���W
	Position2 playerpos(320, 400);//���@���W

	unsigned int frame = 0;//�t���[���Ǘ��p

	char keystate[256] = {};
	char lastKeystate[256] = {};
	bool isDebugMode = true;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;
	constexpr float kHommingShotSpeed = 10.0f;
	bool isRight = false;
	while (ProcessMessage() == 0 && keystate[KEY_INPUT_ESCAPE] == 0) {
		ClearDrawScreen();

		std::copy(keystate, keystate + 256, lastKeystate);
		GetHitKeyStateAll(keystate);

		//�w�i
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);


		//�v���C���[
		if (keystate[KEY_INPUT_RIGHT]) {
			playerpos.x = min(640,playerpos.x+4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			playerpos.x = max(0,playerpos.x-4);
		}
		if (keystate[KEY_INPUT_UP]) {
			playerpos.y = max(0,playerpos.y-4);
		}else if (keystate[KEY_INPUT_DOWN]) {
			playerpos.y = min(480,playerpos.y+4);
		}

		int pidx = (frame/4 % 2)*5+3;
		DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//���@�̖{��(�����蔻��)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}

		//�e����
		if (keystate[KEY_INPUT_SPACE] && !lastKeystate[KEY_INPUT_SPACE])
		{
			isRight = (isRight + 1) % 2;
			for (auto& b : homming) {
				if (!b.isActive) {
					b.pos = playerpos;
					b.vel = Vector2(isRight ? kHommingShotSpeed : -kHommingShotSpeed, 0);
					b.speed = kHommingShotSpeed;
					b.rotateDir = 0.5f;
					b.isActive = true;
					break;
				}
			}
		}

		//�e�̍X�V����ѕ\��
		for (auto& b : homming) {
			if (!b.isActive) {
				continue;
			}

			//�e�̌��ݍ��W�ɒe�̌��ݑ��x�����Z���Ă�������
			
			b.Update(enemypos);

			b.Draw(bulletH);
			
			if (isDebugMode) {
				//�e�̖{��(�����蔻��)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//�e���E��
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
				b.ResetTrails();
			}

			//������I
			//����IsHit�͎����������Ă܂���B�����ŏ����Ă��������B
			if (IsHit(b.pos, bulletRadius, enemypos, enemyRadius)) {
				//�������������������Ă��������B
				b.isActive = false;
				b.ResetTrails();
			}
		}

		//�G�̕\��
		enemypos.x = abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//�G�̖{��(�����蔻��)
			DrawCircle(enemypos.x, enemypos.y, enemyRadius, 0xffaaaa, false, 3);
		}
		++frame;
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}