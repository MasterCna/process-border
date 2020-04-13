
#include <iostream>
#include <Windows.h>
#include <string>


void drawBorder(RECT rc2)
{
	HWND hHwnd = FindWindow(NULL, "Untitled - Notepad");
	PAINTSTRUCT ps;
	auto hdc = BeginPaint(hHwnd, &ps);

	RECT rc;
	GetClientRect(hHwnd, &rc);
	HDC hdesktop = GetDC(0);

	int screenx = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int screeny = GetSystemMetrics(SM_YVIRTUALSCREEN);
	int screenw = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int screenh = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	StretchBlt(hdc, 0, 0, rc.right, rc.bottom,
		hdesktop, screenx, screeny, screenw, screenh, SRCCOPY);

	HBRUSH hBrush2 = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
	HPEN hPen = CreatePen(0, 5, RGB(200, 0, 0));

	SelectObject(hdesktop, hPen);
	SelectObject(hdesktop, GetStockObject(NULL_BRUSH));
	Rectangle(hdesktop, rc2.left, rc2.top - 6, rc2.right, rc2.bottom);

	HFONT font = CreateFont(18, 0, 0, 0, 400, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
	SelectObject(hdesktop, font);
	SelectObject(hdesktop, GetStockObject(NULL_BRUSH));

	DrawText(hdesktop, TEXT("MasterCna"), -1, &rc2, DT_CENTER | DT_NOCLIP);

}

int getProcessPosition(std::string processTitle)
{
	// Get handle of process
	HWND hHwnd = FindWindow(NULL, processTitle.c_str());

	if (hHwnd == NULL)
	{
		std::cout << "FindWindow Faield with error " << GetLastError() << "\n";
		return 1;
	}

	// Get process position
	RECT rect;

	while (1)
	{
		Sleep(1);
		if (!GetWindowRect(hHwnd, &rect))
		{
			std::cout << "GetWindowRect Faield with error " << GetLastError() << "\n";
			return 1;
		}

		drawBorder(rect);
	}
}

int main(int argc, char* argv[])
{
	getProcessPosition("Untitled - Notepad");

	return 0;
}