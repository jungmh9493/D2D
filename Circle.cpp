#include "stdafx.h"
#include "Circle.h"

Circle::Circle(const Vector2& position, const Vector2& scale, const float& rotation, const int& segments, const Color& color)
	: Drawable(position, scale, rotation, L"../_Shaders/Vertex.hlsl", color)
	, segments(segments)
{
	colliderType = COLLIDER_CIRCLE;

	vertices.assign(segments + 1, Vertex());

	for (int i = 0; i <= segments; ++i)
	{
		float theta = 2 * XM_PI * i / segments;

		vertices[i].position = Vector2(cosf(theta), -sinf(theta));
	}

	// My Code
	/*vertices.assign(36, Vertex());
	
	for (UINT i = 0; i < vertices.size(); ++i)
	{
		vertices[i].position = SetVertex((float)i * 10);
		indices.push_back(i);
	}
	indices.push_back(0);*/

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);
	//	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(Vertex::descs, Vertex::count, VS->GetBlob());
}

void Circle::Update()
{
	SUPER::Update();
}

void Circle::Render()
{
	SUPER::Render();
//	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, true);
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, false);
}

Vector2 Circle::SetVertex(const float& degrees)
{
	return Vector2(cosf(XMConvertToRadians(degrees)), sinf(XMConvertToRadians(degrees)));
}