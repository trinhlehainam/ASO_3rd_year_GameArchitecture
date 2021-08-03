#include "HomingShot.h"
#include <cmath>
#include <DxLib.h>

namespace
{
	size_t frame = 0;
}

HomingShot::HomingShot():speed(1.0f),rotateDir(0.5f),angle(0.0f)
{
	trails.set_head_to_tail_loop();
}

void HomingShot::Update(const Vector2& goal)
{
	// Calculate turn angle
	auto vel_unit = vel.Normalized();
	auto to_goal = (goal - pos).Normalized();
	auto turn_angle = std::acos(Dot(vel_unit, to_goal));
	float dir = Cross(vel_unit, to_goal) > 0.0f ? rotateDir : -rotateDir;
	turn_angle = std::fminf(turn_angle, DX_PI_F / 24.0f);
	turn_angle *= dir;
	//

	auto current_angle = std::atan2f(vel.y, vel.x);
	angle = current_angle + turn_angle;

	vel = Vector2(cos(angle), sin(angle)) * speed;

	auto oldPos = pos;
	pos += vel;
	auto newPos = pos;
	Trail trail;
	trail.isSet = true;
	trail.Pos = oldPos;
	trail.thickness = 20.0f;
	trails.insert(trail);
	
}

void HomingShot::Draw(int handle)
{
	DrawRotaGraph(pos.x, pos.y, 1.0f, angle, handle, true);
	auto currentPos = pos;
	for (auto& trail : trails)
	{
		if (trail.isSet == false) continue;
		DrawLineAA(currentPos.x, currentPos.y, trail.Pos.x, trail.Pos.y, 0xffffff, trail.thickness);
		trail.thickness /= 1.2f;
		if (trail.thickness <= 0.05f)
		{
			trail.thickness = 0.0f;
			trail.isSet = false;
		}
		currentPos = trail.Pos;
	}
}

void HomingShot::ResetTrails()
{
	for (auto& trail : trails)
		trail.isSet = false;
}
