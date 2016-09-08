//Testing 2
// include the basic windows header file
#include <windows.h>
#include <windowsx.h>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    
    HWND hWnd;        // the handle for the window
    WNDCLASSEX wc;    // information for the window class
    MSG msg;          // Windows event messages

    ZeroMemory(&wc, sizeof(WNDCLASSEX));    // set entire windows class structure to NULL
    wc.cbSize = sizeof(WNDCLASSEX);         // fill in the struct with the needed information
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass1";

    RegisterClassEx(&wc);                        // register the window class ( each process must register a window class )

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
                          L"WindowClass1",                  // name of the window class
                          L"Our First Windowed Program",    // title of the window
                          WS_OVERLAPPEDWINDOW,              // window style
                          300,                              // x-position of the window
                          300,                              // y-position of the window
                          500,                              // width of the window
                          400,                              // height of the window
                          NULL,                             // we have no parent window, NULL
                          NULL,                             // we aren't using menus, NULL
                          hInstance,                        // application handle
                          NULL);                            // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, nCmdShow);

    // enter the main loop:
    // wait for the next message in the queue, store the result in 'msg'
	msg.message = 0;  // set a default message
	while (msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			// translate and dispatch msg
			DispatchMessage(&msg);
		}
		else
		{
			// continue game operations
		}
	}

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}
int iMouseCount = 0;
// main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)   //check the message
    {
        case WM_DESTROY:    // the WM_DESTROY message is generated on exit
        {
            PostQuitMessage(0); // close the application entirely
            return 0;
        } 
		case WM_KEYUP:
			{
				if ( wParam == 'M' ) 
				{
					MessageBox( hWnd, L"M was pressed", L"M was pressed", MB_OK );
				}

			}
			break;

		case WM_LBUTTONDOWN:
			{
				iMouseCount++;
				if(iMouseCount >= 5)
				{
					MessageBox(hWnd, L"Mouse was clicked 5 times!", L"Mouse Pressed", MB_OK);
					iMouseCount = 0;
				}
			}
			break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);   // Handle all other generated messages the switch statement didn't
} 