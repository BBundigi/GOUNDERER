#pragma once

#include <memory>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vertex.h"
#include <sstream>
#include <AppDefinition.h>

// Use OBJ File
class ModelAsset final
{
public:

	ModelAsset() noexcept = default;
	virtual ~ModelAsset() noexcept = default;
	void Load(const std::string& InPath);

private:

	std::unique_ptr<Vertex[]> mVertices;
	std::unique_ptr<u32[]> mIndices;
	u32 mVerticesLength;
	u32 mIndicesLength;
	

public:
	inline Vertex* GetVertices() const { return mVertices.get(); }
	inline u32* GetIndices() const { return mIndices.get(); }
	inline u32 GetVerticesLength() const { return mVerticesLength; }
	inline u32 GetIndicesLength() const { return mIndicesLength; }

};