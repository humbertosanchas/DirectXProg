#ifndef _MyProject_h
#define _MyProject_h

#include <sstream> // for wostringstream
#include "DirectX.h"
#include "Font.h"


//----------------------------------------------------------------------------------------------
// Main project class
//	Inherits the directx class to help us initalize directX
//----------------------------------------------------------------------------------------------

class MyProject : public DirectXClass
{
public:
	/*int guess = 0;
	int r;
	int highLow;
	int num = 0;
	std::wostringstream ws;*/
	// constructor
	MyProject(HINSTANCE hInstance);

	// Initialize any fonts we need to use
	void InitializeFonts();

	// window message handler
	LRESULT ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam);

	// Called by the render loop to render a single frame
	void Render(void);

	bool IsCorrect();

	bool IsHigh();

	bool OutOfRange();

	void OutputMessage();

	void DisplayGuessNumber();

	void GameOver();

	void AskRestart();

	void RestartYes();

	void RestartNo();

	

	// Start Game
	void StartGame();

private:
	FontType timesNewRoman24Bold;
	FontType righteous30;
	int guess = 0;
	int r;
	int counter = 0;
	bool gameOver = false;
	
	std::wostringstream ws;
	std::wostringstream guessString;
	std::wostringstream guessNumString;
};

#endif