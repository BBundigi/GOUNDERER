
#include "SoftRenderer.h"
#include "Windows/GDIHelper.h"


SoftRenderer::SoftRenderer()
{
	mGDIHelper = nullptr;
}

void SoftRenderer::Initialize(GDIHelper* InitGDIHelper)
{
	if (InitGDIHelper == nullptr)
	{
		return;
	}

	mGDIHelper = InitGDIHelper;

	return;
}

bool SoftRenderer::IsInRange(i32 x, i32 y)
{
	return (abs(x) < (APP_WIDTH / 2)) && (abs(y) < (APP_HEIGHT / 2));
}

void SoftRenderer::DrawPixel(i32 x, i32 y)
{
	if (!IsInRange(x, y))
	{
		return;
	}

	u32* dest = reinterpret_cast<u32*>(mGDIHelper->GetpBits());
	i32 offset = APP_WIDTH * APP_HEIGHT / 2 + APP_WIDTH / 2 + x + APP_WIDTH * -y;
	*(dest + offset) = mGDIHelper->GetCurrentColor();
}

void SoftRenderer::UpdateFrame()
{
	// Buffer Clear
	mGDIHelper->SetColor(32, 128, 255);
	mGDIHelper->Clear();

	// Draw vertical line
	mGDIHelper->SetColor(255, 0, 0);
	for (i32 line = -100; line <= 100; ++line)
	{
		DrawPixel(0, line);
	}

	// Draw horizontal line
	for (i32 line = -100; line <= 100; ++line)
	{
		DrawPixel(line, 0);
	}
	
	// Buffer Swap 
	mGDIHelper->BufferSwap();
}

