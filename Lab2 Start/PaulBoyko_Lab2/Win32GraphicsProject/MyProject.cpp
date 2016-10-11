// Button art reference: http://opengameart.org/content/ui-pack (public domain)
//

#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <SpriteBatch.h>
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
//Paul Boyko Oct 2016
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
		application.InitializeFonts();
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
}

//----------------------------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------------------------
MyProject::~MyProject()
{
	delete spriteBatch;
}

//----------------------------------------------------------------------------------------------
// Initialize any fonts we need to use hereL
//----------------------------------------------------------------------------------------------
void MyProject::InitializeFonts()
{
	verdana24.InitializeFont(D3DDevice, DeviceContext, L"..\\Font\\Verdana24.spritefont");
}
//---------------------------------------------------------------------------------------------
// Initialize any textures we need to use here
//---------------------------------------------------------------------------------------------

void MyProject::InitializeTextures()
{	
	//load texture
	blueSheet.Load(D3DDevice, L"..\\Textures\\blueSheet.png");
	greenSheet.Load(D3DDevice, L"..\\Textures\\greenSheet.png");
	yellowSheet.Load(D3DDevice, L"..\\Textures\\yellowSheet.png");
	background.Load(D3DDevice, L"..\\Textures\\starfield.dds");
	fizzyPlankton.Load(D3DDevice, L"..\\Textures\\Fizyplankton.png");
	//Init sprites fizzy
	fizy.Initialize(&fizzyPlankton, Vector2(clientWidth - ((clientWidth / 2) / 2), (clientHeight / 2)), 0, 1.0f, DirectX::Colors::White.v, 1.0f);
	//Init sprites for Buttons
	btnTop.Initialize(&blueSheet, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);
	btn2ndTop.Initialize(&blueSheet, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);
	btnMiddle.Initialize(&blueSheet, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);
	btn2ndBottom.Initialize(&blueSheet, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);
	btnBottom.Initialize(&blueSheet, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);
	//init the preesed and has been clicked version of the button
	btnPressed.Initialize(&yellowSheet, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);
	btnClicked.Initialize(&greenSheet, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);   
	//Init arrows
	arrowRight.Initialize(&blueSheet, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);
	arrowLeft.Initialize(&blueSheet, Vector2(0.0f, 0.0f), 0, 1, Colors::White.v, 0.0f);
	

	ViewLayout();
	
	// initialize the sprite batch
	spriteBatch = new DirectX::SpriteBatch( DeviceContext );
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
		OnMouseEnter();
		return 0;
	case WM_LBUTTONUP:
		buttonDown = false;
		mousePos.x = (float) GET_X_LPARAM(lParam);
		mousePos.y = (float) GET_Y_LPARAM(lParam);
		OnMouseUp();
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
	//draw the background image
	background.Draw(DeviceContext, BackBuffer, 0, 0);
	// draw your stuff here
	verdana24.PrintMessage(clientWidth/3.0f, clientHeight/24.0f, L"Fizyplankton\'s Menu", DirectX::Colors::White);
	

	spriteBatch->Begin();
		
		btnTop.Draw(spriteBatch);
		btn2ndTop.Draw(spriteBatch);
		btnMiddle.Draw(spriteBatch);
		btn2ndBottom.Draw(spriteBatch);
		btnBottom.Draw(spriteBatch);
		fizy.Draw(spriteBatch);
		arrowRight.Draw(spriteBatch);
		arrowLeft.Draw(spriteBatch);

	spriteBatch->End();	

	verdana24.PrintMessage(25.0f, btnTop.GetPosition().y - btnTop.GetHeight()/4, L"White", DirectX::Colors::White);
	verdana24.PrintMessage(25.0f, btn2ndTop.GetPosition().y - btn2ndTop.GetHeight() / 4, L"Blue", DirectX::Colors::White);
	verdana24.PrintMessage(25.0f, btnMiddle.GetPosition().y - btnMiddle.GetHeight() / 4, L"Red", DirectX::Colors::White);
	verdana24.PrintMessage(25.0f, btn2ndBottom.GetPosition().y - btn2ndBottom.GetHeight() / 4, L"Yellow", DirectX::Colors::White);
	verdana24.PrintMessage(25.0f, btnBottom.GetPosition().y - btnBottom.GetHeight() / 4, L"Green", DirectX::Colors::White);

	// render the base class
	DirectXClass::Render();
}

//----------------------------------------------------------------------------------------------
// Called every frame to update objects.
//	deltaTime: how much time in seconds has elapsed since the last frame
//----------------------------------------------------------------------------------------------
void MyProject::Update(float deltaTime)
{
	
	// if you need to update any sprites, do it here


}

//----------------------------------------------------------------------------------------------
// Called when the mouse is released
//----------------------------------------------------------------------------------------------
void MyProject::OnMouseDown()
{
	// this is called when the left mouse button is down changes button colour
	if (btnTop.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnPressed.SetPosition(btnTop.GetPosition());
		btnTop = btnPressed;		
	}
	if (btn2ndTop.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnPressed.SetPosition(btn2ndTop.GetPosition());
		btn2ndTop = btnPressed;		
	}
	if (btnMiddle.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnPressed.SetPosition(btnMiddle.GetPosition());
		btnMiddle = btnPressed;		
	}
	if (btn2ndBottom.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnPressed.SetPosition(btn2ndBottom.GetPosition());
		btn2ndBottom = btnPressed;	
	}
	if (btnBottom.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnPressed.SetPosition(btnBottom.GetPosition());
		btnBottom = btnPressed;	
	}	
	// mouse position is stored in mousePos variable
}

void MyProject::OnMouseUp()
{
	// this is called when the left mouse button is let up chagnes colour of the buttons
	if (btnTop.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnClicked.SetPosition(btnTop.GetPosition());
		btnTop = btnClicked;
		fizy.SetColor(DirectX::Colors::White.v);
	}
	if (btn2ndTop.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnClicked.SetPosition(btn2ndTop.GetPosition());
		btn2ndTop = btnClicked;
		fizy.SetColor(DirectX::Colors::Blue.v);
	}
	if (btnMiddle.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnClicked.SetPosition(btnMiddle.GetPosition());
		btnMiddle = btnClicked;
		fizy.SetColor(DirectX::Colors::Red.v);
	}
	if (btn2ndBottom.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnClicked.SetPosition(btn2ndBottom.GetPosition());
		btn2ndBottom = btnClicked;
		fizy.SetColor(DirectX::Colors::Yellow.v);
	}
	if (btnBottom.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnClicked.SetPosition(btnBottom.GetPosition());
		btnBottom = btnClicked;
		fizy.SetColor(DirectX::Colors::Green.v);
	}
	//if right arrow pressed scale up
	if (arrowRight.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		if (fizy.GetScale() < 4.0f)
		{
			float scale = fizy.GetScale();
			scale += 0.1f;
			fizy.SetScale(scale);
		}
	}
	//if arrow down scale down
	if (arrowLeft.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		if (fizy.GetScale() - 0.1f > 0.1f)
		{
			float scale = fizy.GetScale();
			scale -= 0.1f;
			fizy.SetScale(scale);
		}
	}
	// mouse position is stored in mousePos variable
}

void MyProject::OnMouseEnter()
{
	//check if mouse enter a button and adjust the colour with a high light
	if (btnTop.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btnTop.SetColor(DirectX::Colors::LightGray.v);
	}
	else
	{
		btnTop.SetColor(DirectX::Colors::White.v);
	}
	if (btn2ndTop.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		btn2ndTop.SetColor(DirectX::Colors::LightGray.v);
	}
	else
	{
		btn2ndTop.SetColor(DirectX::Colors::White.v);
	}
	if (btnMiddle.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{		
		btnMiddle.SetColor(DirectX::Colors::LightGray.v);
	}
	else
	{
		btnMiddle.SetColor(DirectX::Colors::White.v);
	}
	if (btn2ndBottom.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{		
		btn2ndBottom.SetColor(DirectX::Colors::LightGray.v);
	}
	else
	{
		btn2ndBottom.SetColor(DirectX::Colors::White.v);
	}
	if (btnBottom.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{		
		btnBottom.SetColor(DirectX::Colors::LightGray.v);
	}
	else
	{
		btnBottom.SetColor(DirectX::Colors::White.v);
	}
	if (arrowRight.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		arrowRight.SetColor(DirectX::Colors::LightGray.v);
	}
	else
	{
		arrowRight.SetColor(DirectX::Colors::White.v);
	}
	if (arrowLeft.ContainsPoint(Vector2(mousePos.x, mousePos.y)))
	{
		arrowLeft.SetColor(DirectX::Colors::LightGray.v);
	}
	else
	{
		arrowLeft.SetColor(DirectX::Colors::White.v);
	}
}

void MyProject::ViewLayout()
{


	//Sprite Regions of the buttons
	RECT btnUnclicked;
	btnUnclicked.left = 190;
	btnUnclicked.right = 190+190;
	btnUnclicked.top = 49;
	btnUnclicked.bottom = 49 + 45;

	//set the region for all 5 buttons
	btnTop.SetTextureRegion(btnUnclicked.left, btnUnclicked.top, btnUnclicked.right, btnUnclicked.bottom);
	btn2ndTop.SetTextureRegion(btnUnclicked.left, btnUnclicked.top, btnUnclicked.right, btnUnclicked.bottom);
	btnMiddle.SetTextureRegion(btnUnclicked.left, btnUnclicked.top, btnUnclicked.right, btnUnclicked.bottom);
	btn2ndBottom.SetTextureRegion(btnUnclicked.left, btnUnclicked.top, btnUnclicked.right, btnUnclicked.bottom);
	btnBottom.SetTextureRegion(btnUnclicked.left, btnUnclicked.top, btnUnclicked.right, btnUnclicked.bottom);

	//scale the button up
	btnTop.SetScale(2.0f);
	btn2ndTop.SetScale(2.0f);
	btnMiddle.SetScale(2.0f);
	btn2ndBottom.SetScale(2.0f);
	btnBottom.SetScale(2.0f);

	//set region of arrows
	arrowRight.SetTextureRegion(378, 143, 378 + 39, 143 + 31);
	arrowLeft.SetTextureRegion(339, 143, 339 + 39, 143 + 31);

	arrowRight.SetScale(2.0);
	arrowLeft.SetScale(2.0f);

	arrowRight.SetPosition(Vector2(clientWidth - 200.0f , clientHeight - 50.0f));
	arrowLeft.SetPosition(Vector2(clientWidth - 400.0f, clientHeight - 50.0f));

	//set region for both pressed and clicked
	btnPressed.SetTextureRegion(190,0,190+190,45);
	btnClicked.SetTextureRegion(0,49,190,49+45);

	//set scale for pressed and clicked
	btnPressed.SetScale(2.0f);
	btnClicked.SetScale(2.0f);

	//position for all 5 buttons	
	btnTop.SetPosition(Vector2(btnTop.GetWidth() / 2, ((btnTop.GetHeight() * 1.0f) + (clientHeight / 8))));
	btn2ndTop.SetPosition(Vector2 (btn2ndTop.GetWidth() / 2, ((btn2ndTop.GetHeight() * 2.0f) + (clientHeight / 8))));
	btnMiddle.SetPosition(Vector2 (btnMiddle.GetWidth() / 2, ((btnMiddle.GetHeight() * 3.0f) + (clientHeight / 8))));
	btn2ndBottom.SetPosition(Vector2(btn2ndBottom.GetWidth() / 2, ((btn2ndBottom.GetHeight() * 4.0f) + (clientHeight / 8))));
	btnBottom.SetPosition(Vector2 (btnBottom.GetWidth() / 2, ((btnBottom.GetHeight() * 5.0f) + (clientHeight / 8))));	
}