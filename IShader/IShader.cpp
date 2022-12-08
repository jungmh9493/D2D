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
		D3DCOMPILE_ENABLE_STRICTNESS, // --> 더 정확하게 검사를 하겠다는 뜻임 , 많은 매크로가 있다
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
	if (FAILED(hr)) // --> FAILED해도 에러가 안뜨면 무슨 이상이 있는 것임
	{
		if (error)
		{
			const string& str = (const char*)error->GetBufferPointer();
			MessageBoxA(nullptr, str.c_str(), "Shader Error", MB_OK); // --> OK버튼이 있는 메시지박스를 띄우겠다는 뜻임
		}
		assert(false);
	}
}
