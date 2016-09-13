#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <WICTextureLoader.h>

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

	pTexture = NULL;
	pCompiling = NULL;
}

//----------------------------------------------------------------------------------------------
// Destructor
//----------------------------------------------------------------------------------------------
MyProject::~MyProject()
{
	SAFE_RELEASE(pTexture);
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
	HRESULT result = DirectX::CreateWICTextureFromFile(D3DDevice, L"..\\Textures\\Flower.PNG", (ID3D11Resource**)&pTexture, NULL);	
	HRESULT res = DirectX::CreateWICTextureFromFile(D3DDevice, L"..\\Textures\\Fireworks.PNG", (ID3D11Resource**)&pCompiling, NULL);
	if (res != S_OK || result != S_OK)
	{
		MessageBox(mainWnd, L"Could not load texture", L"ERROR", MB_OK | MB_ICONERROR);
	}
}

//----------------------------------------------------------------------------------------------
// Window message handler
//----------------------------------------------------------------------------------------------
LRESULT MyProject::ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONUP:
		mouseX = GET_X_LPARAM(lParam);
		mouseY = GET_Y_LPARAM(lParam);
		return 0;

	}

	// let the base class handle remaining messages
	return DirectXClass::ProcessWindowMessages(msg, wParam, lParam);
}

//----------------------------------------------------------------------------------------------
// Called by the render loop to render a single frame
//----------------------------------------------------------------------------------------------
void MyProject::Render(void)
{

	timesNewRoman24Bold.PrintMessage(mouseX, mouseY, message, FC_RED);

	if (pTexture != NULL)
	{
		//Get the descriptior of the texture
		D3D11_TEXTURE2D_DESC desc;
		pTexture->GetDesc(&desc);

		//describe the region we are copying from the source
		D3D11_BOX sourceRegion;
		sourceRegion.left = 0;
		sourceRegion.right = desc.Width;
		sourceRegion.top = 0;
		sourceRegion.bottom = desc.Height;
		sourceRegion.front = 0;
		sourceRegion.back = 1;



		//Copy the texture to the backbuffer (render to the backbuffer)
		DeviceContext->CopySubresourceRegion(BackBuffer, 0, 100, 100, 0, pTexture, 0, &sourceRegion);
	}

	if (pCompiling != NULL)
	{
		//Get the descriptior of the texture
		D3D11_TEXTURE2D_DESC desc;
		pCompiling->GetDesc(&desc);

		//describe the region we are copying from the source
		D3D11_BOX sourceRegion;
		sourceRegion.left = desc.Width/2;
		sourceRegion.right = desc.Width;
		sourceRegion.top = desc.Height/2;
		sourceRegion.bottom = desc.Height;
		sourceRegion.front = 0;
		sourceRegion.back = 1;

		//Copy the texture to the backbuffer (render to the backbuffer)
		DeviceContext->CopySubresourceRegion(BackBuffer, 0, 200, 200, 0, pCompiling, 0, &sourceRegion);

		if (mouseX >= 0 && mouseX <= 1023 && mouseY >= 0 && mouseY <= 767)
		{
			DeviceContext->CopySubresourceRegion(BackBuffer, 0, mouseX, mouseY, 0, pCompiling, 0, &sourceRegion);
		}
	}


	
	// render the base class
	DirectXClass::Render();
}
