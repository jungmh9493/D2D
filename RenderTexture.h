#pragma once

// 사각형의 영역안에
// srv는 셰이더에서 완성된 리소스의 형태이다
// Render작업을 PreRender에서 해줄계획이다
// 그림을 그리는데 , 그려진 그림을 텍스쳐에 꽂고 그 텍스쳐로 srv를 그리게 되는 것이다
// srv에다가 해당 리소스 뷰를 꽂아주는 것이다
// 그 다음 텍스쳐를 화면크기와 동일하게 그려주는 것이다
// 그렇게 되면 화면전체에 대해서 셰이딩을 할수있는 것이다
// 그렇게 하기 위한 클래스를 만드는 중인 것이다

class RenderTexture	// 화면을 하나의 텍스쳐(그림)으로 만들어서 화면 전체에 대해 쉐이더를 사용할 수 있게 해주는 클래스
{
public:
	RenderTexture() = default;
	~RenderTexture();

	void Initialize();

	void RenderToTexture();
	void SaveTexture(const wstring& path);

	ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
	ID3D11Texture2D* renderTargetTexture = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	ID3D11ShaderResourceView* srv = nullptr;
};