#pragma once

class Drawable : public Object
{
public:
	Drawable& operator=(const Drawable& other);

public:
	Drawable(const Vector2& position, const Vector2& scale, const float& rotation, const wstring& shaderPath, const Color& color = RED);
	Drawable(const Drawable& other) : Object(other) { *this = other; }
	virtual ~Drawable() override;

	wstring GetShaderPath() { return shaderPath; }
	wstring GetShaderPath() const { return shaderPath; }
	Color GetColor() { return color; }
	Color GetColor() const { return color; }

	void SetColor(const Color& color)
	{
		this->color = color;
		CB->SetColor(color);
	}

	virtual void Update() override;
	virtual void Render() override;

protected:
	void DrawCall(const D3D11_PRIMITIVE_TOPOLOGY& topology, const bool& indexed);

protected:
	VertexBuffer* VB = nullptr;
	VertexShader* VS = nullptr;

	vector<UINT> indices;
	IndexBuffer* IB = nullptr;

	InputLayout* IL = nullptr;

	PixelShader* PS = nullptr;

	wstring shaderPath = L"";
	
	Color color;
	ColorBuffer* CB = nullptr;
};