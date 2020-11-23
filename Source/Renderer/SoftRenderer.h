#pragma once

#include "AppDefinition.h"
#include "Vertex.h"
#include "TextureAsset.h"
#include "Camera.h"
#include "GounwooObject.h"

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
	void DrawObject(const GounwooObject& object);
private:
	float mDepthBuffer[APP_WIDTH * APP_HEIGHT];
	Vertex mTriVertexArr[3];
	Camera mCamera;
	TextureAsset mTextureAsset;
	GounwooObject mObject;
	class GDIHelper* mGDIHelper;
	void DrawFlatTri(const Vector4& centerPoint, const Vector4& point1, const Vector4& point2
		, const Vertex* const vertexes);
	Vertex InterporateVertex(Vector2& point, const Vertex* const vertexes, float area);
	void ClaerDephtBuffer();
};
