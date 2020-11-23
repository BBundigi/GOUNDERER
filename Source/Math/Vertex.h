#include <cassert>
#pragma once
#include "Vector2.h";
#include "Vector3.h";
#include "Vector4.h";
class Vertex
{
public :
	static Vertex InterporateVertex(const Vertex& first,
		const Vertex& second,
		const Vertex& third, float a, float b, float c);


	Vertex() = default;
	Vertex(const Vector4& positon, const Vector3& Normal, const Vector2& uv);
	Vector4 Position;
	Vector3 Normal;
	Vector2 UV;
	
private :
};


