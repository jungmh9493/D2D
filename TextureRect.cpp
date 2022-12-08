#include "stdafx.h"
#include "TextureRect.h"

TextureRect::TextureRect(const Vector2& position, const Vector2& scale, const float& rotation, const wstring& texturePath)
	: Drawable(position, scale, rotation, L"../_Shaders/VertexTexture.hlsl"), texturePath(texturePath)
{
	colliderType = COLLIDER_RECT;

	vertices.assign(4, VertexTexture());
	vertices[0].position = Vector2(-0.5f, -0.5f);
	vertices[0].uv = Vector2(0.0f, 1.0f);
	vertices[1].position = Vector2(-0.5f, 0.5f);
	vertices[1].uv = Vector2(0.0f, 0.0f);
	vertices[2].position = Vector2(0.5f, -0.5f);
	vertices[2].uv = Vector2(1.0f, 1.0f);
	vertices[3].position = Vector2(0.5f, 0.5f);
	vertices[3].uv = Vector2(1.0f, 0.0f);

	indices = { 0, 1, 2, 2, 1, 3 };

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexTexture::descs, VertexTexture::count, VS->GetBlob());

	if (texturePath != L"")
		SetSRV(texturePath);

	// Create BlendState
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

		desc.AlphaToCoverageEnable = false;		// 안티 에일리어싱 관련

		desc.IndependentBlendEnable = false;	// 블렌드 옵션을 각각의 렌더타겟이 따로 가질것인지를 결정
		// false 설정 -> RenderTarget[0]의 설정을 다른 렌더타깃이 공유한다.
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;		// -> src의 컬러를 어느정도 비중으로 넣어줄것인지 결정
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;	// -> dest의 컬러를 어느정도 비중으로 넣어줄것인지 결정
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;			// BlendOp = Blend Operator

		// BlendState => 가장 후순위 OM에서 Set해준다.
		// color = (srcColor * srcBlend) BlendOp (destColor * destBlend)
		// D3D11_BLEND_INV_SRC_ALPHA = 1 - D3D11_BLEND_SRC_ALPHA;
		// alpha = (srcAlpha * srcBlendAlpha) BlendOp (destAlpha * destBlendAlpha)
		// 
		// 기본값 -> 따로 알파값을 건드리지 않겠다.
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // 특정 채널 색상만 출력하게 할 수 있는 옵션

		HRESULT hr = DEVICE->CreateBlendState(&desc, &blendState);
		CHECK(hr);
	}
}

TextureRect::~TextureRect()
{
	SAFE_RELEASE(blendState);

	SAFE_RELEASE(srv);
}

void TextureRect::Update()
{
	SUPER::Update();
}

void TextureRect::Render()
{
	SUPER::Render();

	DC->PSSetShaderResources(0, 1, &srv);

	DC->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, true);
}

void TextureRect::SetSRV(const wstring& texturePath)
{
	this->texturePath = texturePath;

	ScratchImage image;
	LoadFromWICFile(texturePath.c_str(), WIC_FLAGS_NONE, nullptr, image);

	HRESULT hr = CreateShaderResourceView
	(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);
	CHECK(hr);
}
