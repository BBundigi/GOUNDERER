#pragma once

#include "AppDefinition.h"

class SoftRenderer
{
public:

	SoftRenderer();
	~SoftRenderer() = default;

	void Initialize(class GDIHelper* InitGDIHelper);
	void UpdateFrame(void);
	bool IsInRange(int x, int y);
	void DrawPixel(int x, int y);

private:

	class GDIHelper* mGDIHelper;

};
