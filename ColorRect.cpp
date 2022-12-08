#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect(const Vector2& position, const Vector2& scale, const float& rotation, const Color& color)
	: Drawable(position, scale, rotation, L"../_Shaders/Vertex.hlsl", color)
{
	colliderType = COLLIDER_RECT;

	vertices.assign(4, Vertex());
	vertices[0].position = Vector2(-0.5f, -0.5f);
	vertices[1].position = Vector2(-0.5f, 0.5f);
	vertices[2].position = Vector2(0.5f, -0.5f);
	vertices[3].position = Vector2(0.5f, 0.5f);
	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	indices = { 0, 1, 2, 2, 1, 3 };
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(Vertex::descs, Vertex::count, VS->GetBlob());
}

void ColorRect::Update()
{
	SUPER::Update();
}

void ColorRect::Render()
{
	SUPER::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, true);
}
