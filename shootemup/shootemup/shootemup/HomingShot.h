#pragma once
#include "Bullet.h"

#include "Utilities/static_ring.h"

#include "Trail.h"

struct HomingShot: public Bullet
{
	float rotateDir;
	float angle;
	float speed;
	static_ring<Trail, 10> trails;

	HomingShot();

	void Update(const Vector2& goal);
	void Draw(int handle);
	void ResetTrails();
};

