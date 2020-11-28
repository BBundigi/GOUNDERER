#include"Camera.h"
Camera::Camera(Vector4 postion, Vector3 rotation)
{
	Position = postion;
	Rotation = rotation;
}

Matrix4x4 Camera::GetViewMatrix()
{
	return Matrix4x4::GetReverseRotationMatrix(Rotation) * Matrix4x4::GetMoveMatrix(-1 * Position);
}

Matrix4x4 Camera::GetProjectMatrix()
{
	float d = 1 / tan((FOV / 2.0f) * (M_PI / 180.0f));
	float aspect = APP_WIDTH / (float)APP_HEIGHT;
	float element[Matrix4x4::MATRIX_LENGTH] = 
	{ d / aspect, 0.0f, 0.0f, 0.0f,
	0.0f,d, 0.0f, 0.0f,
	0.0f, 0.0f, Far / (Far - Near),  Near * Far / (Near - Far),
	0.0f, 0.0f, 1.0f, 0.0f };
	return Matrix4x4(element);
}