#include "SoftRenderer.h"
#include "Windows/GDIHelper.h"
#pragma once
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
	mTriVertexArr[0] = Vertex(Vector2(0.0f, 200.0f),Vector2(0.0f,1.0f));
	mTriVertexArr[1] = Vertex(Vector2(400.0f,0.0f), Vector2(1.0f,0.0f));
	mTriVertexArr[2] = Vertex(Vector2(0.0f, -200.0f),Vector2(0.0f,0.0f));
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

void SoftRenderer::DrawTri(const Vertex* const vertexes)
{
	const Vector2& position0 = vertexes[0].GetPosition();
	const Vector2& position1 = vertexes[1].GetPosition();
	const Vector2& position2 = vertexes[2].GetPosition();

	//TopFlatTri
	if (position0.GetY() == position1.GetY())//우선은 Epsilon 생각 안하기로
	{
		DrawFlatTri(position2,position0,position1, vertexes);
	}
	else if (position1.GetY() == position2.GetY())
	{
		DrawFlatTri(position0, position1, position2, vertexes);
	}
	else
	{

		float newX = position0.GetX() + (position1.GetY() - position0.GetY())
			/ (position2.GetY() - position0.GetY())
			* (position2.GetX() - position0.GetX());//닮음 이용
		float newY = vertexes[1].GetPosition().GetY();
		Vector2 point = Vector2(newX, newY);

		DrawFlatTri(position0 , position1, point, vertexes);
		DrawFlatTri(position2,position1, point, vertexes);
	}
}

void SoftRenderer::DrawFlatTri(const Vector2& centerPoint, const Vector2& point1, const Vector2& point2
								,const Vertex* const vertexes)
{
	const Vector2& position0 = vertexes[0].GetPosition();
	const Vector2& position1 = vertexes[1].GetPosition();
	const Vector2& position2 = vertexes[2].GetPosition();

	float area = (position1.GetX() - position0.GetX()) * (position2.GetY() - position0.GetY())
		- (position2.GetX() - position0.GetX()) * (position1.GetY() - position0.GetY());
	area = abs(area) / 2;
	int fillDir = centerPoint.GetY() > point1.GetY() ? -1 : 1;

	float dy = point1.GetY() - centerPoint.GetY();
	float leftdX = (point1.GetX() - centerPoint.GetX()) / dy * fillDir;//BottomFlat일 경우 기울기의 부호를 뒤집어 줘야함
	float rightdX = (point2.GetX() - centerPoint.GetX()) / dy * fillDir;

	if (leftdX > rightdX)
	{
		float temp = rightdX;
		rightdX = leftdX;
		leftdX = temp;
	}
	dy = abs(dy);
	float curLeftX = centerPoint.GetX();
	float curRightX = centerPoint.GetX();

	int curY = (int)round(centerPoint.GetY());

	for (int i = 0; i <= dy; i++)
	{

		int leftPointX = (int)ceil(curLeftX);
		int rightPointX = (int)curRightX;
		for (int j = leftPointX; j < rightPointX; j++)
		{
			Vertex newVertex = InterporateVertex(Vector2(j, curY), vertexes, area);
			mGDIHelper->SetColor(newVertex.GetUV().GetX() * 255, newVertex.GetUV().GetY() * 255, 0.0f);
			DrawPixel(j, curY);
		}
		curY += fillDir;
		curLeftX += leftdX;
		curRightX += rightdX;
	}
}

Vertex SoftRenderer::InterporateVertex(Vector2& point, const Vertex* const vertexes, float area)
{
	const Vector2 a = vertexes[1].GetPosition() - vertexes[0].GetPosition();
	const Vector2 b = vertexes[2].GetPosition() - vertexes[0].GetPosition();
	const Vector2 p = point - vertexes[0].GetPosition();
	float weightC = a.GetX() * p.GetY() - p.GetX() * a.GetY();
	weightC /= area * 2;
	weightC = abs(weightC);
	float weightB = b.GetX() * p.GetY() - p.GetX() * b.GetY();
	weightB /= area * 2;
	weightB = abs(weightB);
	float weightA = 1 - weightC - weightB;

	return Vertex::InterporateVertex(vertexes[0], vertexes[1], vertexes[2], weightA, weightB, weightC);

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
	DrawTri(mTriVertexArr);

	// Buffer Swap 
	mGDIHelper->BufferSwap();
}



