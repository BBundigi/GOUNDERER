#pragma once

#include "SoftRenderer.h"
#include "Windows/GDIHelper.h"
#include <cassert>

SoftRenderer::SoftRenderer()
	: mObject("SimpleObject.obj", Vector4(0.0f, 0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f))
	, mCamera(Vector4(0.0f, 0.0f, -10.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f))
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
	mCamera.Near = 0.3f;
	mCamera.Far = 300.0f;
	mCamera.FOV = 60.0f;
	// Buffer Clear
	FILE* debugFile = fopen("DebugText.txt", "w");
	Vertex* vertexes = mObject.GetModel().GetVertices();
	Matrix4x4 viewMat = mCamera.GetViewMatrix();
	Matrix4x4 worldMat = mObject.GetWorldMatrix();
	Matrix4x4 projectMat = mCamera.GetProjectMatrix();
	int	vlaue = mObject.GetModel().GetVerticesLength();
	for (int i = 0; i < mObject.GetModel().GetVerticesLength(); i++)
	{
		Vector4 debugVector =  viewMat * worldMat * vertexes[i].Position;
		debugVector = projectMat * debugVector;
		debugVector = debugVector * (-1 / debugVector.GetW());
		//debugVector = Vector4(debugVector.GetX() * (APP_WIDTH / 2), debugVector.GetY() * (APP_HEIGHT / 2), debugVector.GetZ(), debugVector.GetW());
		fprintf(debugFile, "{%f,%f,%f,%f}\n", debugVector.GetX(), debugVector.GetY(),debugVector.GetZ(),debugVector.GetW());
		if (i % 3 == 2)
		{
			fprintf(debugFile, "====================\n");
		}
	}
	fclose(debugFile);
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
	const Vector4& position0 = vertexes[0].Position;
	const Vector4& position1 = vertexes[1].Position;
	const Vector4& position2 = vertexes[2].Position;

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
		float newY = position1.GetY();
		Vector4 point = Vector4(newX, newY, 0.0f, 0.0f);
		float area = (position1.GetX() - position0.GetX()) * (position2.GetY() - position0.GetY())
			- (position2.GetX() - position0.GetX()) * (position1.GetY() - position0.GetY());
		area = abs(area) / 2;
		DrawFlatTri(position0 , position1, point, vertexes);
		DrawFlatTri(position2,position1, point, vertexes);
	}
}

void SoftRenderer::DrawFlatTri(const Vector4& centerPoint, const Vector4& point1, const Vector4& point2
								,const Vertex* const vertexes)
{
	const Vector4& position0 = vertexes[0].Position;
	const Vector4& position1 = vertexes[1].Position;
	const Vector4& position2 = vertexes[2].Position;

	float area = (position1.GetX() - position0.GetX()) * (position2.GetY() - position0.GetY())
		- (position2.GetX() - position0.GetX()) * (position1.GetY() - position0.GetY());
	area = abs(area) / 2;
	int fillDir = centerPoint.GetY() > point1.GetY() ? -1 : 1;

	int dy = (int)point1.GetY() - (int)centerPoint.GetY();
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

	int curY = (int)(centerPoint.GetY());
	const Color24* textureDatas = mTextureAsset.GetTextureData();
	for (int i = 0; i <= dy; i++)
	{
		int leftPointX = (int)ceil(curLeftX);
		int rightPointX = (int)curRightX;
		for (int j = leftPointX; j <= rightPointX; j++)
		{
			Vertex newVertex = InterporateVertex(Vector2(j, curY), vertexes, area);
			Vector2 sampledPos(newVertex.UV.GetX() * (mTextureAsset.GetTextureWidth()),
				newVertex.UV.GetY() * (mTextureAsset.GetTextureHeight() - 1));
			//int newTexelIndex = static_cast<int>(round(sampledPos.GetY())) * mTextureAsset.GetTextureWidth()
				+ static_cast<int>(round(sampledPos.GetX()));
			//assert(newTexelIndex < mTextureAsset.GetTextureWidth() * mTextureAsset.GetTextureHeight());
			//Color24 texel = textureDatas[newTexelIndex];
			if(j > APP_WIDTH / 2 || j < -APP_WIDTH / 2 || curY > APP_HEIGHT / 2 || curY < -APP_HEIGHT / 2)
			{
				continue;
			}
			DrawPixel(j, curY);
		}
		curY += fillDir;
		curLeftX += leftdX;
		curRightX += rightdX;
	}
}

Vertex SoftRenderer::InterporateVertex(Vector2& point, const Vertex* const vertexes, float area)
{
	const Vector4 a = vertexes[1].Position - vertexes[0].Position;
	const Vector4 b = vertexes[2].Position - vertexes[0].Position;
	const Vector4 p = Vector4(point.GetX(),point.GetY(),0.0f,0.0f) - vertexes[0].Position;
	float weightC = a.GetX() * p.GetY() - p.GetX() * a.GetY();
	weightC /= area * 2;
	weightC = abs(weightC);
	float weightB = b.GetX() * p.GetY() - p.GetX() * b.GetY();
	weightB /= area * 2;
	weightB = abs(weightB);
	float weightA = 1 - weightC - weightB;

	return Vertex::InterporateVertex(vertexes[0], vertexes[1], vertexes[2], weightA, weightB, weightC);
}

void SoftRenderer::ClaerDephtBuffer()
{
	u32 bufferLength = APP_WIDTH * APP_HEIGHT;
	for (int i = 0; i < bufferLength; i++)
	{
		mDepthBuffer[i] = 1.0f;
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

void SoftRenderer::DrawObject(const GounwooObject& object)
{
	Vertex triVertex[3];
	const ModelAsset& model = object.GetModel();
	const Vertex* const vertexes = object.GetModel().GetVertices();
	Matrix4x4 world = object.GetWorldMatrix();
	Matrix4x4 view = mCamera.GetViewMatrix();
	Matrix4x4 project = mCamera.GetProjectMatrix();
	Matrix4x4 MVPmat = project * view * world;
	for (int i = 0; i < model.GetVerticesLength(); i += 3)
	{
		mGDIHelper->SetColor(i * 10, i * 10, i * 10);
		triVertex[0] = vertexes[i];
		triVertex[1] = vertexes[i + 1];
		triVertex[2] = vertexes[i + 2];
		
		for (int i = 0; i < 3; i++)
		{
			Vector4 newPos = MVPmat * triVertex[i].Position;
			newPos = newPos * (-1 / newPos.GetW());
			newPos = Vector4(newPos.GetX() * (APP_WIDTH / 2), newPos.GetY() * (APP_HEIGHT / 2), newPos.GetZ(), newPos.GetW());
			
			triVertex[i].Position = newPos;
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3 - i - 1; j++)
			{
				if (triVertex[j + 1].Position.GetY() > triVertex[j].Position.GetY())
				{
					auto temp = triVertex[j];
					triVertex[j] = triVertex[j + 1];
					triVertex[j + 1] = temp;
				}
			}
		}
		DrawTri(triVertex);

	}
}

void SoftRenderer::UpdateFrame()
{
	mGDIHelper->SetColor(32, 128, 255);
	mGDIHelper->Clear();
	DrawObject(mObject);
	mObject.EulerAngle = mObject.EulerAngle + Vector3(0.0f, 1.0f, 0.0f);
	mGDIHelper->BufferSwap();
	return;
}