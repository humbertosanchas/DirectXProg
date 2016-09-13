#include "Texture.h"

Texture2DType::Texture2DType()
{
	pTexture = NULL;
}

Texture2DType::~Texture2DType()
{
	pTexture->Release();
}

bool Texture2DType::Load(ID3D11Device* device, const wchar_t* fileName)
{		
	HRESULT result = DirectX::CreateWICTextureFromFile(device, fileName, (ID3D11Resource**)&pTexture, NULL);
	if (result != S_OK)
	{
		return false;
	}
	return true;
}

void Texture2DType::Draw(ID3D11DeviceContext* context, int x, int y)
{

}