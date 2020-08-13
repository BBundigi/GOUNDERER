#pragma once
#include "AppDefinition.h"
#include "Vertex.h"
#include "TextureAsset.h"
class SoftRenderer
{
public:
	SoftRenderer();
	~SoftRenderer() = default;

	void Initialize(class GDIHelper* InitGDIHelper);
	void UpdateFrame(void);
	bool IsInRange(i32 x, i32 y);
	void DrawPixel(i32 x, i32 y);
	void DrawTri(const Vertex* const vertexes);
	void DrawLine(float x0, float y0, float x1, float y1);
private:
	Vertex mTriVertexArr[3];
	
	class GDIHelper* mGDIHelper;
	void DrawFlatTri(const Vector2& centerPoint, const Vector2& point1, const Vector2& point2
		, const Vertex* const vertexes);
	Vertex InterporateVertex(Vector2& point, const Vertex* const vertexes, float area);
};
