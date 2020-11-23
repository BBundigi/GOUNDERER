#include "Vector3.h"
#include <cmath>
Vector3::Vector3(float x, float y, float z)
	:mElements{ x, y, z}
{
}
Vector3 Vector3::operator+(const Vector3&  rhs) const
{
	Vector3 newVector(mElements[0] + rhs.mElements[0],mElements[1] + rhs.mElements[1], mElements[2] + rhs.mElements[2]);
	return newVector;
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
	Vector3 newVector(mElements[0] - rhs.mElements[0], mElements[1] - rhs.mElements[1], mElements[2] - rhs.mElements[2]);
	return newVector;
}

Vector3 Vector3::operator*(float rhs) const
{
	Vector3 newVector(mElements[0] * rhs, mElements[1] * rhs, mElements[2] * rhs);
	return newVector;
}

Vector3 operator*(float lhs, const Vector3& rhs)
{
	Vector3 newVector = Vector3(rhs.GetX() * lhs, rhs.GetY() * lhs, rhs.GetZ() * lhs);
	return newVector;
}

float Vector3::GetMagnitute()
{
	if (mbIsDirty == true)
	{
		mMagnitute = sqrt(mElements[0] * mElements[0] + mElements[1] * mElements[1] + mElements[2] * mElements[2]);
		mbIsDirty = false;
	}
	return mMagnitute;
}

float Vector3::DotProduct(Vector3 lhs, Vector3 rhs)
{
	return lhs.mElements[0] * rhs.mElements[0] + lhs.mElements[1] * rhs.mElements[1] + lhs.mElements[2] * rhs.mElements[2];
}