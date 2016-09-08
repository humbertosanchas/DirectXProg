# include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MessageBox(NULL, L"Nice Work win32", L"Next simplest Win32 App", MB_ICONEXCLAMATION | MB_OK);

	return 0;
}
