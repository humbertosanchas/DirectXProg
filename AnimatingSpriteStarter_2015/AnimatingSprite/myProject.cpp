// Button art reference: http://opengameart.org/content/ui-pack (public domain)
//

#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <SpriteBatch.h>
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

	movementSpeed = 60; // 60 pixels per second
	movementSpeed1 = 25;
	movementSpeed2 = 90;
	rotationSpeed = 45;
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
	rockTex.Load( D3DDevice, L"..\\Textures\\rockSheet.png" );

	rockSprite.Initialize(&rockTex, Vector2(0, (clientHeight - (clientHeight / 1.2))), 0, 1, Colors::White.v, 0.0f);
	rockSprite.SetTextureAnimation(60, 60, 60);
	rockSprite1.Initialize(&rockTex, Vector2(0, clientHeight / 2), 0, 1, Colors::White.v, 0.0f);
	rockSprite1.SetTextureAnimation(60, 60, 120);
	rockSprite2.Initialize(&rockTex, Vector2(0, (clientHeight - (clientHeight / 6))), 0, 1, Colors::White.v, 0.0f);
	rockSprite2.SetTextureAnimation(60, 60, 15);
	rockSprite3.Initialize(&rockTex, Vector2(0, (clientHeight - (clientHeight / 12))), 0, 1, Colors::White.v, 0.0f);
	rockSprite3.SetTextureAnimation(60, 60, 240);
	

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
		if (wParam >= '0' && wParam <= '4')
		{
			PresentInterval = wParam - '0';
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
	rockSprite1.Draw(spriteBatch);
	rockSprite2.Draw(spriteBatch);
	rockSprite3.Draw(spriteBatch);
	rockSprite4.Draw(spriteBatch);
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
	
	//move the rock 
	Vector2 pos = rockSprite.GetPosition();
	Vector2 pos1 = rockSprite1.GetPosition();
	Vector2 pos2 = rockSprite3.GetPosition();
	Vector2 pos3 = rockSprite3.GetPosition();

	pos.x += movementSpeed * deltaTime;
	pos1.x += movementSpeed1 * deltaTime;
	pos2.x += movementSpeed2 * deltaTime;
	pos3.x += movementSpeed1 * deltaTime;
	rockSprite.SetPosition(pos);
	rockSprite1.SetPosition(pos1);
	rockSprite2.SetPosition(pos3);
	rockSprite3.SetPosition(pos2);
	

	// rotate the rock
	float rot = rockSprite.GetRotation();
	rot += rotationSpeed * deltaTime;
	rockSprite.SetRotation(rot);

	

	// if it's off screen, switch directions
	if (pos.x < 0)	
	{
		movementSpeed = fabsf(movementSpeed);
	}
	
	else if (pos.x > clientWidth)
	{
		pos.x = 0;
		rockSprite.SetPosition(pos);
	}
		
	rockSprite.UpdateAnimation(deltaTime);
	rockSprite1.UpdateAnimation(deltaTime);
	rockSprite2.UpdateAnimation(deltaTime);
	rockSprite3.UpdateAnimation(deltaTime);
	rockSprite4.UpdateAnimation(deltaTime);
}

//----------------------------------------------------------------------------------------------
// Called when the mouse is released
//----------------------------------------------------------------------------------------------
void MyProject::OnMouseDown()
{

	// this is called when the left mouse button is clicked
	// mouse position is stored in mousePos variable


}