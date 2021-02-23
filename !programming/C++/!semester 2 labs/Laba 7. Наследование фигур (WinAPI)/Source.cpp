#include <vector>
#include <windows.h>
#include <string>
#include <sstream>
#include "Rhombus2.h"
#include "Trapezoid2.h"
//
//данные вводятся в 1-2 поляв зависимости что нужно
//потом считать- они сохранятся
//потом- нужное действие
//комаровский когда принимал просил еще акселераторы добавить, но принял



static int x = 250, y = 250, angle = 0;
static float temp1 = 0, temp2 = 0;
static KPoint p(x, y);
static KShape sh(x, y, angle);
static Rhombus par(x,y,30);
static Rhombus2 par2(x, y, 30);
static Trapezoid tr(x, y, angle, 80, 200, 70, 20);
static Trapezoid2 tr2(tr);
HWND hEdit1;
HWND hEdit2;

BOOL CreateMenuItem(HMENU, char*, UINT, UINT, HMENU);
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,                            /*handle на текущий экземпляр приложения*/
	HINSTANCE hPrevInstance,                                       /*handle предыдущего запущенного экземпляра этого же приложения*/
	LPSTR     lpCmdLine,                                           /*параметры командной строки, передаваемой в приложение*/
	int       nCmdShow)                                            /*определяет способ показа главного окна нашего приложения*/

{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HWND hwnd;                                                     /*дескриптор окна*/
	
	MSG msg;
	WNDCLASS w;                                                    /*класс окна*/
	memset(&w, 0, sizeof(WNDCLASS));                               /*во многих полях должно быть 0, поэтому обнуляем их все*/
	w.style = CS_HREDRAW | CS_VREDRAW;                             /*заполняем поля класса*/
	w.lpfnWndProc = (WNDPROC)WndProc;
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = "My Class";
	RegisterClass(&w);                                             /*регистрируем класс*/
	hwnd = CreateWindow("My Class", "Наследование фигур", WS_OVERLAPPEDWINDOW,     /* создаем окно*/
		300, 200, 600, 500, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);                                      /*показываем окно и обновляем его*/
	UpdateWindow(hwnd);
	hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_RIGHT,  /*для считывания данных*/
		10, 60, 80, 30, hwnd, (HMENU)10001, hInstance, NULL);
	hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, "edit", "", WS_CHILD | WS_VISIBLE | ES_RIGHT,
		10, 95, 80, 30, hwnd, (HMENU)10002, hInstance, NULL);
	CreateWindow("button", "Считать данные", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,     /* кнопка*/
		100, 77, 120, 30, hwnd, (HMENU)10000, hInstance, NULL);
	while (GetMessage(&msg, NULL, 0, 0))                            /*запускаем цикл обработки сообщений*/
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}

LONG WINAPI WndProc(HWND hwnd,                    /*окно, в которое мы передаем сообщение Windows*/
	             UINT Message,                    /*само сообщение*/
	            WPARAM wparam,                    /*дополнительные параметры для конкретного сообщения*/
	            LPARAM lparam)
{
	HDC hdc;                           

	static HMENU hMainMenu;
	static HMENU hOptionsMenu;
	static HMENU hOptionsMenu1;
	static HMENU hOptionsMenu2;
	static HMENU hOptionsMenu3;
	static HMENU hOptionsMenu4;
	static HMENU hOptionsMenu5;
	static HMENU hOptionsMenu6;

	char Tools[20] = "Tools";
	char Point[20] = "Point";
	char Fig1[20] = "Shape";
	char Fig2[20] = "Parallelogram";
	char Hide[20] = "Hide";
	char Show[20] = "Show";
	char Shift[20] = "Shift";
	char MoveTo[20] = "MoveTo";
	char Rotate[20] = "Rotate";
	char Explode[20] = "Explode";
	char ChangeA[20] = "ChangeA";
	char Filled[30] = "Filled parallelogram";
	char Trap[20] = "Trapezoid";
	char TrapF[30] = "Filled trapezoid";
	
	char temp[10];            /*строка для чтения из edit*/
	std::string s;            /*строка для тестирования edit*/
	std::ostringstream strs;

	switch (Message) {
	case WM_CREATE:		

		hMainMenu = CreateMenu();                       // Создание главное меню.	
		hOptionsMenu = CreatePopupMenu();
		hOptionsMenu1 = CreatePopupMenu();
		hOptionsMenu2 = CreatePopupMenu();
		hOptionsMenu3 = CreatePopupMenu();
		hOptionsMenu4 = CreatePopupMenu();
		hOptionsMenu5 = CreatePopupMenu();
		hOptionsMenu6 = CreatePopupMenu();

		CreateMenuItem(hMainMenu, Point, 0, 1, hOptionsMenu1);
		CreateMenuItem(hOptionsMenu1, Show, 0, 11, NULL);
		CreateMenuItem(hOptionsMenu1, Hide, 0, 12, NULL);
		CreateMenuItem(hOptionsMenu1, Shift, 0, 13, NULL);
		CreateMenuItem(hOptionsMenu1, MoveTo, 0, 14, NULL);

		CreateMenuItem(hMainMenu, Fig1, 0, 2, hOptionsMenu2);
		CreateMenuItem(hOptionsMenu2, Show, 0, 21, NULL);
		CreateMenuItem(hOptionsMenu2, Hide, 0, 22, NULL);
		CreateMenuItem(hOptionsMenu2, Shift, 0, 23, NULL);
		CreateMenuItem(hOptionsMenu2, MoveTo, 0, 24, NULL);
		CreateMenuItem(hOptionsMenu2, Rotate, 0, 25, NULL);
		CreateMenuItem(hOptionsMenu2, Explode, 0, 26, NULL);
		

		CreateMenuItem(hMainMenu, Fig2, 0, 3, hOptionsMenu3);
		CreateMenuItem(hOptionsMenu3, Show, 0, 31, NULL);
		CreateMenuItem(hOptionsMenu3, Hide, 0, 32, NULL);
		CreateMenuItem(hOptionsMenu3, Shift, 0, 33, NULL);
		CreateMenuItem(hOptionsMenu3, MoveTo, 0, 34, NULL);
		CreateMenuItem(hOptionsMenu3, Rotate, 0, 35, NULL);
		CreateMenuItem(hOptionsMenu3, Explode, 0, 36, NULL);
		CreateMenuItem(hOptionsMenu3, ChangeA, 0, 37, NULL);


		CreateMenuItem(hMainMenu, Filled, 0, 4, hOptionsMenu4);
		CreateMenuItem(hOptionsMenu4, Show, 0, 41, NULL);
		CreateMenuItem(hOptionsMenu4, Hide, 0, 42, NULL);
		CreateMenuItem(hOptionsMenu4, Shift, 0, 43, NULL);
		CreateMenuItem(hOptionsMenu4, MoveTo, 0, 44, NULL);
		CreateMenuItem(hOptionsMenu4, Rotate, 0, 45, NULL);
		CreateMenuItem(hOptionsMenu4, Explode, 0, 46, NULL);
		CreateMenuItem(hOptionsMenu4, ChangeA, 0, 47, NULL);
		
		CreateMenuItem(hMainMenu, Trap, 0, 5, hOptionsMenu5);
		CreateMenuItem(hOptionsMenu5, Show, 0, 51, NULL);
		CreateMenuItem(hOptionsMenu5, Hide, 0, 52, NULL);
		CreateMenuItem(hOptionsMenu5, Shift, 0, 53, NULL);
		CreateMenuItem(hOptionsMenu5, MoveTo, 0, 54, NULL);
		CreateMenuItem(hOptionsMenu5, Rotate, 0, 55, NULL);
		CreateMenuItem(hOptionsMenu5, Explode, 0, 56, NULL);
		
		CreateMenuItem(hMainMenu, TrapF, 0, 6, hOptionsMenu6);
		CreateMenuItem(hOptionsMenu6, Show, 0, 61, NULL);
		CreateMenuItem(hOptionsMenu6, Hide, 0, 62, NULL);
		CreateMenuItem(hOptionsMenu6, Shift, 0, 63, NULL);
		CreateMenuItem(hOptionsMenu6, MoveTo, 0, 64, NULL);
		CreateMenuItem(hOptionsMenu6, Rotate, 0, 65, NULL);
		CreateMenuItem(hOptionsMenu6, Explode, 0, 66, NULL);

		
		SetMenu(hwnd, hMainMenu);                       // Присоединение меню к окну.	
		DrawMenuBar(hwnd);                              // Создание полосы меню.
		break;
	case WM_COMMAND:
		if (LOWORD(wparam) == 11)                      /*точка*/
		{
			p.Show();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 12)
		{
			p.Hide();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 13)
		{
			p.Shift(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 14)
		{
			p.MoveTo(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}

		if (LOWORD(wparam) == 21)                       /*shape*/
		{
			sh.Show();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 22)
		{
			sh.Hide();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 23)
		{
			sh.Shift(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 24)
		{
			sh.MoveTo(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 25)
		{
			sh.Rotate(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 26)
		{
			sh.Explode(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}

		                                            /*параллелограм*/
		if (LOWORD(wparam) == 31)                      
		{
			par.Show();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 32)
		{
			par.Hide();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 33)
		{
			par.Shift(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 34)
		{
			par.MoveTo(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 35)
		{
			par.Rotate(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 36)
		{
			par.Explode(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 37)
		{
			par.ChangeA(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}

		if (LOWORD(wparam) == 41)                  /*параллелограм с закрашенной штукой*/
		{
			par2.Show();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 42)
		{
			par2.Hide();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 43)
		{
			par2.Shift(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 44)
		{
			par2.MoveTo(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 45)
		{
			par2.Rotate(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 46)
		{
			par2.Explode(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 47)
		{
			par2.ChangeA(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}

		if (LOWORD(wparam) == 51)                  /*трапеция*/
		{
			tr.Show();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 52)
		{
			tr.Hide();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 53)
		{
			tr.Shift(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 54)
		{
			tr.MoveTo(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 55)
		{
			tr.Rotate(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 56)
		{
			tr.Explode(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}

		if (LOWORD(wparam) == 61)                  /*закрашенная трапеция*/
		{
			tr2.Show();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 62)
		{
			tr2.Hide();
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 63)
		{
			tr2.Shift(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 64)
		{
			tr2.MoveTo(temp1, temp2);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 65)
		{
			tr2.Rotate(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (LOWORD(wparam) == 66)
		{
			tr2.Explode(temp1);
			InvalidateRect(hwnd, NULL, TRUE);
		}

		if (LOWORD(wparam) == 10000)
		{
			
			GetWindowText(hEdit1, temp, 7);
			temp1 = atof(temp);
			GetWindowText(hEdit2, temp, 7);
			temp2 = atof(temp);
			strs << temp1;
			s = strs.str();
			SetWindowText(hwnd, s.c_str());

		}
		break;
	case WM_CLOSE:
		if (IDOK == MessageBox(hwnd, "Выйти?", "Внимание!", MB_OKCANCEL | MB_ICONQUESTION))
			SendMessage(hwnd, WM_DESTROY, NULL, NULL);
		break;
	case WM_LBUTTONDOWN:
		x = LOWORD(lparam);
		y = HIWORD(lparam);
		/*tr2.MoveTo(x, y);
		tr2.Show();*/
		/*par2.MoveTo(x, y);
		par2.Show();*/
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);  /*присоединение контекста устройства к окну*/

		p.print(hdc);
		sh.print(hdc);
		par.print(hdc);
		par2.print(hdc);
		tr.print(hdc);
		tr2.print(hdc);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY:                          /*это сообщение окно получает при своем уничтожении*/
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wparam, lparam); /*обработка тех сообщений, которые не обрабатываются*/
	}
	return 0;
}
BOOL CreateMenuItem(
	                HMENU hMenu,
	                  char* str, /*заголовок пункта меню*/
	                   UINT uID, /*идентификатор пункта меню*/
	                   UINT wID, 
	              HMENU	hSubMenu
)
{
	// Заполняем структуру mi.
	MENUITEMINFO mi;
	mi.cbSize = sizeof(MENUITEMINFO);
	mi.fMask = MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	mi.fType = MFT_STRING;
	mi.fState = MFS_ENABLED;
	mi.dwTypeData = str;
	mi.cch = sizeof(str);
	mi.wID = wID;
	mi.hSubMenu = hSubMenu; // Устновка подменю.
	// Вставляем меню.
	return InsertMenuItem(hMenu, uID, FALSE, &mi);
}
