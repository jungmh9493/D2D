#pragma once

class IShader
{
public:
	virtual ~IShader() = default;

	virtual void Create(const wstring& path, const string& entryName) = 0;
	virtual void Clear() = 0;
	virtual void SetShader() = 0;

protected:
	void CompileShader(const wstring& path, const string& entryName, 
		const string& profile, ID3DBlob** blob);

	wstring path = L"";
	string entryName = "";


private:
	void CheckShaderError(const HRESULT& hr, ID3DBlob* error);
};