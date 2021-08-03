#include "HomingShot.h"
#include <DxLib.h>

HomingShot::HomingShot():speed(1.0f),rotateDir(0.5f),angle(0.0f)
{
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

	pos += vel;
}

void HomingShot::Draw(int handle)
{
	DrawRotaGraph(pos.x, pos.y, 1.0f, angle, handle, true);
}
