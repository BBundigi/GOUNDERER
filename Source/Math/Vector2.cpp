#include "Vector2.h"

Vector2::Vector2(float x, float y)
{
	mX = x;
	mY = y;
}
Vector2 Vector2::operator+(const Vector2&  rhs) const
{
	Vector2 newVector;
	newVector.mX = mX + rhs.mX;
	newVector.mY = mY + rhs.mY;
	return newVector;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	Vector2 newVector;
	newVector.mX =  mX - rhs.mX;
	newVector.mY = mY - rhs.mY;
	return newVector;
}

Vector2 Vector2::operator*(float rhs) const
{
	Vector2 newVector;
	newVector.mX = mX * rhs;
	newVector.mY = mY * rhs;
	return newVector;
}

Vector2 operator*(float lhs, const Vector2& rhs)
{
	Vector2 newVector = Vector2(rhs.GetX() * lhs, rhs.GetY() * lhs);
	return newVector;
}