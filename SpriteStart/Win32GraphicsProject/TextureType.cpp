//
// 2D Texture class
//
#include "TextureType.h"
#include "DirectX.h"
#include <WICTextureLoader.h> //loads bmp, jpgs etc...
#include <DDSTextureLoader.h>


//------------------------------------------------------------------------------------------
//Constructor
//
TextureType::TextureType()
{
	pTexture = NULL;
}

//------------------------------------------------------------------------------------------
//Destructor
//
TextureType::~TextureType()
{
	UnloadTexture();
}

//------------------------------------------------------------------------------------------
//Load the texture from the disk
//
bool TextureType::LoadTexture(ID3D11Device* device, const wchar_t* fileName)
{
	//store true if the load was succesful, false if it was not
	bool loadResult = false;
	//need a system variable to store the result of the system  load (if there is an error this will tell us what happened)
	HRESULT errorCode;

	//First check to see if we have already loaded the texture, if we have unload it before we load a new one
	if (pTexture != NULL)
	{
		UnloadTexture();
	}
	//save the path to the file name
	filePath = fileName;
	
	//load the texture
	errorCode = DirectX::CreateWICTextureFromFile(device, fileName, (ID3D11Resource **)&pTexture, &pView);

	//if it is loaded properly then set loadResult to true
	if (errorCode == S_OK)
	{
		loadResult = true;
	}

	//Get the descritpion from the texture that was just loaded
	pTexture->GetDesc(&desc);

	return loadResult;
}


//---------------------------------------------------------------------------
// Unloads the texture
//
void TextureType::UnloadTexture()
{
	SAFE_RELEASE(pTexture);
	SAFE_RELEASE(pView);
}

//---------------------------------------------------------------------------
// Draw Texture
//
void TextureType::Draw(ID3D11DeviceContext *deviceContext, ID3D11Texture2D *drawTo, int destX, int destY)
{
	// if we aren't loaded
	if (pTexture == NULL)
	{
		return;
	}

	// get the width and height of what we are drawing to
	D3D11_TEXTURE2D_DESC toDesc;
	drawTo->GetDesc(&toDesc);

	// width of the surface we are drawing to
	int toWidth = (int)toDesc.Width;
	int toHeight = (int)toDesc.Height;

	// if we are offscreen, don't draw
	if (destX >= toWidth || destY >= toHeight || destX <= -toWidth || destY <= -toHeight)
	{
		return;
	}

	int width = desc.Width;
	int height = desc.Height;

	int left = 0;
	int top = 0;

	// if we are offscreen, reduce our width
	if (destX < 0)
	{
		left = -destX;
		width = width + destX;
	}
	if (destY < 0)
	{
		top = -destY;
		height = height + destY;
	}

	// check if we are off the edge of the right screen
	if (destX + width >(int) toDesc.Width)
	{
		width = (int)toDesc.Width - destX;
	}

	if (destY + height > (int)toDesc.Height)
	{
		height = (int)toDesc.Height - destY;
	}


	// describe the sub area we want to draw to
	D3D11_BOX sourceRegion;					// box region

	sourceRegion.left = left;
	sourceRegion.right = width;
	sourceRegion.top = top;
	sourceRegion.bottom = height;
	sourceRegion.front = 0;
	sourceRegion.back = 1;

	// Copy part of a texture resource to the back buffer, or where- 
	deviceContext->CopySubresourceRegion(drawTo, 0, destX, destY, 0, pTexture, 0, &sourceRegion);


}