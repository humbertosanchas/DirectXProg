// Button art reference: http://opengameart.org/content/ui-pack (public domain)
//

#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <SpriteBatch.h>
#include <d3d11.h>
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
	

	blocks[0].Initialize(&blockTex, Vector2(clientWidth*0.25f, clientHeight*0.5f + 10), 0, 0.25f, Colors::White.v, 0.0f);
	blocks[1].Initialize(&blockTex, Vector2(clientWidth*0.75f, clientHeight*0.5f), 0, 0.25f, Colors::White.v, 0.0f);

	blockVelocity[0] = Vector2(-300, 0);
	blockVelocity[1] = Vector2(300, 0);



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

	
	//boxes have been moved. Now check for collision
	Box2D boxA;
	Box2D boxB;
	boxA.center = blocks[0].GetPosition();
	boxA.extents = blocks[0].GetExtents();

	boxB.center = blocks[1].GetPosition();
	boxB.extents = blocks[1].GetExtents();

	if (Collision2D::BoxBoxCheck(boxA, boxB))
	{
		blocks[0].SetColor( Color(0.10f,0.10f,0.10f,1.0f));
		blocks[1].SetColor(Color(0.10f, 0.10f, 0.10f, 1.0f));
		for (int i = 0; i < NUM_BLOCKS; i++)
		{
			if (blockVelocity[i].x < 0 )
			{
				blockVelocity[i].x = fabs(blockVelocity[i].x);
			}
			else
			{
				blockVelocity[i].x = -fabs(blockVelocity[i].x);
			}
		}
	}
	//else
	{
		for (int i = 0; i < NUM_BLOCKS; i++)
		{
			// update the block position
			Vector2 pos = blocks[i].GetPosition();
			pos += blockVelocity[i] * deltaTime;
			blocks[i].SetPosition(pos);

			// keep the ball in place
			if (pos.x < 0) blockVelocity[i].x = fabsf(blockVelocity[i].x);
			if (pos.x > clientWidth) blockVelocity[i].x = -fabs(blockVelocity[i].x);
			if (pos.y < 0) blockVelocity[i].y = fabsf(blockVelocity[i].y);
			if (pos.y > clientHeight) blockVelocity[i].y = -fabs(blockVelocity[i].y);

		}
		blocks[0].SetColor(Colors::White.v);
		blocks[1].SetColor(Colors::White.v);
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