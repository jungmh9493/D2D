#pragma once

// �簢���� �����ȿ�
// srv�� ���̴����� �ϼ��� ���ҽ��� �����̴�
// Render�۾��� PreRender���� ���ٰ�ȹ�̴�
// �׸��� �׸��µ� , �׷��� �׸��� �ؽ��Ŀ� �Ȱ� �� �ؽ��ķ� srv�� �׸��� �Ǵ� ���̴�
// srv���ٰ� �ش� ���ҽ� �並 �Ⱦ��ִ� ���̴�
// �� ���� �ؽ��ĸ� ȭ��ũ��� �����ϰ� �׷��ִ� ���̴�
// �׷��� �Ǹ� ȭ����ü�� ���ؼ� ���̵��� �Ҽ��ִ� ���̴�
// �׷��� �ϱ� ���� Ŭ������ ����� ���� ���̴�

class RenderTexture	// ȭ���� �ϳ��� �ؽ���(�׸�)���� ���� ȭ�� ��ü�� ���� ���̴��� ����� �� �ְ� ���ִ� Ŭ����
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