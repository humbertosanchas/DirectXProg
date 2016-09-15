#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <WICTextureLoader.h>
#include<SpriteBatch.h>
#include<SimpleMath.h>
#include <DirectXColors.h>



using namespace DirectX;
using namespace DirectX::SimpleMath;
// helper function
//
inline float DegToRad(float deg) { return 3.141592f * deg / 180.0f; }

//----------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
	MyProject application(hInstance);    // Create the class variable

	if (application.InitWindowsApp(L"Font Example", nShowCmd) == false)    // Initialize the window, if all is well show and update it so it displays
	{
		return 0;                   // Error creating the window, terminate application
	}

	if (application.InitializeDirect3D())
	{
		application.SetDepthStencil(true);      // Tell DirectX class to create and maintain a depth stencil buffer
		application.InitializeFonts();
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
	mouseX = -1000;
	mouseY = -1000;
	buttonDown = false;

	spriteBatch = NULL;
}

//----------------------------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------------------------
MyProject::~MyProject()
{
	delete spriteBatch;
	spriteBatch = NULL;
}

//----------------------------------------------------------------------------------------------
// Initialize any fonts we need to use here
//----------------------------------------------------------------------------------------------
void MyProject::InitializeFonts()
{
	timesNewRoman24Bold.InitializeFont(D3DDevice, DeviceContext, L"..\\Font\\TimesnewRoman24Bold.spritefont");
}

//---------------------------------------------------------------------------------------------
// Initialize any textures we need to use here
//---------------------------------------------------------------------------------------------
void MyProject::InitializeTextures()
{
	flowerTexture.LoadTexture(D3DDevice, L"..\\Textures\\Flower.png");
	fireworkTexture.LoadTexture(D3DDevice, L"..\\Textures\\Fireworks.png");
	penguinTexture.LoadTexture(D3DDevice, L"..\\Textures\\Fizyplankton.png" );

	spriteBatch = new DirectX::SpriteBatch(DeviceContext);
	
}

//----------------------------------------------------------------------------------------------
// Window message handler
//----------------------------------------------------------------------------------------------
LRESULT MyProject::ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		if (buttonDown)
		{
			mouseX = GET_X_LPARAM(lParam);
			mouseY = GET_Y_LPARAM(lParam);
		}
		return 0;
	case WM_LBUTTONUP:
		buttonDown = false;
		mouseX = GET_X_LPARAM(lParam);
		mouseY = GET_Y_LPARAM(lParam);
		break;
	case WM_LBUTTONDOWN:
		buttonDown = true;
		mouseX = GET_X_LPARAM(lParam);
		mouseY = GET_Y_LPARAM(lParam);
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

	flowerTexture.Draw(DeviceContext, BackBuffer, 0, 0);

	fireworkTexture.Draw(DeviceContext, BackBuffer, mouseX, mouseY);
	
	timesNewRoman24Bold.PrintMessage(mouseX, mouseY, message, FC_RED);

	spriteBatch->Begin();

	Vector2 center(penguinTexture.GetWidth() / 2, penguinTexture.GetHeight() / 2);
	float scale = 0.25f;

	Vector2 pos(mouseX, mouseY);
	Vector2 posLeft(mouseX - penguinTexture.GetWidth(), mouseY);	
	Vector2 posUnder(mouseX, mouseY +  penguinTexture.GetHeight());
	Vector2 posBottom(mouseX - penguinTexture.GetWidth(), mouseY + penguinTexture.GetHeight());

	RECT area;
	area.left = penguinTexture.GetWidth() * 1 / 3;
	area.right = penguinTexture.GetWidth() * 2 / 3;
	area.top = 0;
	area.bottom = penguinTexture.GetHeight() / 2;

	RECT full;
	full.top = full.left = 0;
	full.right = penguinTexture.GetWidth();
	full.bottom = penguinTexture.GetHeight();

	spriteBatch->Draw(penguinTexture.GetView(),posLeft, Colors::Purple);
	spriteBatch->Draw(penguinTexture.GetView(), posLeft, &full ,Colors::Red, DegToRad(90), center);
	spriteBatch->Draw(penguinTexture.GetView(), posLeft, &full, Colors::Green, DegToRad(90), center, scale);
	spriteBatch->Draw(penguinTexture.GetView(), posUnder, Color(0, 42, 0, 0.5));
	spriteBatch->Draw(penguinTexture.GetView(), pos);

	spriteBatch->Draw(penguinTexture.GetView(), posBottom, &area);



	spriteBatch->End();


	// render the base class
	DirectXClass::Render();
}
