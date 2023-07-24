#include "GounwooObject.h"

GounwooObject::GounwooObject(const std::string& modelPath, const Vector3& position, const Vector3& eulerAngle)
	: Position(position), EulerAngle(eulerAngle)
{
	Model.Load(modelPath);
}

GounwooObject::GounwooObject(const Vector3& position, const Vector3& eulerAngle)
	: Position(position), EulerAngle(eulerAngle)
{
}


Matrix4x4 GounwooObject::GetWorldMatrix() const
{
	return Matrix4x4::GetRotationMatrix(EulerAngle) * Matrix4x4::GetMoveMatrix(Position );
}