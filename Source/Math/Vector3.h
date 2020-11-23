#pragma once

class Vector3
{
public:
	friend class Matrix4x4;
	enum
	{
		VECTOR_LENGTH = 3
	};
	static float DotProduct(Vector3 lhs, Vector3 rhs);

	Vector3() = default;
	Vector3(float x, float y, float z);
	virtual ~Vector3() = default;
	float GetMagnitute();
	inline float GetX() const;
	inline float GetY() const;
	inline float GetZ() const;
	inline float GetValue(unsigned int index) const;
	Vector3 operator+(const Vector3& rhs) const;
	Vector3 operator-(const Vector3& rhs) const;
	Vector3 operator*(float rhs) const;
private:
	float mElements[VECTOR_LENGTH];
	float mMagnitute;
	bool mbIsDirty;
};

Vector3 operator*(float lhs, const Vector3& rhs);


float Vector3::GetX() const
{
	return mElements[0];
}

float Vector3::GetY() const
{
	return mElements[1];
}

float Vector3::GetZ() const
{
	return mElements[2];
}

float Vector3::GetValue(unsigned int index) const
{
	return mElements[index];
}