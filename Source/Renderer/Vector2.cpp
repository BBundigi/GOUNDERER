#include "Vector2.h"

Vector2::Vector2(float x, float y)
{
	mX = x;
	mY = y;
}
Vector2& Vector2::operator+(const Vector2&  rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	return *this;
}

Vector2& Vector2::operator-(const Vector2& rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	return *this;
}

Vector2& Vector2::operator*(float rhs)
{
	mX *= rhs;
	mY *= rhs;
	return *this;
}

Vector2 operator*(float lhs, const Vector2& rhs)
{
	Vector2 newVector = Vector2(rhs.GetX() * lhs, rhs.GetY() * lhs);
	return newVector;
}