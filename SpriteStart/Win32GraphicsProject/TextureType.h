#pragma once

#include <string>
#include <d3d11_1.h>  //inlude the Direct X inlude file

class TextureType
{
public:
	//constructor/destructor
	TextureType();
	~TextureType();

	//Initialize Textur / Load Texture -- loads the texture from disk
	bool LoadTexture(ID3D11Device * device, const wchar_t* fileName);
	void UnloadTexture();

	//draw the texture to a resource
	void Draw(ID3D11DeviceContext *deviceContext, ID3D11Texture2D *drawTo, int destX, int destY);

	//return shader resource view texture
	ID3D11ShaderResourceView* GetView() { return pView; }

	//return height and width of textures
	int GetWidth() { return desc.Width; }
	int GetHeight() { return desc.Height; }


private:
	ID3D11Texture2D*			pTexture;	//the directX interface to the texture
	ID3D11ShaderResourceView*	pView;		// our description when using with shaders
	
	std::wstring filePath;					//location of the texture file (.jpg, .png etc..)

	D3D11_TEXTURE2D_DESC desc;				//Description of our texture

};

