#include "MyProject.h"
#include <Windowsx.h> // for GET__LPARAM macros
#include <sstream> // for wostringstream
#include <time.h> 


//Paul Boyko Sept 2016
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
	InputRequest();
}

//----------------------------------------------------------------------------------------------
// Initialize any fonts we need to use here
//----------------------------------------------------------------------------------------------
void MyProject::InitializeFonts()
{
	timesNewRoman24Bold.InitializeFont(D3DDevice, DeviceContext, L"..\\Font\\TimesnewRoman24Bold.spritefont" );
	righteous30.InitializeFont(D3DDevice, DeviceContext, L"..\\Font\\Righteous30.spritefont");
	impact30.InitializeFont(D3DDevice, DeviceContext, L"..\\Font\\Impact30.spritefont");

}

//----------------------------------------------------------------------------------------------
// Window message handler
//----------------------------------------------------------------------------------------------
LRESULT MyProject::ProcessWindowMessages(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg )
	{
	case WM_KEYUP:
		if (!gameOver)
		{
			if (wParam >= '0' && wParam <= '9')
			{				
				//each digit is a single digit between 0 & 9 and is place as proper power of base ten location
				guess *= 10;
				guess += wParam - '0';
				//display the number
				DisplayGuessNumber();
			}
			else if (wParam == VK_BACK)
			{
				//if backspaced div by 10 to remove on base 10 and display the new number (if greater then 10)
				if (guess > 10)
				{
					guess /= 10;
					DisplayGuessNumber();
				}
				else
				{
					//if less then ten set the number to zero and clear the display
					guess = 0;
					ClearDisplayedGuessNumber();
				}				
			}
			else if (wParam == VK_RETURN)
			{
				// Enter key is pressed
				//Output the appropiate message
				OutputMessage();
				//set guess back to 0
				guess = 0;
				//increment counter
				counter++;
			}
			
		}
		else
		{
			if (wParam == 'Y')
			{
				RestartYes();
			}
			else if (wParam == 'N')
			{
				RestartNo();
			}
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
	/*int num = 42;
	std::wostringstream ws;
	ws << L"The number "<< num << " is the answer";*/

	//display for the request for input
	timesNewRoman24Bold.PrintMessage( 50, 50, inputRequest.str(), FC_RED );
	//display for the output of the number selected
	impact30.PrintMessage(50, 100, guessNumString.str(), FC_RED);
	//display for to high to low, correct and restart
	righteous30.PrintMessage(50, 150, guessString.str(), FC_RED);

	// render the base class
	DirectXClass::Render();
}

//----------------------------------------------------------------------------------------------
// check if guess is right
//----------------------------------------------------------------------------------------------
bool MyProject::IsCorrect()
{
	if (guess == r)
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------------------------
// check if guess is too high
//----------------------------------------------------------------------------------------------

bool MyProject::IsHigh()
{
	if (guess > r)
	{
		return true;
	}	
		return false;	
}

//----------------------------------------------------------------------------------------------
// check if guess is out of range 
//----------------------------------------------------------------------------------------------
bool MyProject::OutOfRange()
{
	if (guess > 100 || guess <= 0)
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------
// set proper out message based of result of the guess
//----------------------------------------------------------------------------------------------
void MyProject::OutputMessage()
{
	guessString.str(L"");
	if (OutOfRange())
	{
		guessString << L"Guess must be between 1 and 100 ";
	}
	else if (IsCorrect())
	{
		guessString << L"You are right the number was " << guess << endl << "it took you " << counter << " attempts to get it right" << endl;
		GameOver();
		AskRestart();
		
	}
	else if (IsHigh())
	{
		guessString << L"Guess is too high" << endl;
	}
	else
	{
		guessString << L"Guess is too low" << endl;
	}
}

//----------------------------------------------------------------------------------------------
// set the number to display according to guesses
//----------------------------------------------------------------------------------------------
void MyProject::DisplayGuessNumber()
{
	ClearDisplayedGuessNumber();
	guessNumString << guess;
}

//----------------------------------------------------------------------------------------------
// clear the number to displayed as guess
//----------------------------------------------------------------------------------------------
void MyProject::ClearDisplayedGuessNumber()
{
	guessNumString.str(L"");	
}

//----------------------------------------------------------------------------------------------
// set the input request
//----------------------------------------------------------------------------------------------
void MyProject::InputRequest()
{
	inputRequest.str(L"");
	inputRequest << L"Enter an number between 1 - 100" << endl;
}

//----------------------------------------------------------------------------------------------
// set game over flag true
//----------------------------------------------------------------------------------------------
void MyProject::GameOver()
{
	gameOver = true;
}

//----------------------------------------------------------------------------------------------
// add restart request to the winning output
//----------------------------------------------------------------------------------------------
void MyProject::AskRestart()
{
	guessString << "Would you like to restart [Y\\N] : " << endl;
}

//----------------------------------------------------------------------------------------------
//if restart requested clear data and restart
//----------------------------------------------------------------------------------------------
void MyProject::RestartYes()
{
	guess = 0;
	counter = 0;
	gameOver = false;
	guessString.str(L"");
	guessNumString.str(L"");
	StartGame();
	InputRequest();
}

//----------------------------------------------------------------------------------------------
//if restart not requested close Quit (post the quit so it will close when safe to do so)
//----------------------------------------------------------------------------------------------
void MyProject::RestartNo()
{
	PostQuitMessage(0);
}

//----------------------------------------------------------------------------------------------
// Starts or restarts the game
//----------------------------------------------------------------------------------------------
void MyProject::StartGame()
{
	// picks a number betwee 1 and 100
	r = rand() % 100 + 1;
}
