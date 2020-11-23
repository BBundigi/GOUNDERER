#pragma once

class Vector4
{
public:
	friend class Matrix4x4;
	enum
	{
		VECTOR_LENGTH = 4
	};
	static float DotProduct(Vector4 lhs, Vector4 rhs);

	Vector4() = default;
	Vector4(float x, float y, float z, float w);
	virtual ~Vector4() = default;
	float GetMagnitute();
	inline float GetX() const;
	inline float GetY() const;
	inline float GetZ() const;
	inline float GetW() const;
	inline float GetValue(unsigned int index) const;
	Vector4 operator+(const Vector4& rhs) const;
	Vector4 operator-(const Vector4& rhs) const;
	Vector4 operator*(float rhs) const;
private:
	float mElements[VECTOR_LENGTH];
	float mMagnitute;
	bool mbIsDirty;
};

Vector4 operator*(float lhs, const Vector4& rhs);


float Vector4::GetX() const
{
	return mElements[0];
}

float Vector4::GetY() const
{
	return mElements[1];
}

float Vector4::GetZ() const
{
	return mElements[2];
}

float Vector4::GetW() const
{
	return mElements[3];
}

float Vector4::GetValue(unsigned int index) const
{
	return mElements[index];
}