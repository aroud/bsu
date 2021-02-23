#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <string.h>
#include "resource.h"
HWND hEdit;
HINSTANCE hInst;
static int a = 100;
static int R;
BOOL CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CreateMenuItem(HMENU, char*, UINT, UINT, HMENU);
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	HWND hwnd;
	HWND dialog{};
	MSG msg;
	WNDCLASS w;
	hInst = hInstance;
	memset(&w, 0, sizeof(WNDCLASS));
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = "My Class";
	RegisterClass(&w);
	hwnd = CreateWindow("My Class", "My title", WS_OVERLAPPEDWINDOW,
		300, 200, 500, 400, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
		10, 70, 80, 30, hwnd, (HMENU)10001, hInstance, NULL);
	CreateWindow("button", "������� ������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		100, 70, 120, 30, hwnd, (HMENU)10000, hInstance, NULL);
	CreateWindow("button", "�������� ������", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
		10, 180, 160, 20, hwnd, (HMENU)10003, hInstance, NULL);
	HWND hButton1;
	hButton1 = CreateWindow("button", "���������� ����",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		30, 250, 160, 30,
		hwnd, (HMENU)11111,
		hInstance, NULL);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	
	static LOGFONT lf; //������ ��������� LOGFONT
	lf.lfCharSet = DEFAULT_CHARSET; //�������� �� ���������
	lf.lfPitchAndFamily = DEFAULT_PITCH; //�������� �� ���������
	strcpy(lf.lfFaceName, "Arial"); //�������� � ������ �������� ������ 
	lf.lfHeight = 24; //������
	lf.lfEscapement = 0; //����� ��� ��������
	HFONT hFont = CreateFontIndirect(&lf); //�����
	lf.lfItalic = true;

	static LOGFONT lf2; //������ ��������� LOGFONT
	lf2.lfCharSet = DEFAULT_CHARSET; //�������� �� ���������
	lf2.lfPitchAndFamily = DEFAULT_PITCH; //�������� �� ���������
	strcpy(lf2.lfFaceName, "Times New Roman"); //�������� � ������ �������� ������ 
	lf2.lfHeight = 16; //������
	lf2.lfEscapement = 0; //����� ��� ��������
	HFONT hFont2 = CreateFontIndirect(&lf2); //�����
	lf2.lfItalic = false;

	static BOOL isChecked;
	HDC hdc;
	char str[] = "���� ������ ������������";
	PAINTSTRUCT ps;
	static bool fig;
	static bool mouse;
	static int x, y;
	char c1[] = "��������";
	char c2[] = "����";
	char c3[] = "�������� ������ ������";
	static HMENU hMainMenu;
	static HMENU hOptionsMenu;
	static int cxClient, cyClient;
	
	R = a / 2;
	HBRUSH Hatchbr1;
	HBRUSH Hatchbr2;
	HPEN hPen;
	static DLGPROC lpfnDlgProc;
	
	switch (Message) {
	case WM_SETFOCUS:
	{
		SetFocus(hEdit);
		return 0;
	}
	case WM_LBUTTONUP:
		x = LOWORD(lparam);
		y = HIWORD(lparam);
		InvalidateRect(hwnd, NULL, TRUE);
		mouse = true;
		break;
	case WM_SIZE:
		cxClient = LOWORD(lparam);
		cyClient = HIWORD(lparam);
		InvalidateRect(hwnd, NULL, TRUE);
	case WM_COMMAND:
		if (wparam == 11111)
		{
			// ���������� ��� ������� ���������� ������
			lpfnDlgProc = (DLGPROC)MakeProcInstance((FARPROC)DlgProc, hInst);
			// ������� ��������� ���������� ������
			DialogBox(hInst, "DIALOG_OK", hwnd, lpfnDlgProc);
		}
		// ��������� ��������� ���������� ���������
	  // �� ������
		if (wparam == 10001)
		{
			if (HIWORD(lparam) == EN_ERRSPACE)
			{
				MessageBox(hwnd, "���� ������",
					"Edit error!", MB_OK);
			}
		}
		// ��������� �� ������
		else if (wparam == 10000)
		{
			char chBuff[80];
			WORD cbText;
			// ���������� � ������ ����� ������
			// �������� ������� ������ � ������
			* (WORD *)chBuff = sizeof(chBuff) - 1;
			// �������� �� ��������� ������ ����������
			// ������ ������. ������� ���������� ����������
			// ����, ������������� � �����
			cbText = SendMessage(hEdit, EM_GETLINE, 0,
				(LPARAM)(LPSTR)chBuff);
			// ��������� ����� �������� �����
			chBuff[cbText] = '\0';
			int k = atoi(chBuff);
			if (k)
				a = k;
			InvalidateRect(hwnd, NULL, TRUE);
			// ������� ���������� ������ �� �����
			MessageBox(hwnd, chBuff,
				"����� ����� �������:", MB_OK);
		}
		if (LOWORD(wparam) == 1001)
		{
			if (fig == false) {
				CheckDlgButton(hwnd, 10003, BST_CHECKED);				
			}
			else
			{
				CheckDlgButton(hwnd, 10003, BST_UNCHECKED);
			}
			fig = !fig;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		// ���� ������� ������
		if (LOWORD(wparam) == 10003)
		{
			if (fig == false) {
				CheckDlgButton(hwnd, 10003, BST_CHECKED);
			}
			else
			{
				CheckDlgButton(hwnd, 10003, BST_UNCHECKED);
			}
			fig = !fig;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_CREATE:
		// ������� ������ ����.
		hMainMenu = CreateMenu();
		// ������� �������.
		hOptionsMenu = CreatePopupMenu();
		// ���������� ��������� "������� ������".
		CreateMenuItem(hOptionsMenu, c3, 0, 1001, NULL);
		// ���������� ������ "������� ������" � �������� ����.
		CreateMenuItem(hMainMenu, c1, 0, 0, hOptionsMenu);
		CreateMenuItem(hMainMenu, c2, 1, 0, NULL);
		// ������������ ���� � ����.
		SetMenu(hwnd, hMainMenu);
		// �������� ������ ����.
		DrawMenuBar(hwnd);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(128, 0, 0)); //���� ������
		TextOut(hdc, 10, 10, str, strlen(str)); //������� �����
		DeleteObject(hFont); //�������� �� ������ ������ ������

		SelectObject(hdc, hFont2);
		SetTextColor(hdc, RGB(0,0,0));
		TextOut(hdc, 10, 50, "������� ����� ������� ��������: ", strlen("������� ����� ������� ��������: "));
		DeleteObject(hFont);

		if (mouse)
		{
			Ellipse(hdc, x - 5, y - 5, x + 5, y + 5);
		}
		if (fig) //��������� ������ 
		{
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			SelectObject(hdc, hPen);
			Hatchbr2 = CreateHatchBrush(HS_HORIZONTAL, RGB(0, 0, 255));
			SelectObject(hdc, Hatchbr2);

			Ellipse(hdc, (cxClient - 260 - a) / 2 + 260, (cyClient - 3 * R) / 2, (cxClient - 260 - a) / 2 + 260 + a, (cyClient - 3 * R) / 2 + 2 * R);
			
			DeleteObject(Hatchbr2);

			Hatchbr1 = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 0, 255));
			SelectObject(hdc, Hatchbr1);
			Rectangle(hdc, (cxClient - 260 - a) / 2 + 260, (cyClient - 3 * R) / 2 + R, (cxClient - 260 - a) / 2 + 260 + a, (cyClient - 3 * R) / 2 + 3 * R);

			DeleteObject(hPen);
			DeleteObject(Hatchbr1);
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_CLOSE:
		if (IDOK == MessageBox(hwnd, "�������?", "", MB_OKCANCEL | MB_ICONQUESTION))
			SendMessage(hwnd, WM_DESTROY, NULL, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wparam, lparam);
	}
	return 0;
}
BOOL CreateMenuItem(HMENU hMenu /*������������� ����*/, char* str /*��������� ����*/,
	UINT uID, UINT wID, HMENU hSubMenu)
{
	// ��������� ��������� mi.
	MENUITEMINFO mi;
	mi.cbSize = sizeof(MENUITEMINFO);
	mi.fMask = MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	mi.fType = MFT_STRING;
	mi.fState = MFS_ENABLED;
	mi.dwTypeData = str;
	mi.cch = sizeof(str);
	mi.wID = wID;
	mi.hSubMenu = hSubMenu; // �������� �������.
	// ��������� ����.
	return InsertMenuItem(hMenu, uID, FALSE, &mi);
}
BOOL CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// ������������� ���������� ������
	case WM_INITDIALOG:
	{
		return TRUE;
	}
	case WM_COMMAND:
	{
		switch (wParam)
		{
			// ��������� �� ������ "OK"
		case IDOK:
			
			// ������ ���������� ������.
			// ��� ��������� ��������, ����� ������������
			// �������� �� ������� <Esc>
		case IDCANCEL:
		{
			// ������������� ���� ���������� �������
			EndDialog(hdlg, 0);
			return TRUE;
		}
		}
	}
	}
	return FALSE;
}
