#pragma once

class Vector2
{
public:
	inline float GetX() const;
	inline float GetY() const;
	Vector2& operator+(const Vector2& rhs);
	Vector2& operator-(const Vector2& rhs);
private:
	float mX;
	float mY;
};

float Vector2::GetX() const
{
	return mX;
}

float Vector2::GetY() const
{
	return mY;
}

