#ifndef _MyProject_h
#define _MyProject_h

#include "DirectX.h"
#include "Font.h"
#include "TextureType.h"
#include "Sprite.h"

//Paul Boyko Oct 2016
// forward declare the sprite batch
namespace DirectX { class SpriteBatch; };

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

	// Initialize any Fonts we need to use
	void InitializeFonts();

	// Initialize any Textures we need to use
	void InitializeTextures();

	// window message handler
	LRESULT ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam);

	// Called by the render loop to render a single frame
	void Render(void);

	// Called by directX framework to allow you to update any scene objects
	void Update(float deltaTime);

	//Layout all controls
	void ViewLayout();

private:
	// textures and sprites go here
	



	// sprite batch 
	DirectX::SpriteBatch* spriteBatch;

	// mouse variables
	Vector2 mousePos;
	bool buttonDown;

	// status message
	std::wstring message;

	//called if mouse eneter a button
	void OnMouseEnter();

	// call when the mouse is pressed
	void OnMouseDown();

	// call when the mouse is released
	void OnMouseUp();
	
	//Fonts
	FontType verdana24;	

	//Sprites
	TextureType blueSheet;
	TextureType greenSheet;
	TextureType yellowSheet;
	TextureType background;
	TextureType fizzyPlankton;

	
	Sprite btnPressed;
	Sprite btnClicked;
	
	Sprite arrowRight;
	Sprite arrowLeft;
	

	Sprite btnTop;
	Sprite btn2ndTop;
	Sprite btnMiddle;
	Sprite btn2ndBottom;
	Sprite btnBottom;	

	Sprite fizy;
};

#endif