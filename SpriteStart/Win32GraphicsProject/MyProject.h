#ifndef _MyProject_h
#define _MyProject_h

#include "DirectX.h"
#include "Font.h"
#include "TextureType.h"

namespace DirectX { class SpriteBatch; }

//----------------------------------------------------------------------------------------------
// Main project class
//	Inherits the directx class to help us initalize directX
//----------------------------------------------------------------------------------------------

class MyProject : public DirectXClass
{
public:
	// constructor
	MyProject(HINSTANCE hInstance);
	~MyProject();

	// Initialize any fonts we need to use
	void InitializeFonts();

	//Initialize textures we want to use
	void InitializeTextures();



	// window message handler
	LRESULT ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam);

	// Called by the render loop to render a single frame
	void Render(void);

private:

	//FONT Members
	FontType timesNewRoman24Bold;

	//Texture members
	TextureType  flowerTexture;
	TextureType  fireworkTexture;
	TextureType penguinTexture;
	
	int mouseX;
	int mouseY;
	bool buttonDown;

	std::wstring message;

	DirectX::SpriteBatch *spriteBatch;
};

#endif