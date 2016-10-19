#ifndef _MyProject_h
#define _MyProject_h

#include "DirectX.h"
#include "Font.h"
#include "TextureType.h"
#include "Sprite.h"

// forward declare the sprite batch
namespace DirectX { class SpriteBatch; };

//----------------------------------------------------------------------------------------------
// Main project class
//	Inherits the directx class to help us initalize directX
//----------------------------------------------------------------------------------------------

class MyProject : public DirectXClass
{
public:
	static const int NUM_OF_ASTROIDS = 10;
	static const int NUM_OF_COLOURS = 5;

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

	void InitShip();

	void InitAsteroids();

	void MoveAsteroids(float deltaTime);

private:
	// textures and sprites go here
	TextureType backGroundTex;
	TextureType rockTex;
	TextureType shipTex;
	TextureType explosionTex;


	Sprite ship;
	Sprite astroids[NUM_OF_ASTROIDS];
	const Color colours[NUM_OF_COLOURS] = {DirectX::Colors::Red.v, DirectX::Colors::Blue.v, DirectX::Colors::Green.v, DirectX::Colors::Yellow.v, DirectX::Colors::White.v };

	/*Sprite astroid;*/

	// sprite batch 
	DirectX::SpriteBatch* spriteBatch;

	// mouse variables
	Vector2 mousePos;
	bool buttonDown;

	// status message
	std::wstring message;

	// call when the mouse is released
	void OnMouseDown();

	DirectX::SimpleMath::Color GenerateRandColour();

	float GenerateRandScale();

	float GenerateRandX();

	float shipVelocityX;
	float shipVelocityY;
	float shipSpeed;



};

#endif