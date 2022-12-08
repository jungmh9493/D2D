#pragma once

struct Vertex
{
	Vertex() = default;
	Vertex(const Vector2& position) : position(position) {}

	Vector2 position;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 1;
};

struct VertexColor
{
	VertexColor() = default;
	VertexColor(const Vector2& position, const Vector2& color)
		: position(position), color(color)
	{}

	Vector2 position;
	Color color;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 2;
};

struct VertexTexture
{
	VertexTexture() = default;
	VertexTexture(const Vector2& position, const Vector2& uv)
		: position(position), uv(uv)
	{}

	Vector2 position;
	Vector2 uv;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 2;
};