#include "Vector4.h"
#include <cmath>
Vector4::Vector4(float x, float y, float z, float w)
	:mElements{ x, y, z, w }
{
}
Vector4 Vector4::operator+(const Vector4&  rhs) const
{
	Vector4 newVector;
    newVector.mElements[0] = mElements[0] + rhs.mElements[0];
	newVector.mElements[1] = mElements[1] + rhs.mElements[1];
	newVector.mElements[2] = mElements[2] + rhs.mElements[2];
	newVector.mElements[3] = mElements[3] + rhs.mElements[3];
	return *this;
}

Vector4 Vector4::operator-(const Vector4& rhs) const
{
	Vector4 newVector4;
	newVector4.mElements[0] = mElements[0] - rhs.mElements[0];
	newVector4.mElements[1] = mElements[1] - rhs.mElements[1];
	newVector4.mElements[2] = mElements[2] - rhs.mElements[2];
	newVector4.mElements[3] = mElements[3] - rhs.mElements[3];
	return newVector4;
}

Vector4 Vector4::operator*(float rhs) const
{
	Vector4 newVector;
	newVector.mElements[0] = mElements[0] * rhs;
	newVector.mElements[1] = mElements[1] * rhs;
	newVector.mElements[2] = mElements[2] * rhs;
	newVector.mElements[3] = mElements[3] * rhs;
	return newVector;
}

Vector4 operator*(float lhs, const Vector4& rhs)
{
	Vector4 newVector = Vector4(rhs.GetX() * lhs, rhs.GetY() * lhs, rhs.GetZ() * lhs, rhs.GetW() * lhs);
	return newVector;
}

float Vector4::GetMagnitute()
{
	if (mbIsDirty == true)
	{
		mMagnitute = sqrt(mElements[0] * mElements[0] + mElements[1] * mElements[1] + mElements[2] * mElements[2]);
		mbIsDirty = false;
	}
	return mMagnitute;
}

float Vector4::DotProduct(Vector4 lhs, Vector4 rhs)
{
	return lhs.mElements[0] * rhs.mElements[0] + lhs.mElements[1] * rhs.mElements[1] + lhs.mElements[2] * rhs.mElements[2];
}