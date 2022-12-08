#pragma once

class TextureRect : public Drawable
{
public:
	TextureRect(const Vector2& position, const Vector2& scale, const float& rotation, const wstring& texturePath = L"");
	virtual ~TextureRect();

	virtual void Update() override;
	virtual void Render() override;

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetSRV(const wstring& texturePath);

private:
	vector<VertexTexture> vertices;
	ID3D11ShaderResourceView* srv = nullptr;
	wstring texturePath = L"";

	ID3D11BlendState* blendState = nullptr;
};