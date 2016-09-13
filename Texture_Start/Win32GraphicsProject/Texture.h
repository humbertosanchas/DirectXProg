#pragma once
#include "DirectX.h"
#include <WICTextureLoader.h>

class Texture2DType
{
	public:		
		Texture2DType();
		~Texture2DType();

		bool Load(ID3D11Device* device, const wchar_t* fileName);
		void Draw(ID3D11DeviceContext* context, int x, int y);
		void SetRegion(int left, int right, int top, int bottom);

		int GetWidth();
		int GetHeight();

	private:
		ID3D11Texture2D *pTexture;
};
