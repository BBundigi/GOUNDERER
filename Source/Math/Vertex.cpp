#include "Vertex.h"
Vertex::Vertex(const Vector4& positon, const Vector3& normal, const Vector2& uv)
	: Position(positon), Normal(normal), UV(uv)
{
}

Vertex Vertex::InterporateVertex(const Vertex& first, const Vertex& second, const Vertex& third, float a, float b, float c)
{
	Vertex newVertex = Vertex(first.Position * a + second.Position * b + third.Position * c,
		first.Normal * a + second.Normal * b + third.Normal * c,
		first.UV * a + second.UV * b + third.UV * c);
	return newVertex;
}