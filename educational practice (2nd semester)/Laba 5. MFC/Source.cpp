#define _CRT_SECURE_NO_WARNINGS
#include "afxwin.h" //MFC основные и стандартные компоненты
#include "afxext.h"
#include "resource.h" 
#include <chrono>
#include <ctime>

#define IDC_MYBUTTON 100 //Идентификатор кнопки

#define IDC_MYEDIT 102 
#define ID_FILE_EXIT 40001
#define ID_FILE_DIALOG 40003
#define ID_FILE_PAINT 40002


class CMyApp : public CWinApp
{
public:
	CMyApp(); //Конструктор по умолчанию
	virtual BOOL InitInstance(); //Стандартная инициализация
};

class CMainWnd : public CFrameWnd
{
public:
	CMainWnd(); //Конструктор по умолчанию
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT, CPoint);
	afx_msg void OnRButtonDown(UINT, CPoint);
	afx_msg void OnMouseMove(UINT, CPoint cp);
	afx_msg void OnKeyDown(UINT, UINT, UINT);
	afx_msg void MenuExit();
	afx_msg void OnPaint();
	afx_msg void OnP();
	afx_msg void OnButton();
	afx_msg void OnDialog();
	~CMainWnd();
private:

	CButton *MyButton;
	CStatusBar m_wndStatusBar; //Класс панели состояния
	CMenu m_wndMenu;
	CRect Place;
	bool b1 = 0, b2 = 0, b3 = 0, b4 = 0;
	int x = 0, y = 0;
	int x1 = 0, y1 = 0;
	int n=0;
	char c = '\0';
	DECLARE_MESSAGE_MAP();
};




BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)	// таблица откликов на сообщения
	ON_WM_CREATE()
	ON_COMMAND(IDC_MYBUTTON, OnButton)
	ON_COMMAND(ID_FILE_EXIT, MenuExit)
	ON_COMMAND(ID_FILE_PAINT, OnP)
	ON_COMMAND(ID_FILE_DIALOG, OnDialog)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()		// реакция на нажатие левой кнопки мыши
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()			// реакция на нажатие клавиши
END_MESSAGE_MAP()

void CMainWnd::OnDialog()
{
	CDialog about(IDD_DIALOG1);
	about.DoModal();
}

void CMainWnd::OnP()
{
	b1 == 1 ? b1 = 0 : b1 = 1;
	Invalidate();
}


void CMainWnd::OnButton()
{
	AfxMessageBox("Была нажата кнопка");
}

void CMainWnd::OnPaint()
{
	RECT rect;
	GetClientRect(&rect);
	CPaintDC dc(this);
	if (b1 == 1)
	{
		
		dc.MoveTo(rect.left, rect.bottom);
		dc.LineTo(rect.right, rect.top);
	}
	if (b2 == 1)
	{
		char string1[6];
		char string2[6];
		_itoa(x, string1,10);
		_itoa(y, string2, 10);
		dc.TextOut(rect.right - 50, rect.top + 50, string1);
		dc.TextOut(rect.right - 50, rect.top + 80, string2);
	}
	if (b3 == 1)
	{	
		char ch[20];
		_itoa(n, ch, 10);
		dc.TextOut(x1, y1, ch);
	}
	if (b4 == 1)
		dc.TextOut(rect.left+30, rect.bottom-80, c);
}
void CMainWnd::OnMouseMove(UINT, CPoint cp)
{
	x = cp.x;
	y = cp.y;
	b2 = 1;
	Invalidate();
}

void CMainWnd::MenuExit()
{
	DestroyWindow(); // Уничтожить окно
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_wndStatusBar.Create(this);
	m_wndMenu.LoadMenu(IDR_MENU1); // Загрузить меню из файла ресурса
	SetMenu(&m_wndMenu); // Установить меню
	return 0;
}

void CMainWnd::OnKeyDown(UINT u, UINT, UINT)
{
	c = u-48+'0';
	b4 = 1;
	Invalidate();
}

void CMainWnd::OnRButtonDown(UINT, CPoint cp)
{
	x1 = cp.x;
	y1 = cp.y;
	b3 = 1;
	n = std::rand();
	Invalidate();
}
void CMainWnd::OnLButtonDblClk(UINT, CPoint)
{
	
	AfxMessageBox("Была 2 раза нажата левая кнопка мыши.");
}

CMainWnd::CMainWnd()
{
	Create(NULL, "Окно приложения пользователя", WS_OVERLAPPEDWINDOW,
		rectDefault, NULL, NULL); //Создать окно программы

	Place.left = 350;
	Place.top = 350;
	Place.right = 470;
	Place.bottom = 470;
	
	MyButton = new CButton();
	if (MyButton != NULL)
		MyButton->Create("Кнопка", WS_CHILD | WS_VISIBLE | SS_CENTER,
			CRect(120, 10, 220, 50), this, IDC_MYBUTTON);

}

CMainWnd::~CMainWnd() //Деструктор класса
{
	if (MyButton != NULL) delete MyButton; //Удалить динамический объект
}

CMyApp::CMyApp() //Конструктор главного класса приложения
{}
BOOL CMyApp::InitInstance() //Стандартная инициализация
{
	m_pMainWnd = new CMainWnd(); //Создать указатель на класс окна
	ASSERT(m_pMainWnd); //Проверить его правильность
	m_pMainWnd->ShowWindow(SW_SHOW); //Показать окно
	m_pMainWnd->UpdateWindow(); //Обновить окно
	return TRUE; //Вернуть, что все нормально
};
CMyApp theApp;