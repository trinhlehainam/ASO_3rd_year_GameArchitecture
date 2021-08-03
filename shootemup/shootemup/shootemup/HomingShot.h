#pragma once
#include "Bullet.h"
#include "Utilities/static_ring.h"

struct HomingShot: public Bullet
{
	float rotateDir;
	float angle;
	float speed;


	HomingShot();

	void Update(const Vector2& goal);
	void Draw(int handle);
};

