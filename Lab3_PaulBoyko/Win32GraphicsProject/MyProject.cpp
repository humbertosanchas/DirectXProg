// Button art reference: http://opengameart.org/content/ui-pack (public domain)
//

#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <SpriteBatch.h>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <DirectXColors.h>
#include <sstream>
#include <time.h>
#include "Collision2D.h"

//Paul Boyko Oct 2016

using namespace DirectX;
using namespace DirectX::SimpleMath;

// helper function
//
// returns a random float between 0 & 1
float RandFloat() { return float(rand())/float(RAND_MAX); } 



//----------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
	MyProject application(hInstance);    // Create the class variable
	srand((unsigned int)time(NULL));
	if( application.InitWindowsApp(L"Lab 3", nShowCmd) == false )    // Initialize the window, if all is well show and update it so it displays
	{
		return 0;                   // Error creating the window, terminate application
	}

	if( application.InitializeDirect3D() )
	{
		application.SetDepthStencil(true);      // Tell DirectX class to create and maintain a depth stencil buffer
		application.InitializeTextures();
		application.InitAsteroids();
		application.InitShip();
		application.InitializeFonts();
		application.InitExplosion();
		application.MessageLoop();	
		
		// Window has been successfully created, start the application message loop
	}
	
	return 0;
}

//----------------------------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------------------------
MyProject::MyProject(HINSTANCE hInstance)
	: DirectXClass(hInstance)
{
	message = L"Mouse was clicked here";
	mousePos = Vector2(clientWidth * 0.5f, clientHeight * 0.5f);
	buttonDown = false;
	spriteBatch = NULL;
	
	ClearColor = Color(DirectX::Colors::Black.v);
	scoreString << L"Score : 0";
	
	score = 0;
}

void MyProject::InitializeFonts()
{
	timesNewRoman24Bold.InitializeFont(D3DDevice, DeviceContext, L"..\\Font\\TimesnewRoman24Bold.spritefont");
}

//----------------------------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------------------------
MyProject::~MyProject()
{
	delete spriteBatch;
}

//----------------------------------------------------------------------------------------------
// Initialize any fonts we need to use here
//----------------------------------------------------------------------------------------------
void MyProject::InitializeTextures()
{
	// initialize the sprite batch
	spriteBatch = new DirectX::SpriteBatch( DeviceContext );

	backGroundTex.Load( D3DDevice, L"..\\Textures\\starfield.dds" );
	rockTex.Load( D3DDevice, L"..\\Textures\\RockSheet.png" );
	shipTex.Load(D3DDevice, L"..\\Textures\\ship.png");
	explosionTex.Load(D3DDevice, L"..\\Textures\\Explosion.png");

}

//----------------------------------------------------------------------------------------------
// Window message handler
//----------------------------------------------------------------------------------------------
LRESULT MyProject::ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg )
	{
		//Move using arrows and wasd stop move on no key press
		case WM_KEYDOWN:
			if (wParam == 'W' || wParam == VK_UP)
			{
				shipVelocityY = -shipSpeed;
				shipVelocityX = 0;
				break;
			}
			if (wParam == 'A' || wParam == VK_LEFT)
			{
				shipVelocityX = -shipSpeed;
				shipVelocityY = 0;
				break;
			}
			if (wParam == 'S' || wParam == VK_DOWN)
			{
				shipVelocityY = shipSpeed;
				shipVelocityX = 0;
				break;
			}
			if (wParam == 'D' || wParam == VK_RIGHT)
			{
				shipVelocityX = shipSpeed;
				shipVelocityY = 0;
				break;
			}
		case WM_KEYUP:
			shipVelocityX = 0;
			shipVelocityY = 0;
			break;
	
	}

	// let the base class handle remaining messages
	return DirectXClass::ProcessWindowMessages(msg, wParam, lParam);
}

//----------------------------------------------------------------------------------------------
// Called by the render loop to render a single frame
//----------------------------------------------------------------------------------------------
void MyProject::Render(void)
{
	backGroundTex.Draw(DeviceContext, BackBuffer, 0, 0);	
	timesNewRoman24Bold.PrintMessage(5, 5, scoreString.str(), FC_RED);

	// draw your stuff here
	spriteBatch->Begin( SpriteSortMode_BackToFront );

	for (int c = 0; c < MyProject::NUM_OF_ASTROIDS; c++)
	{
		/*Sprite astr = astroids[c];
		astr.Draw(spriteBatch);*/
		astroids[c].Draw(spriteBatch);
	}
	ship.Draw(spriteBatch);
	explosion.Draw(spriteBatch);

	// draw sprites

	spriteBatch->End();


	// render the base class
	DirectXClass::Render();
}

//----------------------------------------------------------------------------------------------
// Called every frame to update objects.
//	deltaTime: how much time in seconds has elapsed since the last frame
//----------------------------------------------------------------------------------------------
void MyProject::Update(float deltaTime)
{
	//// update the explosion
	MoveAsteroids(deltaTime);
	MoveShip(deltaTime);	

	//loop to update score and check collisons
	for (int c = 0; c < MyProject::NUM_OF_ASTROIDS; c++)
	{
		if (TestCollision(ship, astroids[c]))
		{			
			score = score - 30;
			scoreString.str(L"");
			scoreString << L"Score : " << score;
		}

		// explosion animation
		explosion.UpdateAnimation(deltaTime);
		//move frame out on last frame
		if (explosion.isLastFrame())
		{			
			explosion.SetPosition(Vector2(-2500.0f, -2500.0f));
		}	
		//make red for half second
		if (isRed)
		{
			timer = timer + 1 * deltaTime;
			if (timer >= 0.5)
			{
				ship.SetColor(Colors::White.v);
				isRed = false;
			}
		}
	}
}

//moveing the ship according to bounds
void MyProject::MoveShip(float deltaTime)
{
	if ((ship.GetPosition().y + ship.GetHeight()/2) <= clientHeight  || (ship.GetPosition().y + ship.GetHeight() / 2  + (shipVelocityY * deltaTime)) <= clientHeight)
	{
		ship.SetPosition(Vector2(ship.GetPosition().x + (shipVelocityX * deltaTime), ship.GetPosition().y + (shipVelocityY * deltaTime)));
	}	
	else
	{
		ship.SetPosition(Vector2(ship.GetPosition().x + (shipVelocityX * deltaTime), ship.GetPosition().y));
	}

	ship.UpdateAnimation(deltaTime);
}

//check if objects have collided
bool MyProject::TestCollision(Sprite &a, Sprite &b)
{
	Box2D boxA;
	Box2D boxB;
	boxA.center = a.GetPosition();
	boxA.extents = a.GetExtents();

	boxB.center = b.GetPosition();
	boxB.extents = b.GetExtents();

	if (Collision2D::BoxBoxCheck(boxA, boxB))
	{
		Circle circleB;
		circleB.center = b.GetPosition();
		circleB.radius = b.GetWidth() / 2.0f;
		if (Collision2D::BoxCircleCheck(boxA, circleB))
		{
			Circle circleA;
			circleA.center = a.GetPosition();
			circleA.radius = a.GetWidth() / 2.0f;
			if (Collision2D::CircleCircleCheck(circleA, circleB))
			{
				a.SetColor(Colors::Red.v);				
				Vector2 pos = b.GetPosition();
				explosion.SetPosition(pos);
				explosion.RestartAnimation();
				pos.y = -2.0f;
				b.SetPosition(pos);	
				isRed = true;
				timer = 0;
				return true;				
			}
		}
		else
		{
			return false;
		}
	}
	
}

//----------------------------------------------------------------------------------------------
// Called when the mouse is released
//----------------------------------------------------------------------------------------------
void MyProject::OnMouseDown()
{

	// this is called when the left mouse button is clicked
	// mouse position is stored in mousePos variable
}

//return a colour from the array
DirectX::SimpleMath::Color MyProject::GenerateRandColour()
{
	return (colours[rand() % 5]);
}

//Generate Random X and Y's'
float MyProject::GenerateRandX()
{
	return (float)(rand() % (clientWidth - 2) + 5);
}

//Creates a Random Scale
float MyProject::GenerateRandScale()
{
	return (float)((rand() % 20 + 1)*0.10f);
}

//create the ship
void MyProject::InitShip()
{
	shipSpeed = 100;
	ship.Initialize(&shipTex, Vector2(0.0f,0.0f), 0, 1, Colors::White.v, 0.0f);
	ship.SetPosition(Vector2((float)(clientWidth / 2 - ship.GetWidth() / 2), (float)(clientHeight - ship.GetHeight()/2)));	
}

//create the explosion
void MyProject::InitExplosion()
{
	explosion.Initialize(&explosionTex, Vector2(-2500.0f, -2500.0f), 0, 0.5f, Colors::White.v, 0.0f);
	explosion.SetTextureAnimation(256, 256, 60);
}

//create the asteroids
void MyProject::InitAsteroids()
{
	for (int c = 0; c < MyProject::NUM_OF_ASTROIDS; c++)
	{			
		Sprite astroid;
		astroid.Initialize(&rockTex, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);
		astroid.SetTextureAnimation(60, 60, ((rand() % 60) + 60));		
		astroid.SetPosition(Vector2(GenerateRandX(), (float)((rand() % clientHeight + 1)*-1)));
		astroid.SetRotationVelocity((float)((rand() % 50) + 1));
		astroid.SetVelocity(Vector2(0.0f, (float)(rand() % 25) + 25),astroid.GetRotationalVelocity());
		astroid.SetScale(GenerateRandScale());
		astroid.SetColor(GenerateRandColour());
		astroids[c] = astroid;
	}
}

//move asteroids
void MyProject::MoveAsteroids(float deltaTime)
{
	for (int c = 0; c < MyProject::NUM_OF_ASTROIDS; c++)
	{
		
		Vector2 pos = astroids[c].GetPosition();
		Vector2 vol = astroids[c].GetVelocity();
		astroids[c].SetRotation(astroids[c].GetRotation() + astroids[c].GetRotationalVelocity()*deltaTime);
		pos.y += vol.y * deltaTime;
		astroids[c].SetPosition(pos);		
		if (astroids[c].GetPosition().y > clientHeight)
		{
			pos.y = -2;
			pos.x = GenerateRandX();
			astroids[c].SetPosition(pos);
			astroids[c].SetScale(GenerateRandScale());
			astroids[c].SetColor(GenerateRandColour());
			score++;
			scoreString.str(L"");
			scoreString << L"Score : " << score;
		}
		astroids[c].UpdateAnimation(deltaTime);
	}
}