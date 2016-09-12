#include "MyProject.h"
#include <sstream> // for wostringstream
#include <Windowsx.h> // for GET__LPARAM macros

//----------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
	MyProject application(hInstance);    // Create the class variable

	if( application.InitWindowsApp(L"Font Example", nShowCmd) == false )    // Initialize the window, if all is well show and update it so it displays
	{
		return 0;                   // Error creating the window, terminate application
	}

	if( application.InitializeDirect3D() )
	{
		application.SetDepthStencil(true);      // Tell DirectX class to create and maintain a depth stencil buffer
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
	message = L"Mouse was clicked here ";
	mouseX = -1000;
	mouseY = -1000;
}

//----------------------------------------------------------------------------------------------
// Initialize any fonts we need to use here
//----------------------------------------------------------------------------------------------
void MyProject::InitializeFonts()
{
	timesNewRoman24Bold.InitializeFont(D3DDevice, DeviceContext, L"..\\Font\\TimesnewRoman24Bold.spritefont" );



}

//----------------------------------------------------------------------------------------------
// Window message handler
//----------------------------------------------------------------------------------------------
LRESULT MyProject::ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg )
	{
	case WM_LBUTTONUP:
		mouseX = GET_X_LPARAM( lParam );
		mouseY = GET_Y_LPARAM( lParam );
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
	// create a string that can hold numeric values and character values
	std::wostringstream ws; 

	// put information into the string
	ws << message << L"X: " << mouseX << L" Y: " << mouseY; 

	//print string to the screen using a font
	timesNewRoman24Bold.PrintMessage(mouseX, mouseY, ws.str(), FC_RED); 


	// render the base class
	DirectXClass::Render();
}
