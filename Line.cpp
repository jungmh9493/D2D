#include "stdafx.h"
#include "Line.h"

Line::Line(const Vector2& position, const float& length, const float& rotation, const Color& color)
	: Drawable(position, Vector2(length, 0), rotation, L"../_Shaders/Vertex.hlsl", color)
{
	vertices.assign(2, Vertex());
	vertices[0].position = Vector2(0, 0);
	vertices[1].position = Vector2(1, 0);

	IL->Create(Vertex::descs, Vertex::count, VS->GetBlob());

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);
}

void Line::Update()
{
	SUPER::Update();
}

void Line::Render()
{
	SUPER::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINELIST, false);
}
