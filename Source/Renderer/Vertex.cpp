#include "Vertex.h"
Vertex::Vertex(const Vector2& positon, const Vector2& uv)
{
	mPosition = positon;
	mUV = uv;
}

Vertex Vertex::InterporateVertex(const Vertex& first, const Vertex& second, const Vertex& third, float a, float b, float c)
{
	Vertex newVertex = Vertex(first.GetPosition() * a + second.GetPosition() * b + third.GetPosition() * c,
		first.GetUV() * a + second.GetUV() * b + third.GetUV() * c);
	return newVertex;
}