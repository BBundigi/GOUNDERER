#pragma once
#define _USE_MATH_DEFINES
#include <cassert>
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"
#include <cmath>	
class Matrix4x4
{
public:
	enum
	{
		MATRIX_LENGTH = 16,
	};
	static Matrix4x4 GetRotationMatrix(const Vector3& eulerAngle);
	static Matrix4x4 GetReverseRotationMatrix(const Vector3& eulerAngle);
	static Matrix4x4 GetMoveMatrix(const Vector3& positionVector);
	static Matrix4x4 GetIdentitiy();

	Matrix4x4() = default;
	Matrix4x4(const float elements[]);
	Matrix4x4(const Matrix4x4& rhs) = default;
	Matrix4x4& operator=(const Matrix4x4& rhs) = default;
	Matrix4x4 operator+(const Matrix4x4& rhs);
	Matrix4x4 operator-(const Matrix4x4& rhs);
	Matrix4x4 operator*(const Matrix4x4& rhs);
	Matrix4x4& operator*(float rhs);
	Vector4 operator*(const Vector4& rhs) const;
	Matrix4x4& TransPos();
	inline float GetValue(unsigned int x, unsigned int y) const;
private:
	float mElements[MATRIX_LENGTH];
};

float Matrix4x4::GetValue(unsigned int x, unsigned int y) const
{
	assert(y * 4 + x < MATRIX_LENGTH);
	return mElements[y * 4 + x];
}