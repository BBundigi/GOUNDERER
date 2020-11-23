#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Matrix4x4.h"
#include "AppDefinition.h"
#include <cmath>
class Camera
{
public:
	Camera() = default;
	Camera(Vector4 postion, Vector3 rotation);
	Vector4 Position;
	Vector3 Rotation;
	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectMatrix();

	float Near;
	float Far;
	float FOV;
private:

};