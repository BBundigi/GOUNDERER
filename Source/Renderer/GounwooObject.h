#pragma once
#include "ModelAsset.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include <cstring>
class GounwooObject
{
public:
	GounwooObject() = default;
	virtual ~GounwooObject() = default;
	GounwooObject(const std::string& modelPath, const Vector4& position, const Vector3& eulerAngle);
	Matrix4x4 GetWorldMatrix() const;
	Vector4 Position;
	Vector3 EulerAngle;
	inline const ModelAsset& GetModel() const
	{
		return Model;
	}
private:
	ModelAsset Model;
};