#pragma once
#include "AppDefinition.h"
class SoftRenderer
{
public:
	class Vector2;
	SoftRenderer();
	~SoftRenderer() = default;

	void Initialize(class GDIHelper* InitGDIHelper);
	void UpdateFrame(void);
	bool IsInRange(i32 x, i32 y);
	void DrawPixel(i32 x, i32 y);
	void DrawTri(float x0, float y0, float x1, float y1, float x2, float y2);
	void DrawLine(float x0, float y0, float x1, float y1);
private:
	class GDIHelper* mGDIHelper;
	void DrawFlatTri(float centerX, float centerY, float x1, float x2, float flatY);
};
