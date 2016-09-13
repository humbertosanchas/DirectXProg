#ifndef _MyProject_h
#define _MyProject_h

#include "DirectX.h"
#include "Font.h"

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
	
	int mouseX;
	int mouseY;

	std::wstring message;


	//Texture members
	//create a pointer to a texture
	ID3D11Texture2D *pTexture;
	ID3D11Texture2D *pCompiling;
	
};

#endif