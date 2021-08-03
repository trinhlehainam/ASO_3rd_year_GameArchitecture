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
	Vector2 lastDeltaVec, nextDeltaVec;
	auto trail_count = 0;
	for (auto& trail : trails)
	{
		if (trail.isActive == true) ++trail_count;
	}

	auto trail_idx = 0;
	Vector2 img_size;
	Vector2 block_size;
	GetGraphSizeF(handle, &img_size.x, &img_size.y);
	block_size.x = img_size.x / trail_count;
	block_size.y = img_size.y;
	for (auto& trail : trails)
	{
		if (trail.isActive == false) continue;
		auto nextPos = trail.Pos;
		auto deltaVec = currentPos - nextPos;
		Vector2 leftPos, rightPos;
		if (lastDeltaVec != 0.0f || nextDeltaVec != 0.0f)
		{

		}
		else
		{
			leftPos = currentPos + deltaVec.Orthogonal();
			rightPos = nextPos + deltaVec.Orthogonal();
		}
		
		
		DxLib::DrawRectModiGraphF(currentPos.x, currentPos.y,
			nextPos.x, nextPos.y,
			rightPos.x, rightPos.y,
			leftPos.x, leftPos.y,
			0, 0,
			block_size.x, block_size.y,
			handle, 1);

		currentPos = nextPos;
		lastDeltaVec = deltaVec;
		++trail_idx;
	}
}

void HomingShot::ResetTrails()
{
	for (auto& trail : trails)
		trail.isActive = false;
}
