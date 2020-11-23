#pragma once

class Vector2
{
public:
	static float DotProduct(Vector2 lhs, Vector2 rhs);
	static float CrossMagnitute(Vector2 lhs, Vector2 rhs);
 	Vector2() = default;
	Vector2(float x, float y);
	virtual ~Vector2() = default;
	inline float GetX() const;
	inline float GetY() const;
	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator-(const Vector2& rhs) const;
	Vector2 operator*(float rhs) const;
private:
	float mX;
	float mY;
};

Vector2 operator*(float lhs, const Vector2& rhs);


float Vector2::GetX() const
{
	return mX;
}

float Vector2::GetY() const
{
	return mY;
}

