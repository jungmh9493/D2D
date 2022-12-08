#pragma once

class D3DEnumAdapterInfo;
class D3DEnumOutputInfo;

class Graphics
{
	DECLARE_SINGLETON(Graphics);

private:
	// COM Interface
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };

	UINT numerator = 0;
	UINT denominator = 1;

	UINT gpuMemorySize = 0;
	wstring gpuDescription = L"";
	vector<D3DEnumAdapterInfo*> adapterInfos;
	int selectedAdapterIndex = 0;

	bool bVsync = true;

	set<Vector2> resolutionList;

public:
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDC() { return deviceContext; }
	Color GetClearColor() { return clearColor; }

	void Resize(const float& width, const float& height);
	void SetViewport(const float& width, const float& height);
	void SetViewport();
	void SetBackbufferToRTV();

	void Begin();
	void End();

private:
	void CreateSwapChain();
	void CreateRenderTargetView();
	void DeleteSurface();

private:
	void EnumerateAdapters();
	bool EnumerateAdapterOutput(D3DEnumAdapterInfo* adapterInfo);
};

class D3DEnumAdapterInfo
{
public:
	D3DEnumAdapterInfo() = default;
	~D3DEnumAdapterInfo();

	UINT adapterOrdinal = 0;
	IDXGIAdapter1* adapter = nullptr;	// adapter : 그래픽 카드
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	D3DEnumOutputInfo* outputInfo = nullptr;
};

class D3DEnumOutputInfo
{
public:
	D3DEnumOutputInfo() = default;
	~D3DEnumOutputInfo();

	IDXGIOutput* output = nullptr;
	DXGI_OUTPUT_DESC outputDesc = { 0 };

	UINT numerator = 0;
	UINT denominator = 1;
};