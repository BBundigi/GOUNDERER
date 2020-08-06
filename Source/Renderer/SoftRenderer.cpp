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

void SoftRenderer::DrawTri(float x0, float y0, float x1, float y1, float x2, float y2)
{
	//Sort Y;
	float sortY[3]
	{
		y0, y1, y2
	};
	float sortX[3]
	{
		x0, x1, x2
	};

	for(i32 i = 0; i < 3 - 1; i++)
	{
		for (i32 j = 0; j < 3 - i - 1; j++)
		{
			if (sortY[j] < sortY[j + 1])
			{
				float temp = sortY[j];
				sortY[j] = sortY[j + 1];
				sortY[j + 1] = temp;

				temp = sortX[j];
				sortX[j] = sortX[j + 1];
				sortX[j + 1] = temp;
			}
		}
	}
	//TopFlatTri
	if (sortY[0] == sortY[1])//우선은 Epsilon 생각 안하기로
	{
		DrawFlatTri(sortX[2], sortY[2], sortX[0], sortX[1], sortY[0]);
	}
	else if (sortY[1] == sortY[2])
	{
		DrawFlatTri(sortX[0], sortY[0], sortX[1], sortX[2], sortY[1]);
	}
	else
	{
		float newX = sortX[0] + (sortY[1] - sortY[0]) / (sortY[2] - sortY[0]) * (sortX[2] - sortX[0]);//닮음 이용
		float newY = sortY[1];

		DrawFlatTri(sortX[0], sortY[0], sortX[1], newX, newY);
		DrawFlatTri(sortX[2], sortY[2], sortX[1], newX, newY);
	}
}

void SoftRenderer::DrawFlatTri(float centerX, float centerY, float x1, float x2, float flatY)
{
	int fillDir = centerY > flatY ? -1 : 1;

	float dy = flatY - centerY;
	float leftdX = (x1 - centerX) / dy * fillDir;//BottomFlat일 경우 기울기의 부호를 뒤집어 줘야함
	float rightdX = (x2 - centerX) / dy * fillDir;

	if (leftdX > rightdX)
	{
		float temp = rightdX;
		rightdX = leftdX;
		leftdX = temp;
	}
	dy = abs(dy);
	float curLeftX = centerX;
	float curRightX = centerX;

	int curY = (int)round(centerY);

	for (int i = 0; i <= dy; i++)
	{
		int leftPointX = (int)ceil(curLeftX);
		int rightPointX = (int)curRightX;
		for (int j = leftPointX; j < rightPointX; j++)
		{
			DrawPixel(j, curY);
		}
		curY += fillDir;
		curLeftX += leftdX;
		curRightX += rightdX;
	}
}

void SoftRenderer::DrawLine(float x0, float y0, float x1, float y1)
{
	float currentX, currentY, dx, dy, step;
	int i = 0;
	dx = x1 - x0;
	dy = y1 - y0;

	if (abs(dx) >= abs(dy))
	{
		step = abs(dx);
	}
	else
	{
		step = abs(dy);
	}

	dx /= step;
	dy /= step;
	
	currentX = x0;
	currentY = y0;
	while (i <= step)
	{
		int xPoint = (int)round(currentX);
		int yPoint = (int)round(currentY);
		DrawPixel(xPoint, yPoint);

		currentX += dx;
		currentY += dy;
		i++;
	}
}

void SoftRenderer::UpdateFrame()
{
	// Buffer Clear
	mGDIHelper->SetColor(32, 128, 255);
	mGDIHelper->Clear();

	// Draw vertical line
	mGDIHelper->SetColor(255, 255, 255);
	DrawTri(0.0f,0.0f, 200.0f,100.0f, 200.0f, -300.0f);

	





	// Buffer Swap 
	mGDIHelper->BufferSwap();
}



