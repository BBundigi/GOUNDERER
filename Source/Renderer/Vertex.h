#include "Vector2.h"
#pragma once
class Vertex
{
public :
	static Vertex InterporateVertex(const Vertex& first,
		const Vertex& second,
		const Vertex& third, float a, float b, float c);


	Vertex() = default;
	Vertex(const Vector2& positon, const Vector2& uv);
	inline Vector2 GetPosition() const;
	inline Vector2 GetUV() const;
	
private :
	Vector2 mPosition;
	Vector2 mUV;
};

Vector2 Vertex::GetPosition() const
{
	return mPosition;
}
Vector2 Vertex::GetUV() const
{
	return mUV;
}

