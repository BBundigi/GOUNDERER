#pragma once

#include "SoftRenderer.h"
#include "Windows/GDIHelper.h"
#include <iostream>
#include <cassert>

SoftRenderer::SoftRenderer()
	: mObject("Resources/Models/Box.obj", Vector4(1.0f, 0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f))
	, mCamera(Vector4(0.0f, 0.0f, -5.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f))
{
	mTextureAsset.Load("Resources/Texture/Fieldstone_DM.tga");
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
	mCamera.Far = 3000.0f;
	mCamera.FOV = 60.0f;
	// Buffer Clear
	FILE* debugFile = fopen("DebugText.txt", "w");
	Vertex* vertexes = mObject.GetModel().GetVertices();
	Matrix4x4 viewMat = mCamera.GetViewMatrix();
	Matrix4x4 worldMat = mObject.GetWorldMatrix();
	Matrix4x4 projectMat = mCamera.GetProjectMatrix();
	int	vlaue = mObject.GetModel().GetVerticesLength();
	fprintf(debugFile, "World Vector\n");
	for (int i = 0; i < mObject.GetModel().GetVerticesLength(); i++)
	{
		Vector4 worldVector = worldMat * vertexes[i].Position;
		//debugVector = projectMat * debugVector;
		//debugVector = Vector4(debugVector.GetX() * (APP_WIDTH / 2), debugVector.GetY() * (APP_HEIGHT / 2), debugVector.GetZ(), debugVector.GetW());
		fprintf(debugFile, "{%f,%f,%f,%f}\n", worldVector.GetX(), worldVector.GetY(), worldVector.GetZ(), worldVector.GetW());
		if (i % 3 == 2)
		{
			fprintf(debugFile, "====================\n");
		}
	}

	fprintf(debugFile, "View Vector\n");
	for (int i = 0; i < mObject.GetModel().GetVerticesLength(); i++)
	{
		Vector4 viewVector = viewMat * worldMat * vertexes[i].Position;
		//debugVector = projectMat * debugVector;
		//debugVector = Vector4(debugVector.GetX() * (APP_WIDTH / 2), debugVector.GetY() * (APP_HEIGHT / 2), debugVector.GetZ(), debugVector.GetW());
		fprintf(debugFile, "{%f,%f,%f,%f}\n", viewVector.GetX(), viewVector.GetY(), viewVector.GetZ(), viewVector.GetW());
		if (i % 3 == 2)
		{
			fprintf(debugFile, "====================\n");
		}
	}

	fprintf(debugFile, "Project NDC Vector\n");
	for (int i = 0; i < mObject.GetModel().GetVerticesLength(); i++)
	{
		Vector4 projectVector = viewMat * worldMat * vertexes[i].Position;
		projectVector =  projectMat * projectVector;
		projectVector = projectVector * (1.0f / projectVector.GetW());
		fprintf(debugFile, "{%f,%f,%f,%f}\n", projectVector.GetX(), projectVector.GetY(), projectVector.GetZ(), projectVector.GetW());
		if (i % 3 == 2)
		{
			fprintf(debugFile, "====================\n");
		}
	}

	fprintf(debugFile, "Project Screen Vector\n");
	for (int i = 0; i < mObject.GetModel().GetVerticesLength(); i++)
	{
		Vector4 projectVector = viewMat * worldMat * vertexes[i].Position;
		projectVector = projectMat * projectVector;
		projectVector = projectVector * (1.0f / projectVector.GetW());
		projectVector = Vector4(projectVector.GetX() * (APP_WIDTH / 2), projectVector.GetY() * (APP_HEIGHT / 2), 
			projectVector.GetZ(), projectVector.GetW());
		fprintf(debugFile, "{%f,%f,%f,%f}\n", projectVector.GetX(), projectVector.GetY(), projectVector.GetZ(), projectVector.GetW());
		if (i % 3 == 2)
		{
			fprintf(debugFile, "====================\n");
		}
	}
	fclose(debugFile);
	DrawObject(mObject);
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
		DrawFlatTri(position0 , position1, point, vertexes);
		DrawFlatTri(position2, position1, point, vertexes);
	}
}

void SoftRenderer::DrawFlatTri(const Vector4& centerPoint, const Vector4& point1, const Vector4& point2
								,const Vertex* const vertexes)
{

#ifdef DEBUG
	static int sFunctionCallCount = 0;
	char fileName[32];
	sprintf(fileName, "DrawTriDebug%d.txt", sFunctionCallCount);
	FILE* debugFile = fopen(fileName, "w");
	sFunctionCallCount++;
	if (sFunctionCallCount > 4)
	{
		sFunctionCallCount = 0;
	}
#endif
	const Vector4& position0 = vertexes[0].Position;
	const Vector4& position1 = vertexes[1].Position;
	const Vector4& position2 = vertexes[2].Position;

	float area = (position1.GetX() - position0.GetX()) * (position2.GetY() - position0.GetY())
		- (position2.GetX() - position0.GetX()) * (position1.GetY() - position0.GetY());
	area = abs(area) / 2;
	if (area == 0)
	{
		return;
	}
	int fillDir = centerPoint.GetY() > point1.GetY() ? -1 : 1;
	float dy = (point1.GetY() - centerPoint.GetY());
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
	//int curY = (int)(centerPoint.GetY());
	float curY = centerPoint.GetY();
	const Color24* textureDatas = mTextureAsset.GetTextureData();

#ifdef DEBUG
	fprintf(debugFile, "====Draw New Flat Tri====\n");
	fprintf(debugFile, "CenterPoints : (%f, %f)\nPoint1 : (%f, %f)\nPoint2 : (%f, %f)\n"
		, centerPoint.GetX(), centerPoint.GetY(), point1.GetX(), point1.GetY(), point2.GetX(), point2.GetY());
	fprintf(debugFile, "Basic Info\nfillDir : %s\ndy : %f\nleftdx : %f\nrightdx : %f\n",
		fillDir == 1 ? "above" : "below", dy, leftdX, rightdX);
	fprintf(debugFile, "\t=====Draw Start=====\n");
#endif // DEBUG

	for (int i = 0; i <= dy; i++)
	{
		int pixelYIndex = fillDir == 1 ? (int)ceil(curY) : (int)floor(curY);
		int leftPointX = (int)floor(curLeftX);
		int rightPointX = (int)ceil(curRightX);
#ifdef DEBUG
		fprintf(debugFile, "\t===Y Index Info===\n");
		fprintf(debugFile, "\tcurY : %f, Pixel Y Index : %d\n", curY, pixelYIndex);
		fprintf(debugFile, "\t\t======Draw Line=====\n");
		fprintf(debugFile, "\t\tcurLeftX : %f, curRightX : %f\n",curLeftX, curRightX);
		fprintf(debugFile, "\t\tleftPointX : %d, rightPointX : %d\n",leftPointX, rightPointX);
		fprintf(debugFile, "\t\tDrawPixel Count : %d\n", rightPointX - leftPointX + 1);
#endif;
		for (int j = leftPointX; j <= rightPointX; j++)
		{
			if (j > APP_WIDTH / 2 || j < -APP_WIDTH / 2 || curY > APP_HEIGHT / 2 || curY < -APP_HEIGHT / 2)
			{
				continue;
			}
			Vertex newVertex = InterporateVertex(Vector2(curLeftX, curY), vertexes, area);
			float interporatedZ = GetZinterporateValue(Vector2(j, curY), vertexes, area);
			int bufferIndex = j + (APP_WIDTH / 2) + APP_HEIGHT * (pixelYIndex + APP_HEIGHT / 2);
			if (mDepthBuffer[bufferIndex] < interporatedZ)
			{
				continue;
			}
			mDepthBuffer[bufferIndex] = interporatedZ;

			Vector2 sampledPos(newVertex.UV.GetX() * (mTextureAsset.GetTextureWidth()),
				newVertex.UV.GetY() * (mTextureAsset.GetTextureHeight()));

			int newTexelIndex = static_cast<int>(sampledPos.GetY()) * mTextureAsset.GetTextureWidth()
				+ static_cast<int>(sampledPos.GetX()) - 1;
			assert(newTexelIndex < mTextureAsset.GetTextureWidth() * mTextureAsset.GetTextureHeight());
		 newVertex = InterporateVertex(Vector2(j, curY), vertexes, area);

			Color24 texel = textureDatas[newTexelIndex];
			mGDIHelper->SetColor(newVertex.UV.GetX() * 255, newVertex.UV.GetY() * 255, 0);
			
			DrawPixel(j, pixelYIndex);
		}
#ifdef DEBUG
		fprintf(debugFile, "\t\t====Draw Line End ====\n");
#endif // DEBUG
		curY += fillDir;
		curLeftX += leftdX;
		curRightX += rightdX;
	}
#ifdef DEBUG
	fclose(debugFile);
#endif // DEBUG
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

float SoftRenderer::GetZinterporateValue(Vector2& point, const Vertex* const vertexes, float area)
{
	const Vector4 a = vertexes[1].Position - vertexes[0].Position;
	const Vector4 b = vertexes[2].Position - vertexes[0].Position;
	const Vector4 p = Vector4(point.GetX(), point.GetY(), 0.0f, 0.0f) - vertexes[0].Position;
	float weightC = a.GetX() * p.GetY() - p.GetX() * a.GetY();
	weightC /= area * 2;
	weightC = abs(weightC);
	float weightB = b.GetX() * p.GetY() - p.GetX() * b.GetY();
	weightB /= area * 2;
	weightB = abs(weightB);
	float weightA = 1 - weightC - weightB;
	float newZ = (1 / vertexes[0].Position.GetZ()) * weightA +
		(1 / vertexes[1].Position.GetZ()) * weightB +
		(1 / vertexes[2].Position.GetZ()) * weightC;
	newZ = 1 / newZ;
 	return newZ;

}

void SoftRenderer::ClearDephtBuffer()
{
	u32 bufferLength = APP_WIDTH * APP_HEIGHT;
	for (int i = 0; i < bufferLength; i++)
	{
		mDepthBuffer[i] = 1;
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
	UINT totalFaceCount = model.GetVerticesLength() / 3;
	float colorPerFace = 255 / (float)totalFaceCount;
	for (int i = 0; i < model.GetVerticesLength(); i += 3)
	{
		triVertex[0] = vertexes[i];
		triVertex[1] = vertexes[i + 1];
		triVertex[2] = vertexes[i + 2];
		
		for (int i = 0; i < 3; i++)
		{
			Vector4 newPos = MVPmat * triVertex[i].Position;
			newPos = newPos * (1 / newPos.GetW());
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
		//float currentColor = colorPerFace * i / 3;
		//mGDIHelper->SetColor(currentColor, currentColor, currentColor);
		DrawTri(triVertex);

	}

}

void SoftRenderer::UpdateFrame()
{
	mGDIHelper->SetColor(32, 128, 255);
	mGDIHelper->Clear();
	ClearDephtBuffer();
	DrawObject(mObject);
	mObject.EulerAngle = mObject.EulerAngle + Vector3(0.0f, 2.0f, 0.0f);
	mObject.Position = mObject.Position + Vector4(10.0f, 0.0f, 0.0f, 0.0f);
	mGDIHelper->BufferSwap();
	return;
} 