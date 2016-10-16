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
	case WM_MOUSEMOVE:
		mousePos.x = (float) GET_X_LPARAM(lParam);
		mousePos.y = (float) GET_Y_LPARAM(lParam);
		return 0;
	case WM_LBUTTONUP:
		buttonDown = false;
		mousePos.x = (float) GET_X_LPARAM(lParam);
		mousePos.y = (float) GET_Y_LPARAM(lParam);
		break;
	case WM_LBUTTONDOWN:
		buttonDown = true;
		mousePos.x = (float) GET_X_LPARAM(lParam);
		mousePos.y = (float) GET_Y_LPARAM(lParam);
		OnMouseDown();
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
	

	// draw your stuff here
	spriteBatch->Begin( SpriteSortMode_BackToFront );

	for (int c = 0; c < MyProject::NUM_OF_ASTROIDS; c++)
	{
		/*Sprite astr = astroids[c];
		astr.Draw(spriteBatch);*/
		astroids[c].Draw(spriteBatch);
	}
		

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

	/*for (int c = 0; c < MyProject::NUM_OF_ASTROIDS; c++)
	{
		int movementSpeed = 25;
		Vector2 pos = astroids[c].GetPosition();
		pos.y += movementSpeed * deltaTime;
		astroids[c].SetPosition(pos);
		if (astroids[c].GetPosition().y > clientHeight)
		{
			pos.y = -2;
			astroids[c].SetPosition(pos);
		}
		astroids[c].UpdateAnimation(deltaTime);
	}
	*/

}

//----------------------------------------------------------------------------------------------
// Called when the mouse is released
//----------------------------------------------------------------------------------------------
void MyProject::OnMouseDown()
{

	// this is called when the left mouse button is clicked
	// mouse position is stored in mousePos variable
}


DirectX::SimpleMath::Color MyProject::GenerateRandColour()
{
	return (colours[rand() % 5]);
}

float MyProject::GenerateRandX()
{
	return (float)(rand() % (clientWidth - 2) + 5);
}

float MyProject::GenerateRandScale()
{
	return (float)((rand() % 20 + 1)*0.10f);
}

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
		}
		astroids[c].UpdateAnimation(deltaTime);
	}
}