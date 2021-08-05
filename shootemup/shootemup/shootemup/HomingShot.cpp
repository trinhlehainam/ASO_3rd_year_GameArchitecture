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

	Trail trail;
	trail.isActive = true;
	trail.Pos = pos;
	trail.thickness = 20.0f;
	trails.insert(trail);

	pos += vel;
}

void HomingShot::Draw(int handle)
{
	auto currentPos = pos;
	auto trail_count = 0;
	for (auto& trail : trails)
	{
		if (trail.isActive == true) ++trail_count;
	}

	float u = 0.0f;
	float div = 1.0f / static_cast<float>(trail_count);
	for (auto& trail : trails)
	{
		if (trail.isActive == false) continue;
		auto nextPos = trail.Pos;
		auto deltaVec = currentPos - nextPos;

		auto v = deltaVec.Orthogonal().Normalized();
		auto p1 = currentPos + v * 16.0f;
		auto p2 = nextPos + v * 16.0f;
		auto p3 = nextPos - v * 16.0f;
		auto p4 = currentPos - v * 16.0f;

		DrawRectModiGraphF(
			p1.x, p1.y,
			p2.x, p2.y,
			p3.x, p3.y,
			p4.x, p4.y,
			u * 256, 0,
			div * 256, 64,
			handle, true);

		u += div;
		currentPos = nextPos;
	}
}

void HomingShot::ResetTrails()
{
	for (auto& trail : trails)
		trail.isActive = false;
}
