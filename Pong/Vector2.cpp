#include "Vector2.h"

const Vector2 Vector2::Zero(0.0f, 0.0f);

Vector2::Vector2()
	:x(0.0f)
	,y(0.0f)
{
}

Vector2::Vector2(float x, float y)
	:x(x)
	,y(y)
{
}

Vector2::~Vector2()
{
}
