#include "stdafx.h"
#include "Graphics.h"

Graphics* Graphics::instance = nullptr;

Graphics::Graphics()
{
	EnumerateAdapters();
	CreateSwapChain();
}

Graphics::~Graphics()
{
	for (D3DEnumAdapterInfo* adapterInfo : adapterInfos)
		SAFE_DELETE(adapterInfo);

	SAFE_RELEASE(rtv);
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}

void Graphics::Resize(const float& width, const float& height)
{
	DeleteSurface();
	{
		HRESULT hr = swapChain->ResizeBuffers
		(
			0,
			(UINT)gWinWidth,
			(UINT)gWinHeight,
			DXGI_FORMAT_UNKNOWN,
			0
		);
		CHECK(hr);
	}
	CreateRenderTargetView();
	SetViewport(width, height);

	cout << width << " X " << height << '\n';
}

void Graphics::SetViewport(const float& width, const float& height)
{
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}

void Graphics::SetViewport()
{
	deviceContext->RSSetViewports(1, &viewport);
}

void Graphics::SetBackbufferToRTV()
{
	deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
	deviceContext->ClearRenderTargetView(rtv, clearColor);
}

void Graphics::Begin()
{
	SetViewport();
	SetBackbufferToRTV();
}

void Graphics::End()
{
	HRESULT hr = swapChain->Present(1, 0);
	CHECK(hr);

}

void Graphics::CreateSwapChain()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(swapChain);


	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;

	if (bVsync)	// ���� ����ȭ : FPS�� ȭ�� �ֻ����� ��ġ��Ű�� ��� (ȭ�� �ֻ����� fps�� ���� ������ �� ������ �Ͼ �� �ִ�.)
	{
		//adapterInfos[0] : �� ��� �׷��� ī��
		desc.BufferDesc.RefreshRate.Numerator = adapterInfos[0]->outputInfo->numerator;		// ����
		desc.BufferDesc.RefreshRate.Denominator = adapterInfos[0]->outputInfo->denominator;	// �и�
	}
	else
	{
		desc.BufferDesc.RefreshRate.Numerator = 0;	// 0���� ���� -> ������ ���� �ʴ´�.
		desc.BufferDesc.RefreshRate.Denominator = 1;
	}

	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// UROM : Unsigned Normalized

	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	desc.BufferCount = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	// sampling -> �⺻�� ����
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.OutputWindow = gHandle;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
	creationFlags = D3DCOMPILE_PREFER_FLOW_CONTROL | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	vector<D3D_FEATURE_LEVEL> featurelevel
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT maxVideoMemory = 0;
	for (UINT i = 0; i < adapterInfos.size(); ++i)
	{
		// DedicatedVideoMemory : VRAM(���� ���� �޸�)�� �޸� ũ�Ⱑ �� ��������
		if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory > maxVideoMemory)
		{
			selectedAdapterIndex = i;
			maxVideoMemory = (UINT)adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
		}
	}

	numerator = adapterInfos[0]->outputInfo->numerator;
	denominator = adapterInfos[0]->outputInfo->denominator;

	gpuMemorySize = maxVideoMemory / 1024 / 1024;
	gpuDescription = adapterInfos[selectedAdapterIndex]->adapterDesc.Description;

	cout << "DedicatedVideoMemory : " << gpuMemorySize << '\n';
	wcout << "GPU Description : " << gpuDescription << '\n';

	cout << "Numerator : " << numerator << '\n';
	cout << "Denominator : " << denominator << '\n';
	cout << "RefreshRate : " << numerator / denominator << '\n';

	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featurelevel.data(),
		(UINT)featurelevel.size(),
		D3D11_SDK_VERSION,
		&desc,
		&swapChain,
		&device,
		nullptr,
		&deviceContext
	);
	CHECK(hr);

	Resize(gWinWidth, gWinHeight);
}

void Graphics::CreateRenderTargetView()
{
	ID3D11Texture2D* backBuffer = nullptr;

	HRESULT hr = swapChain->GetBuffer
	(
		0,							// ���° buffer�� ������ ������
		__uuidof(ID3D11Texture2D),	// __uuidof : GUID �˻�, ��ȯ / GUID ã�ƺ���
		(void**)&backBuffer
	);
	CHECK(hr);

	hr = device->CreateRenderTargetView
	(
		backBuffer,
		nullptr,	// �̹� swapChain���� �޾ƿԱ� ������ ���� ������ �ʿ䰡 ����
		&rtv
	);
	CHECK(hr);

	//	backBuffer->Release();	// ������ ���� ��û �߱� ������, ������ ������ ��û�� ���� �����ؾ��Ѵ�.
	SAFE_RELEASE(backBuffer);
}

void Graphics::DeleteSurface()
{
	SAFE_RELEASE(rtv);
}

void Graphics::EnumerateAdapters()
{
	IDXGIFactory1* factory;		// IDXGIFactory �ڿ� ���� �ѹ��� ������ ���� ���̴�. -> IDXGI 1.1�� ����Ʈ�Ǵ°��� Factory1 �̴�.
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory)))
		return;

	UINT index = 0;
	while (true)
	{
		IDXGIAdapter1* adapter;
		HRESULT hr = factory->EnumAdapters1(index, &adapter);	// EnumAdapter -> �׷��� ī�� ������ �����ض�(���� �׷���, ���� �׷���)

		if (hr == DXGI_ERROR_NOT_FOUND)	// ERROR_NOT_FOUND : �� ã�Ҵٴ� ����
			break;

		CHECK(hr);

		D3DEnumAdapterInfo* adapterInfo = new D3DEnumAdapterInfo();
		ZeroMemory(adapterInfo, sizeof(D3DEnumAdapterInfo));
		adapterInfo->adapterOrdinal = index;
		adapter->GetDesc1(&adapterInfo->adapterDesc);
		adapterInfo->adapter = adapter;

		EnumerateAdapterOutput(adapterInfo);
		adapterInfos.push_back(adapterInfo);

		++index;
	}

	SAFE_RELEASE(factory);
}

bool Graphics::EnumerateAdapterOutput(D3DEnumAdapterInfo* adapterInfo)
{
	IDXGIOutput* output = nullptr;
	HRESULT hr = adapterInfo->adapter->EnumOutputs(0, &output);	// EnumOutputs -> �׷��� ī�忡 ����Ǿ� �ִ� ����� ������ �����ض�

	if (hr == DXGI_ERROR_NOT_FOUND)
		return false;

	D3DEnumOutputInfo* outputInfo = new D3DEnumOutputInfo();
	ZeroMemory(outputInfo, sizeof(D3DEnumOutputInfo));

	hr = output->GetDesc(&outputInfo->outputDesc);
	CHECK(hr);

	outputInfo->output = output;

	UINT numModes = 0;
	DXGI_MODE_DESC* displayModes = nullptr;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	CHECK(hr);

	displayModes = new DXGI_MODE_DESC[numModes];
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes);
	CHECK(hr);

#pragma warning (disable : 6385)
	for (UINT i = 0; i < numModes; ++i)
	{
		resolutionList.insert(Vector2((float)displayModes[i].Width, (float)displayModes[i].Height));

		bool bCheck = true;
		bCheck &= displayModes[i].Width == gWinWidth;
		bCheck &= displayModes[i].Height == gWinHeight;

		if (bCheck == true)
		{
			outputInfo->numerator = displayModes[i].RefreshRate.Numerator;
			outputInfo->denominator = displayModes[i].RefreshRate.Denominator;
		}
	}
#pragma warning (default : 6385)

	for (const Vector2& res : resolutionList)
		cout << res.x << " X " << res.y << '\n';

	adapterInfo->outputInfo = outputInfo;
	SAFE_DELETE_ARRAY(displayModes);

	return true;
}

D3DEnumAdapterInfo::~D3DEnumAdapterInfo()
{
	SAFE_RELEASE(adapter);
	SAFE_DELETE(outputInfo);
}

D3DEnumOutputInfo::~D3DEnumOutputInfo()
{
	SAFE_RELEASE(output);
}
