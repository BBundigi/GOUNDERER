#pragma once

#include <memory>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vertex.h"
#include <sstream>
typedef unsigned int UINT;

// Use OBJ File
class ModelAsset final
{
public:

	ModelAsset() noexcept = default;
	virtual ~ModelAsset() noexcept = default;
	void Load(const std::string& InPath);

private:

	std::unique_ptr<Vertex[]> mVertices;
	std::unique_ptr<UINT[]> mIndices;
	UINT mVerticesLength;
	UINT mIndicesLength;
	

public:

	inline Vertex* GetVertices() const { return mVertices.get(); }
	inline UINT* GetIndices() const { return mIndices.get(); }
	inline UINT GetVerticesLength() const { return mVerticesLength; }
	inline UINT GetIndicesLength() const { return mIndicesLength; }

};