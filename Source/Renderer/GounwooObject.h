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
	GounwooObject(const std::string& modelPath, const Vector3& position, const Vector3& eulerAngle);
	GounwooObject(const Vector3& position, const Vector3& eulerAngle);
	Matrix4x4 GetWorldMatrix() const;
	Vector3 Position;
	Vector3 EulerAngle;

	void LoadModel(const std::string& modelPath)
	{
		Model.Load(modelPath);
	}
	inline int GetVertexCount() const
	{
		return Model.GetVerticesLength() / 3;	
	}

	
	inline const ModelAsset& GetModel() const
	{
		
		return Model;
	}
private:
	ModelAsset Model;
};