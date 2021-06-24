#include "IShape.h"

IShape::IShape():Pos(),IsAlive(true), EnableCollision(true)
{
}

IShape::IShape(TYPE type, unsigned int color):Type(type), Color(color), IsAlive(true), EnableCollision(true)
{
}

IShape::IShape(TYPE type, float x, float y, unsigned int color): Pos(x, y), Type(type), Color(color), IsAlive(true), EnableCollision(true)
{
}

IShape::IShape(TYPE type, vec2f pos, unsigned int color):Pos(pos), Type(type), Color(color), IsAlive(true), EnableCollision(true)
{
}

IShape::IShape(TYPE type, vec2f pos, vec2f speed, unsigned int color): Pos(pos), Speed(speed), Type(type), Color(color) ,IsAlive(true), EnableCollision(true)
{
}

IShape::~IShape()
{
}

void IShape::SetAlive(bool isAlive)
{
	IsAlive = isAlive;
}

void IShape::SetColor(unsigned int color)
{
	Color = color;
}

void IShape::SetCollisionFlag(bool enableCollision)
{
	EnableCollision = enableCollision;
}
