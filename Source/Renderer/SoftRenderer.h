#pragma once

#include "AppDefinition.h"

class SoftRenderer
{
public:

	SoftRenderer();
	~SoftRenderer() = default;

	void Initialize(class GDIHelper* InitGDIHelper);
	void UpdateFrame(void);
	bool IsInRange(i32 x, i32 y);
	void DrawPixel(i32 x, i32 y);

private:

	class GDIHelper* mGDIHelper;

};
