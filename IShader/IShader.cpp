#include "IShader.h"

void IShader::CompileShader(const wstring& path, const string& entryName, const string& profile, ID3DBlob** blob)
{
	ID3DBlob* error = nullptr;
	HRESULT hr = D3DCompileFromFile
	(
		path.c_str(),
		nullptr,
		nullptr,
		entryName.c_str(),
		profile.c_str(),
		D3DCOMPILE_ENABLE_STRICTNESS, // --> �� ��Ȯ�ϰ� �˻縦 �ϰڴٴ� ���� , ���� ��ũ�ΰ� �ִ�
		0,
		blob,
		&error
	);
	CheckShaderError(hr, error);

	SAFE_RELEASE(error);

		// --> 
}

void IShader::CheckShaderError(const HRESULT& hr, ID3DBlob* error)
{
	if (FAILED(hr)) // --> FAILED�ص� ������ �ȶ߸� ���� �̻��� �ִ� ����
	{
		if (error)
		{
			const string& str = (const char*)error->GetBufferPointer();
			MessageBoxA(nullptr, str.c_str(), "Shader Error", MB_OK); // --> OK��ư�� �ִ� �޽����ڽ��� ���ڴٴ� ����
		}
		assert(false);
	}
}
