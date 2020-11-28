#include "GounwooObject.h"

GounwooObject::GounwooObject(const std::string& modelPath, const Vector4& position, const Vector3& eulerAngle)
	:Position(position), EulerAngle(eulerAngle)
{
	Model.Load(modelPath);
}
Matrix4x4 GounwooObject::GetWorldMatrix() const
{
	return Matrix4x4::GetMoveMatrix(Position ) * Matrix4x4::GetRotationMatrix(EulerAngle);
}