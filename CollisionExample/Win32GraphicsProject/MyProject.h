#ifndef _MyProject_h
#define _MyProject_h

#include "DirectX.h"
#include "Font.h"
#include "TextureType.h"
#include "Sprite.h"
#include "Collision2D.h"

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

	// Initialize any Textures we need to use
	void InitializeTextures();

	// window message handler
	LRESULT ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam);

	// Called by the render loop to render a single frame
	void Render(void);

	// Called by directX framework to allow you to update any scene objects
	void Update(float deltaTime);

private:
	// textures and sprites go here
	TextureType backGroundTex;
	TextureType ballTex;
	TextureType blockTex;

	Sprite ballSprite;
	Vector2 ballVelocity;

	static const int NUM_BLOCKS = 4;
	Sprite blocks[NUM_BLOCKS];

	// sprite batch 
	DirectX::SpriteBatch* spriteBatch;

	// mouse variables
	Vector2 mousePos;
	bool buttonDown;

	// call when the mouse is released
	void OnMouseDown();

};

#endif