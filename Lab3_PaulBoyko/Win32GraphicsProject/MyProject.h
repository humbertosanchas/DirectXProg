#ifndef _MyProject_h
#define _MyProject_h

#include <sstream>
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

	void InitExplosion();

	void MoveAsteroids(float deltaTime);
	void MoveShip(float deltaTime);
	bool TestCollision(Sprite &a, Sprite &b);

	void InitializeFonts();
	

private:
	// textures and sprites go here
	TextureType backGroundTex;
	TextureType rockTex;
	TextureType shipTex;
	TextureType explosionTex;
	 
	//fonts
	FontType timesNewRoman24Bold;

	//sprites
	Sprite explosion;
	Sprite ship;
	Sprite astroids[NUM_OF_ASTROIDS];

	//array of random colours
	const Color colours[NUM_OF_COLOURS] = {DirectX::Colors::Red.v, DirectX::Colors::Blue.v, DirectX::Colors::Green.v, DirectX::Colors::Yellow.v, DirectX::Colors::White.v };	

	// sprite batch 
	DirectX::SpriteBatch* spriteBatch;

	// mouse variables
	Vector2 mousePos;
	bool buttonDown;

	// status message
	std::wstring message;

	// call when the mouse is released
	void OnMouseDown();


	//return a colour from the array
	DirectX::SimpleMath::Color GenerateRandColour();

	//Creates a Random Scale
	float GenerateRandScale();

	//Generate Random X and Y's'
	float GenerateRandX();

	//movement score and and flag values
	float shipVelocityX;
	float shipVelocityY;
	float shipSpeed;
	int score;
	bool isRed;
	double timer;
	
	//output string
	std::wostringstream scoreString;



};

#endif