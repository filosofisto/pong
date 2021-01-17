#pragma once
#include <iostream>

using namespace std;

class Vector2
{
public:
	float x;
	float y;

	Vector2();

	explicit Vector2(float x, float y);

	virtual ~Vector2();

	static const Vector2 Zero;

	//friend ostream& operator<<(ostream& out, const Vector2& vector);
};

/*ostream& operator<<(ostream& out, const Vector2& vector)
{
	out << "(" << vector.x << ", " << vector.y << ")";
	return out;
}*/

