#ifndef _MyProject_h
#define _MyProject_h

#include <sstream> // for wostringstream
#include "DirectX.h"
#include "Font.h"

//Paul Boyko Sept 2016
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

	//Check if the guess is correct
	bool IsCorrect();

	//check if the guess is to high or low
	bool IsHigh();

	//check if guess is out of range
	bool OutOfRange();

	//Create output message
	void OutputMessage();

	//Display for the number guessed
	void DisplayGuessNumber();

	//clear guess display
	void ClearDisplayedGuessNumber();

	//Display a request for valid input
	void InputRequest();

	//Set flag var gameOver to true
	void GameOver();

	//display message asking if player wishes to play again
	void AskRestart();

	//Restart game if player wants to
	void RestartYes();

	//Don't restart if the choose not to
	void RestartNo();

	

	// Start Game
	void StartGame();

private:
	//to store new fonts
	FontType timesNewRoman24Bold;
	FontType righteous30;
	FontType impact30;
	//store guess, random number, counter and gameOver flag value
	int guess = 0;
	int r;
	int counter = 0;
	bool gameOver = false;
	
	//OutPutstrings for displaying
	std::wostringstream inputRequest;
	std::wostringstream guessString;
	std::wostringstream guessNumString;
};

#endif