// Button art reference: http://opengameart.org/content/ui-pack (public domain)
//

#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <SpriteBatch.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXColors.h>

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

	if( application.InitWindowsApp(L"Lab 2", nShowCmd) == false )    // Initialize the window, if all is well show and update it so it displays
	{
		return 0;                   // Error creating the window, terminate application
	}

	if( application.InitializeDirect3D() )
	{
		application.SetDepthStencil(true);      // Tell DirectX class to create and maintain a depth stencil buffer
		application.InitializeTextures();
		application.MessageLoop();				// Window has been successfully created, start the application message loop
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

	direction = 1;
	movementSpeed = 1024 / 4;
	changeMovementAmount = movementSpeed;
	rotationSpeed = 180;
	scaleAmount = 0.5;
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
	rockTex.Load( D3DDevice, L"..\\Textures\\Rock.png" );

	rockSprite.Initialize(&rockTex, Vector2(0, clientHeight / 2), 0, 1, Colors::White.v, 0.0f );

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
	case WM_KEYUP:
		if (wParam >= '0' && wParam <= '3')
		{
			PresentInterval = wParam - '0';
		}
		if (wParam == VK_RIGHT)
		{
			movementSpeed += changeMovementAmount;
		}
		else if (wParam == VK_LEFT)
		{
			movementSpeed -= changeMovementAmount;
		}
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
	spriteBatch->Begin();
	rockSprite.Draw(spriteBatch);
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
	// move the rock 
	Vector2 pos = rockSprite.GetPosition();
	float rotation = rockSprite.GetRotation();
	float scale = rockSprite.GetScale();
	Color colour = rockSprite.GetColor();
	
	pos.x += direction * (movementSpeed * deltaTime);
	rotation += rotationSpeed * deltaTime;
	scale += scaleAmount * deltaTime;
	if (scale <= 1 || scale >= 5)
	{
		scaleAmount *= -1;
	}

	rockSprite.SetRotation(rotation);
	rockSprite.SetScale(scale);
	rockSprite.SetPosition(pos);

	// if it's off screen, switch directions
	if (pos.x < 0 || pos.x > clientWidth)
	{
		direction *= -1;
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