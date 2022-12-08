#pragma once

#include "IShader.h"

class PixelShader : public IShader
{
public:
	virtual ~PixelShader() override;

	ID3D11PixelShader* GetResource() { return shader; }
	ID3DBlob* GetBlob() { return blob; }

	void Create(const wstring& path, const string& entryName) override;
	void Clear() override;
	void SetShader() override;

private:
	ID3D11PixelShader* shader = nullptr;
	ID3DBlob* blob = nullptr;
};
