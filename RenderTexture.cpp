#include "stdafx.h"
#include "RenderTexture.h"

RenderTexture::~RenderTexture()
{
	SAFE_RELEASE(srv);
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(renderTargetTexture);
}

void RenderTexture::Initialize()
{
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&rtvDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	textureDesc.Width = (UINT)gWinWidth;
	textureDesc.Height = (UINT)gWinHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	HRESULT hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, &renderTargetTexture);
	CHECK(hr);

	rtvDesc.Format = textureDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	hr = DEVICE->CreateRenderTargetView(renderTargetTexture, &rtvDesc, &rtv);
	CHECK(hr);

	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = DEVICE->CreateShaderResourceView(renderTargetTexture, &srvDesc, &srv);
	CHECK(hr);
}

void RenderTexture::RenderToTexture()
{
	DC->OMSetRenderTargets(1, &rtv, nullptr);
	DC->ClearRenderTargetView(rtv, GRAPHICS->GetClearColor());
}

// 전체 화면 스크린샷
void RenderTexture::SaveTexture(const wstring& path)
{
	ScratchImage image;
	CaptureTexture(DEVICE, DC, renderTargetTexture, image);

	/*
	   WIC_CODEC_BMP = 1,          // Windows Bitmap (.bmp)
	   WIC_CODEC_JPEG,             // Joint Photographic Experts Group (.jpg, .jpeg)
	   WIC_CODEC_PNG,              // Portable Network Graphics (.png)
	   WIC_CODEC_TIFF,             // Tagged Image File Format  (.tif, .tiff)
	   WIC_CODEC_GIF,              // Graphics Interchange Format  (.gif)
	   WIC_CODEC_WMP,              // Windows Media Photo / HD Photo / JPEG XR (.hdp, .jxr, .wdp)
	   WIC_CODEC_ICO,              // Windows Icon (.ico)
	   WIC_CODEC_HEIF,             // High Efficiency Image File (.heif, .heic)
	*/

	wstring ext = path.substr(path.find_last_of(L".") + 1);
	WICCodecs fileExt = WIC_CODEC_BMP;	// bmp : beat map file
	if (ext == L"jpg" || ext == L"jpeg")
		fileExt = WIC_CODEC_JPEG;
	else if (ext == L"png")
		fileExt = WIC_CODEC_PNG;
	else if (ext == L"gif")
		fileExt = WIC_CODEC_GIF;

	SaveToWICFile(image.GetImages(), image.GetImageCount(), WIC_FLAGS_NONE, GetWICCodec(fileExt), path.c_str());
}
