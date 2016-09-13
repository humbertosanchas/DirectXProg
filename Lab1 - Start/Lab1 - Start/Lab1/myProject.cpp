#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <sstream> // for wostringstream
#include <time.h> 

//----------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
	MyProject application(hInstance);    // Create the class variable

	if( application.InitWindowsApp(L"Lab 1 - Pick a number", nShowCmd) == false )    // Initialize the window, if all is well show and update it so it displays
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
	// intializes the random number generator
	srand( (unsigned int) time(NULL) );

	StartGame();
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
	case WM_KEYUP:
		if ( wParam >= '0' && wParam <= '9' )
		{
			// digit is a single digit between 0 & 9
			int digit = wParam - '0';
		}
		else if ( wParam == VK_RETURN )
		{
			// Enter key is pressed
		}
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
	// example how to put a number into a string
	int num = 42;
	std::wostringstream ws;
	ws << L"The number "<< num << " is the answer";

	timesNewRoman24Bold.PrintMessage( 50, 50, ws.str(), FC_RED );

	// render the base class
	DirectXClass::Render();
}

//----------------------------------------------------------------------------------------------
// Starts or restarts the game
//----------------------------------------------------------------------------------------------
void MyProject::StartGame()
{
	// picks a number betwee 0 and 999999
	int r = rand() % 1000000;
}
