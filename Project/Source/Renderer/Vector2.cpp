#include "Vector2.h"

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