#include "stdafx.h"
#include "Drawable.h"

Drawable& Drawable::operator=(const Drawable& other)
{
	SAFE_DELETE(CB);

	SAFE_DELETE(PS);

	SAFE_DELETE(IL);

	SAFE_DELETE(IB);
	SAFE_DELETE(VS);
	SAFE_DELETE(VB);

	shaderPath = other.shaderPath;
	color = other.color;

	VB = new VertexBuffer();
	VS = new VertexShader();
	VS->Create(shaderPath, "VS");
	IB = new IndexBuffer();

	IL = new InputLayout();

	PS = new PixelShader();
	PS->Create(shaderPath, "PS");

	CB = new ColorBuffer();
	CB->SetColor(color);

	return *this;
}

Drawable::Drawable(const Vector2& position, const Vector2& scale, const float& rotation, const wstring& shaderPath, const Color& color)
	: Object(position, scale, rotation), shaderPath(shaderPath), color(color)
{
	VB = new VertexBuffer();
	VS = new VertexShader();
	VS->Create(shaderPath, "VS");
	IB = new IndexBuffer();

	IL = new InputLayout();

	PS = new PixelShader();
	PS->Create(shaderPath, "PS");

	CB = new ColorBuffer();
	CB->SetColor(color);
}

Drawable::~Drawable()
{
	SAFE_DELETE(CB);

	SAFE_DELETE(PS);

	SAFE_DELETE(IL);

	SAFE_DELETE(IB);
	SAFE_DELETE(VS);
	SAFE_DELETE(VB);
}

void Drawable::Update()
{
	SUPER::Update();			// __super : 기반 클래스(부모 클래스)를 의미
}

void Drawable::Render()
{
	SUPER::Render();

	VB->SetIA();
	if (indices.size() > 0)
		IB->SetIA();
	IL->SetIA();

	VS->SetShader();

	CB->SetPSBuffer(0);
	PS->SetShader();
}

void Drawable::DrawCall(const D3D11_PRIMITIVE_TOPOLOGY& topology, const bool& indexed)
{
	DC->IASetPrimitiveTopology(topology);

	if (indexed)
		DC->DrawIndexed(IB->GetCount(), 0, 0);
	else
		DC->Draw(VB->GetCount(), 0);
}
