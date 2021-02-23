#include <windows.h>
#include "MVC.h"

HINSTANCE hInst;
HWND hwnd;
HWND hListBox;
HWND hListBox2;
HWND hEdit;
HDC hdc;
PAINTSTRUCT ps;




List<Complex> l1= { {1,1}, {2,2}, {3,3} };
Model<Complex> lst(l1);
WinapiView<Complex> v(lst.toStringVisitor(), hListBox);
Controller<Complex> c(lst, v);

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	hInst = hInstance;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	
	
	MSG msg;
	WNDCLASS w;
	memset(&w, 0, sizeof(WNDCLASS));
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = (WNDPROC)WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = "My Class";
	RegisterClass(&w);
	hwnd = CreateWindow("My Class", "Stack", WS_OVERLAPPEDWINDOW,
		300, 200, 700, 500, NULL, NULL, hInstance, NULL);

	
	
	CreateWindow("button", "push_front", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 150, 80, 30, hwnd, (HMENU)11, hInstance, NULL);
	CreateWindow("button", "push_back", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 180, 80, 30, hwnd, (HMENU)12, hInstance, NULL);
	CreateWindow("button", "pop_front", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 210, 80, 30, hwnd, (HMENU)13, hInstance, NULL);
	CreateWindow("button", "Max", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 240, 80, 30, hwnd, (HMENU)14, hInstance, NULL);
	CreateWindow("button", "Min", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 270, 80, 30, hwnd, (HMENU)15, hInstance, NULL);
	CreateWindow("button", "List size", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 300, 80, 30, hwnd, (HMENU)16, hInstance, NULL);
	
	hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_CENTER,
		420, 190, 200, 30, hwnd, (HMENU)20000, hInst, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	
	switch (Message) {
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 30, 270, "Структура через [min,max,количество]:", ARRAYSIZE("Структура через [min,max,количество]"));
		TextOut(hdc, 420, 170, "Формат ввода в поле : int int", ARRAYSIZE("Формат ввода в поле : int int"));
		
		c.MinMaxCountOut(hdc);
		
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_CREATE:
	{
		c.view.hListBox = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER | WS_VSCROLL | LBS_DISABLENOSCROLL,
			30, 30, 200, 200, hwnd, (HMENU)10000, hInst, NULL);
		v.refresh();
		break;
	}
	case WM_COMMAND:
		
		if (LOWORD(wparam) == 11)
		{
			char temp[40];
			GetWindowText(hEdit, temp, 39);
			string t(temp);
			istringstream iss(t);
			Complex i;
			if (iss >> i)
				c.push_front(i);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 12)
		{
			char temp[40];
			GetWindowText(hEdit, temp, 39);
			string t(temp);
			istringstream iss(t);
			Complex i;
			if (iss >> i)
				c.push_back(i);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 13)
		{
			c.pop_front();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		
		if (LOWORD(wparam) == 14)
		{
			c.Max();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 15)
		{
			c.Min();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 16)
		{
			c.Count();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wparam, lparam);
	}
	return 0;
}

