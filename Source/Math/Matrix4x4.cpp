#include "Matrix4x4.h"
Matrix4x4::Matrix4x4(const float elements[])
	: mElements{elements[0], elements[1] ,elements[2] ,elements[3], 
				elements[4], elements[5], elements[6], elements[7], 
				elements[8], elements[9], elements[10], elements[11], 
				elements[12], elements[13], elements[14], elements[15], }
{

}
Matrix4x4 Matrix4x4::GetRotationMatrix(const Vector3& eulerAngle)
{
	float elements[Matrix4x4::MATRIX_LENGTH] =
	{ cos(eulerAngle.GetY() * M_PI / 180.0f), 0, sin(eulerAngle.GetY() * M_PI / 180.0f), 0,
		0,1,0,0,
	  -sin(eulerAngle.GetY() * M_PI / 180.0f),0,cos(eulerAngle.GetY() * M_PI / 180.0f), 0,
		0,0,0,1 };

	Matrix4x4 roll = Matrix4x4(elements);

	elements[0] = 1;
	elements[1] = 0;
	elements[2] = 0;
	elements[3] = 0;

	elements[4] = 0;
	elements[5] = cos(eulerAngle.GetX() * M_PI / 180.0f);
	elements[6] = -sin(eulerAngle.GetX() * M_PI / 180.0f);
	elements[7] = 0;

	elements[8] = 0;
	elements[9] = sin(eulerAngle.GetX() * M_PI / 180.0f);
	elements[10] = cos(eulerAngle.GetX() * M_PI / 180.0f);
	elements[11] = 0;

	elements[12] = 0;
	elements[13] = 0;
	elements[14] = 0;
	elements[15] = 1;
	Matrix4x4 pitch = Matrix4x4(elements);

	elements[0] = cos(eulerAngle.GetZ() * M_PI / 180.0f);
	elements[1] = -sin(eulerAngle.GetZ() * M_PI / 180.0f);
	elements[2] = 0;
	elements[3] = 0;

	elements[4] = sin(eulerAngle.GetZ() * M_PI / 180.0f);
	elements[5] = cos(eulerAngle.GetZ() * M_PI / 180.0f);
	elements[6] = 0;
	elements[7] = 0;

	elements[8] = 0;
	elements[9] = 0;
	elements[10] = 1;
	elements[11] = 0;

	elements[12] = 0;
	elements[13] = 0;
	elements[14] = 0;
	elements[15] = 1;
	Matrix4x4 yaw = Matrix4x4(elements);
	return yaw * pitch * roll;
}
Matrix4x4 Matrix4x4::GetReverseRotationMatrix(const Vector3& eulerAngle)
{
	float elements[Matrix4x4::MATRIX_LENGTH];
	elements[0] = cos(eulerAngle.GetY() * M_PI / 180.0f);
	elements[1] = 0;
	elements[2] = sin(eulerAngle.GetY() * M_PI / 180.0f);
	elements[3] = 0;

	elements[4] = 0;
	elements[5] = 1;
	elements[6] = 0;
	elements[7] = 0;

	elements[8] = -sin(eulerAngle.GetY() * M_PI / 180.0f);
	elements[9] = 0;
	elements[10] = cos(eulerAngle.GetY() * M_PI / 180.0f);
	elements[11] = 0;

	elements[12] = 0;
	elements[13] = 0;
	elements[14] = 0;
	elements[15] = 1;
	Matrix4x4 roll = Matrix4x4(elements);
	roll.TransPos();

	elements[0] = 1;
	elements[1] = 0;
	elements[2] = 0;
	elements[3] = 0;

	elements[4] = 0;
	elements[5] = cos(eulerAngle.GetX() * M_PI / 180.0f);
	elements[6] = -sin(eulerAngle.GetX() * M_PI / 180.0f);
	elements[7] = 0;

	elements[8] = 0;
	elements[9] = sin(eulerAngle.GetX() * M_PI / 180.0f);
	elements[10] = cos(eulerAngle.GetX() * M_PI / 180.0f);
	elements[11] = 0;

	elements[12] = 0;
	elements[13] = 0;
	elements[14] = 0;
	elements[15] = 1;
	Matrix4x4 pitch = Matrix4x4(elements);
	pitch.TransPos();

	elements[0] = cos(eulerAngle.GetZ() * M_PI / 180.0f);
	elements[1] = -sin(eulerAngle.GetZ() * M_PI / 180.0f);
	elements[2] = 0;
	elements[3] = 0;

	elements[4] = sin(eulerAngle.GetZ() * M_PI / 180.0f);
	elements[5] = cos(eulerAngle.GetZ() * M_PI / 180.0f);
	elements[6] = 0;
	elements[7] = 0;

	elements[8] = 0;
	elements[9] = 0;
	elements[10] = 1;
	elements[11] = 0;

	elements[12] = 0;
	elements[13] = 0;
	elements[14] = 0;
	elements[15] = 1;
	Matrix4x4 yaw = Matrix4x4(elements);
	yaw.TransPos();
	return roll * pitch * yaw;
}
Matrix4x4 Matrix4x4::GetMoveMatrix(const Vector4& positionVector)
{
	Matrix4x4 moveMat = Matrix4x4::GetIdentitiy();
	moveMat.mElements[3] = positionVector.GetX();
	moveMat.mElements[7] = positionVector.GetY();
	moveMat.mElements[11] = positionVector.GetZ();
	return moveMat;
}
Matrix4x4 Matrix4x4::GetIdentitiy()
{
	float element[Matrix4x4::MATRIX_LENGTH] = { 1,0,0,0,
												0,1,0,0,
												0,0,1,0,
												0,0,0,1 };
	return Matrix4x4(element);
}
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs)
{
	float elements[Matrix4x4::MATRIX_LENGTH];
	for (int i = 0; i < Matrix4x4::MATRIX_LENGTH; i++)
	{
		elements[i] = mElements[i] + rhs.mElements[i];
	}
	return Matrix4x4(elements);
}
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs)
{
	float elements[Matrix4x4::MATRIX_LENGTH];
	for (int i = 0; i < Matrix4x4::MATRIX_LENGTH; i++)
	{
		elements[i] = mElements[i] - rhs.mElements[i];
	}
	return Matrix4x4(elements);
}
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs)
{
	Matrix4x4 mat;
	for (int i = 0; i < Matrix4x4::MATRIX_LENGTH; i++)
	{
		mat.mElements[i] = 0;
	}
	for (int i = 0; i < MATRIX_LENGTH; i++)
	{
		int xIndex = i % 4;
		int yIndex = i / 4;
		for (int j = 0; j < 4; j++)
		{
			mat.mElements[i] += mElements[yIndex * 4 + j] * rhs.mElements[j * 4 + xIndex];
		}
	}
	return mat;
}
Matrix4x4& Matrix4x4::operator*(float rhs)
{
	for (int i = 0; i < Matrix4x4::MATRIX_LENGTH; i++)
	{
		mElements[i] *= rhs;
	}
	return *this;
}
Vector4 Matrix4x4::operator*(const Vector4& rhs) const
{
	float vectorValue[4] = { 0,0,0,0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			vectorValue[i] += mElements[i * 4 + j] * rhs.mElements[j];
		}
	}
	return Vector4(vectorValue[0], vectorValue[1], vectorValue[2], vectorValue[3]);
}

Matrix4x4& Matrix4x4::TransPos()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			int index = i * 4 + j;
			int transIndex = j * 4 + i;
			float temp = mElements[transIndex];
			mElements[transIndex] = mElements[index];
			mElements[index] = temp;
		}
	}
	return *this;
}