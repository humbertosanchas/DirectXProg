#ifndef _MyProject_h
#define _MyProject_h

#include "DirectX.h"
#include "Font.h"

//----------------------------------------------------------------------------------------------
// Main project class
//	Inherits the directx class to help us initalize directX
//----------------------------------------------------------------------------------------------

class MyProject : public DirectXClass
{
public:
	// constructor
	MyProject(HINSTANCE hInstance);

	// Initialize any fonts we need to use
	void InitializeFonts();

	// window message handler
	LRESULT ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam);

	// Called by the render loop to render a single frame
	void Render(void);

private:
	FontType timesNewRoman24Bold;
	FontType modak30;


	int mouseX;
	int mouseY;

	std::wstring message;

};

#endif