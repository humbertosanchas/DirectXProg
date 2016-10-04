// Button art reference: http://opengameart.org/content/ui-pack (public domain)
//

#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <SpriteBatch.h>
#include<d3d11.h>
#include <SimpleMath.h>
#include <DirectXColors.h>
#include <sstream>
#include "Collision2D.h"

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

	if( application.InitWindowsApp(L"Lab 3", nShowCmd) == false )    // Initialize the window, if all is well show and update it so it displays
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
	blockTex.Load( D3DDevice, L"..\\Textures\\block_purple.png" );
	ballTex.Load(D3DDevice, L"..\\Textures\\sphere-04.png");

	Vector2 center(clientWidth * 0.5f, clientHeight * 0.5f);

	ballSprite.Initialize(&ballTex, center, 0, 0.25f, Colors::White.v, 0.0f);
	ballVelocity = Vector2(-200.0f, 90.0f);

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		blocks[i].Initialize(&blockTex, center + Vector2(300.0f* cosf(i * 6.28f / NUM_BLOCKS), 300.0f*sinf(i * 6.28f / NUM_BLOCKS)), 0, 0.25f, Colors::White.v, 0.0f);
	}

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
	case WM_KEYDOWN:
		if (wParam == VK_ADD)
		{
			ballVelocity = ballVelocity * 1.1f; // add 10%
		}
		else if (wParam == VK_SUBTRACT)
		{
			ballVelocity = ballVelocity * 0.9f; // 90% of current speed
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
	spriteBatch->Begin( SpriteSortMode_BackToFront );
	ballSprite.Draw(spriteBatch);

	for (int i = 0; i < NUM_BLOCKS; i++)
	{

		blocks[i].Draw(spriteBatch);
	}

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
	Vector2 pos = ballSprite.GetPosition();
	pos += ballVelocity * deltaTime;
	ballSprite.SetPosition(pos);
	
	// keep the ball in place
	if (pos.x < 0) ballVelocity.x = fabsf(ballVelocity.x);
	if (pos.x > clientWidth) ballVelocity.x = -fabs(ballVelocity.x);
	if (pos.y < 0) ballVelocity.y = fabsf(ballVelocity.y);
	if (pos.y > clientHeight) ballVelocity.y = -fabs(ballVelocity.y);


	// get the collision sphere for the ball sprite
	Circle ballCollision(pos, ballSprite.GetWidth() * 0.5f);

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		Box2D blockCollision(blocks[i].GetPosition(), blocks[i].GetExtents());
		if (Collision2D::BoxCircleCheck(blockCollision, ballCollision))
		{
			// COLLISION RESPONSE

			// back the circle up and find the reflection
			ballCollision.center -= ballVelocity * deltaTime;

			// returns the center of the circle after reflecting off the box
			pos = Collision2D::ReflectCircleBox(ballCollision, ballVelocity, deltaTime, blockCollision);
			ballSprite.SetPosition(pos);
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