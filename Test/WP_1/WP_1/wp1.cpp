//1강 윈도우 생성
WM_CREATE 윈도우가 생성될 때 발생 WM_RBUTTONDOWN 마우스 오른쪽 버튼을 누르면 발생
WM_NCACTIVATE 윈도우의 비 작업영역의 활성화 또는 비 활성화시
발생(윈도우 타이틀 바 색상 제어) WM_RBUTTONUP 마우스 오른쪽 버튼을 떼면 발생
WM_DESTROY 윈도우가 파괴되기 직전에 발생 WM_MOUSEMOVE 마우스가 움직이고 있으면 발생
WM_PAINT 윈도우가 다시 그려져야 하면 발생 WM_SETCURSOR 마우스의 아이콘을 재설정해야 할 때 발생
WM_LBUTTONDOWN 마우스 왼쪽 버튼을 누르면 발생 WM_TIMER 타이머 설정 시 주기적으로 발생
WM_LBUTTONUP 마우스 왼쪽 버튼을 떼면 발생 WM_COMMAND 메뉴, 버튼, 액셀러레이터 선택 시 발생//윈도우 메시지typedef struct tagMSG {
	HWND hwnd; //--- 윈도우 핸들
	UINT message; //--- 메시지 id
	WPARAM wParam; //--- 메시지 전달 인자 1: 32 (또는 64) 비트 LONG_PTR
	LPARAM lParam; //--- 메시지 전달 인자 2: 32 (또는 64) 비트 UINT_PTR
	DWORD time; //--- 이벤트 발생 시각
	POINT pt; //--- 이벤트 발생 시 커서 위치
} MSG, * PMSG;

//
typedef struct _WNDCLASSEX {
	UINT cbSize; //--- 본 구조체의 크기
	UINT style; //--- 출력 스타일
	WNDPROC lpfnWndProc; //--- 프로시저 함수
	int cbClsExtra; //--- 클래스 여분 메모리--- 사용안함
	int cbWndExtra; //--- 윈도우 여분 메모리--- 사용안함
	HANDLE hInstance; //--- 윈도우 인스턴스
	HICON hIcon; //--- 아이콘
	HCURSOR hCursor; //--- 커서
	HBRUSH hbrBackground; //--- 배경색
	LPCTSTR lpszMenuName; //--- 메뉴이름
	LPCTSTR lpszClassName; //--- 클래스 이름
	HICON hIconSm; //--- 작은 아이콘
} WNDCLASSEX;

{
	HWND CreateWindow
		lpClassName 윈도우 클래스에서 설정한 윈도우 클래스 이름
		lpWindowName 윈도우의 타이틀 이름
		dwStyle 윈도우의 다양한 스타일
		WS_OVERLAPPED : 디폴트 윈도우
		WS_CAPTION : 타이틀 바를 가진 윈도우
		WS_HSCROLL / WS_VSCROLL : 수평 / 수직 스크롤 바
		WS_MAXIMIZEBOX / WS_MINIMIZEBOX : 최대화 / 최소화 버튼
		WS_SYSMENU : 시스템 메뉴
		WS_THICKFRAME : 크기 조정이 가능한 두꺼운 경계선
		WS_BORDER : 단선으로 된 경계선, 크기 조정 불가능
		WS_POPUP : 팝업 윈도우(WS_CHILD와 같이 쓸 수 없다)
		WS_CHILD : 차일드 윈도우
		WS_VISIBLE : 윈도우를 만들자마자 화면에 출력
		WS_OVERLAPPEDWINDOW : 가장 일반적인 윈도우 스타일
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME |
		WS_MINIMIZEBOX | WS_MAXIMIZEBOX
		WS_POPUPWINDOW : 일반적인 팝업 윈도우
		WS_POPUP | WS_BORDER | WS_SYSMENU
		x, y 윈도우의 좌표값(좌측 상단 기준)
		nWidth / nHeight 윈도우의 가로, 세로 크기(픽셀 단위)
		hWndParent 부모 윈도우 핸들, 부모가 없을 때는 NULL
		hMenu 윈도우의 상단에 붙는 메뉴의 핸들 : 메뉴가 없을 때
		는 NULL
		hInstance WinMain에서 받은 인스턴스 핸들
}


//문제 1-1 윈도우 기본 생성
#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 2";

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

//2강 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;

	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//TextOut wsprintf
TCHAR str_1[15] = _T(“나는 winple”);//문자열 사용 1번
TCHAR lpOut[100];//문자열 사용 2번
int x1 = (rand() % 70) * 10, y1 = (rand() % 50) * 10;
wsprintf(lpOut, L"1st sentence : (%d, %d)", x1, y1);
TextOut(hdc, x1, y1, lpOut, lstrlen(lpOut));
//컬러 텍스트 박스 만들기
{
	RECT rect1;
	TCHAR lpOut[100];
	srand(time(NULL));
	rect1.left = 0;
	rect1.top = 0;
	rect1.right = 260;
	rect1.bottom = 290;
	SetBkColor(hdc, RGB(br1, bg1, bb1));
	SetTextColor(hdc, RGB(r1, g1, b1));
	wsprintf(lpOut, L"abcdefghijklmnopqrstuvwxyzsl;gjreghioilajsdajsufhoefhweioufbhoabcdefghij");
	DrawText(hdc, lpOut, lstrlen(lpOut), &rect1, DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=
}
InvalidateRect(hwnd, NULL, TRUE)//메시지 끝내고 다음 메시지 Paint 불러와

//가상키 코드 테이블
{
	VK_CANCEL Ctrl + Break VK_END End
		VK_BACK Backspace VK_HOME Home
		VK_TAB Tab VK_LEFT 좌측 화살표
		VK_RETURN Enter VK_UP 위쪽 화살표
		VK_SHIFT Shift VK_RIGHT 우측 화살표
		VK_CONTROL Ctrl VK_DOWN 아래쪽 화살표
		VK_MENU Alt VK_INSERT Insert
		VK_CAPITAL Caps Lock VK_DELETE Delete
		VK_ESCAPE Esc VK_F1 ~VKF10 F1 - F10
		VK_SPACE Space VK_NUMLOCK Num Lock
		VK_PRIOR Page Up VK_SCROLL Scroll Lock
		VK_NEXT Page Down
}
//Caret
{
	BOOL CreateCaret(HWND hwnd, HBITMAP hBitmap, int nWidth, int nHeight);	‒ 캐럿 만들기 함수 		‒ HWND hwnd : 캐럿을 놓을 윈도우 핸들 		‒ HBITMAP hbitmap : 비트맵 캐럿 		‒ int nWidth, nHeight : 캐럿의 폭과 높이 	• BOOL ShowCaret(HWND hwnd); 		‒ 캐럿 출력하기 		‒ HWND hwnd : 캐럿이 출력될 윈도우 핸들 	• BOOL SetCaretPos(int x, int y); 		‒ 캐럿 위치 설정하기 		‒ int x, int y : 캐럿의 x, y 위치 	• BOOL GetCaretPos(LPPOINT lpPoint);		— 캐럿의 위치를 조사하기 		— LPPOINT lpPoint : 캐럿의 위치를 가져온다.	• BOOL SetCaretBlinkTime(UINT uMSeconds); 		— 캐럿의 깜빡임 속도를 설정 		— UINT uMSeconds : 밀리세컨 단위의 깜빡임 속도 	• BOOL HideCaret(HWND hwnd); 		‒ 캐럿 감추기 		‒ HWND hwnd : 캐럿이 놓여있는 윈도우 핸들 	• BOOL DestroyCaret(); 		— 캐럿 삭제하기
	//캐럿 위치
		BOOL GetTextExtentPoint32(HDC hdc, LPCTSTR lpString, int cbString, LPSIZE lpSize);
		SIZE size;
		GetTextExtentPoint32(hdc, L"Abijc", 5, &size);
		TextOut(hdc, x, y, ”Abijc”, 5);
		SetCaretPos(x + size.cx, y); //--- x좌표에 출력문자열 길이 합산
}
//윈도우에 점 그리기
{
	COLORREF SetPixel(HDC hdc, int nXpos, int nYpos, COLORREF color);
	-hdc: DC 핸들
		- nXpos, nYpos : 설정할 점의 x, y 좌표
		- color : 점을 그리는데 사용 할 색상
		BOOL SetPixelV(HDC hdc, int nxPos, int nYpos, COLORREF color);
	-hdc: DC 핸들
		- nXpos, nYpos : 설정할 점의 x, y 좌표
		- color : 점을 그리는데 사용 할 색상
		COLORREF GetPixel(HDC hdc, int nXPos, int nYpos);
	-hdc: DC 핸들
		- nXpos, nYpos : 설정할 점의 x, y 좌표
		- 리턴 값 : 픽셀의 색상
}
//도형 그리기
{
	MoveToEx(hdc, 10, 30, NULL); // (10, 30) -> (50, 60) 직선 그리기
	LineTo(hdc, 50, 60);
	BOOL Ellipse(HDC hdc, int X1, int Y1, int X2, int Y2);//원그리기
	– X1, Y1: 좌측 상단 좌표값(x와 y 최소값)
		– X2, Y2 : 우측 하단 좌표값(x와 y 최대값)		BOOL Rectangle(HDC hdc, int X1, int Y1, int X2, int Y2);//삼각형
	– X1, Y1: 좌측 상단 좌표값(x와 y 최소값)
		– X2, Y2 : 우측 하단 좌표값(x와 y 최대값)
		int FillRect(HDC hDC, CONST RECT* lprc, HBRUSH hbr)
		– hDC : DC 핸들
		– lprc : 사각형의 좌표값
		– hbr : 내부 색		int FrameRect(HDC hDC, CONST RECT* lprc, HBRUSH hbr);
	– hDC : DC 핸들
		– lprc : 사각형의 좌표값
		– hbr : 외곽선 색
		int InvertRect(HDC hDC, CONST RECT* lprc);
	– hDC : DC 핸들
		– lprc : 사각형의 좌표값
		BOOL OffsetRect(LPRECT lprc, int dx, int dy);
	– 주어진 Rect를 dx, dy만큼 이동한다.
		BOOL InflateRect(LPRECT lprc, int dx, int dy);
	– 주어진 Rect를 dx, dy만큼 늘이거나 줄인다.
		BOOL IntersectRect(LPRECT lprcDest, CONST RECT* lprcSrc1, CONST RECT lprcSrc2);
	– 두 RECT(lprcSrc1, lprcSrc2)가 교차되었는지 검사한다.
		– lprcDest : 교차된 RECT 부분의 좌표값이 저장된다.
		BOOL UnionRect(LPRECT lprcDest, CONST RECT* lprcSrc1, CONST RECT* lprcSrc2)
		– 두 RECT(lprcSrc1, lprcSrc2) 를 union 시킨다.
		– lprcDest : 두 사각형을 합한 사각형의 좌표값이 저장된다.
		BOOL PtInRect(CONST RECT* lprc, POINT pt);
	– 특정 좌표 pt가 lprc 영역 안에 있는지 검사한다.		BOOL Polygon(HDC hdc, CONST POINT* lppt, int cPoints);
	-hdc: DC 핸들
		- lppt : 다각형 꼭지점의 좌표 값이 저장된 리스트
		- cPoints : 꼭지점의 개수}
펜브러쉬
{
	– 펜 :
• HPEN CreatePen(int fnPenStyle, int nWidth, COLORREF crColor);
– 브러시 :
• HBRUSH CreateSolidBrush(COLORREF crColor);
• HBRUSH CreateHatchBrush(int iHatch, COLORREF crColor);
– 폰트(글꼴) :
• HFONT CreateFont(int cHeight, int cWidth, int cEscapement, int cOrientation, int cWeight, DWORD bItalic, DWORD bUnderline,
DWORD bStrikeOut, DWORD iCharSet, DWORD iOutPrecision, DWORD iClipPrecision, DWORD iQuality, DWORD iPitchAndFamily,
LPCSTR pszFaceName);
• HFONT CreateFontIndirect(const LOGFONT* lplf);
– 비트맵 :
• HBITMAP CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitCount, const VOID* lpBits);
• HBITMAP CreateCompatibleBitmap(HDC hdc, int cx, int cy);
}
Ex) 빨간원그리기
{
	HBRUSH hBrush, oldBrush;
switch (iMsg) {
case WM_PAINT:
hdc = BeginPaint(hwnd, &ps); // DC 얻어오기
hBrush = CreateSolidBrush(RGB(255,0,0)); // GDI: 브러시 만들기
oldBrush = (HBRUSH)SelectObject(hdc, hBrush); // 새로운 브러시 선택하기
Ellipse(hdc, 20,20, 300,300); // 선택한 브러시로 도형 그리기
SelectObject(hdc, oldBrush); // 이전의 브러시로 돌아가기
DeleteObject(hBrush); // 만든 브러시 객체 삭제하기
EndPaint(hwnd, &ps); // DC 해제하기
return 0;
}
}

//2-6강 화면에 그림 그리기
{
PAINTSTRUCT ps;
HDC hdc;
RECT rect;
SIZE size;
static TCHAR str[100][1000];
int r1, g1, b1;
int dx = 760 / randDivX;
int dy = 560 / randDivY;

for (int i = 0; i < 10000; i++)
	randPicture[i] = rand() % 6;

TCHAR ystr[100] = { 'X' };
TCHAR bstr[100] = { 'O' };
TCHAR cstr[100] = { 'X' };
TCHAR dstr[100] = { 'O' };
TCHAR estr[100] = { 'X' };
TCHAR fstr[100] = { 'O' };
TCHAR nstr[100] = { ' ', ' ' };

switch (uMsg)

case WM_CREATE:
	break;
case WM_PAINT:
	hdc = BeginPaint(hWnd, &ps);
	//randDivY, randDivX
	for (int Bigy = 0; Bigy < randDivY; Bigy++)
	{
		for (int Bigx = 0; Bigx < randDivX; Bigx++)
		{
			//Box
			{
				r1 = rand() % 257, g1 = rand() % 257, b1 = rand() % 257;
				r2 = rand() % 257, g2 = rand() % 257, b2 = rand() % 257;
				rect.left = Bigx * dx;
				rect.top = Bigy * dy;
				rect.right = (Bigx + 1) * dx;
				rect.bottom = (Bigy + 1) * dy;

				SetBkColor(hdc, RGB(r1, g1, b1));
				SetTextColor(hdc, RGB(r2, g2, b2));
			}
			switch (randPicture[Bigy * randDivX + Bigx])
			{
			case 0:	//X
				for (int y = 0; y < dy / 16; y++)
				{
					for (int x = 0; x < dx / 8; x++)
					{
						if (x == y || x == (dy / 16 - y - 1))
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
					}
				}
				break;
			case 1:	//삼각형
				for (int y = 0; y < dy / 16; y++)
				{
					for (int x = 0; x < dx / 8; x++)
					{
						if (x > y && x < (dy / 8 - y - 1))
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, bstr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
					}
				}
				break;
			case 2: // diamond
				for (int y = 0; y < dy / 32; y++)
				{
					for (int x = 0; x < dx / 8; x++)
					{
						if (x >= dy / 16 - y &&
							x <= dy / 16 + y)
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, cstr, 1);//출력
						else
						TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
					}
				}
				for (int y = dy / 32; y < dy / 16; y++)
				{
					for (int x = 0; x < dx / 8; x++)
					{
						if (x > y &&
							x < (dy / 8 - y - 1))
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, cstr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
					}
				}
				break;
			case 3://butterFly
				for (int y = 0; y < dy / 32; y++)
				{
					for (int x = 0; x < dx / 8; x++)
					{
						if ((x <= y ||
							x > dy / 16 - y - 1) && x < dy / 16 + 1)
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, dstr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
					}
				}
				for (int y = dy / 32; y < dy / 16; y++)
				{
					for (int x = 0; x < dx / 8; x++)
					{
						if ((x >= 0 && x < dy / 16 - y) ||
							(x > y && x <= dy / 16))
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, dstr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
					}
				}
				break;
			case 4: // SandClock
				for (int y = 0; y < dy / 32; y++)
				{
					for (int x = 0; x < dx / 8; x++)
					{
						if ((y <= x &&
							x < dy / 16 - y) && x < dy / 16 + 1)
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, estr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
					}
				}//x > y && x < (dy / 8 - y - 1)
				for (int y = dy / 32; y < dy / 16; y++)
				{
					for (int x = 0; x < dx / 8; x++)
					{
						if ((dy / 16 - y - 1 <= x &&
							x < y + 1) && x < dy / 16 + 1)
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, estr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
					}
				}
				break;

			case 5://double Rect
				for (int y = 0; y < dy / 16; y++)
				{
					for (int x = 0; x < dx / 8; x++)
					{
						if (x == 0 || x == dy / 32 || x == dy / 32 + 1 || x == dy / 16)
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, fstr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
					}
				}
				for (int x = 0; x < dx / 8; x++)
				{
					if (x < dy / 16 + 1)
						TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy), fstr, 1);//출력
					else
						TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy), nstr, 2);//출력
				}
				for (int x = 0; x < dx / 8; x++)
				{
					if (x < dy / 16 + 1)
						TextOut(hdc, (Bigx * dx) + x * 8, ((Bigy + 1) * dy - 16), fstr, 1);//출력
					else
						TextOut(hdc, (Bigx * dx) + x * 8, ((Bigy + 1) * dy - 16), nstr, 2);//출력
				}
				break;
			default:
				break;
			}


		}
	}
}

	//메모장 만들기
{
	static SIZE size;
	PAINTSTRUCT ps;
	HDC hdc;

	static TCHAR str[MAXLINE][100];
	static TCHAR roundstr[MAXLINE][500];
	static TCHAR passstr[MAXLINE][100];
	static TCHAR blankstr[MAXLINE][100];

	static int linecount = 0;
	static int wordcount;

	static int cword = 0;
	static int yPos = 0;

	static int caps = 1;
	static int insert = -1;
	static int password = -1;
	static int round = -1;
	static int blank = -1;

	//백스페이스 전줄로 이동
	//10줄 넘으면 첫줄로 이동
	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15); //--- 캐럿 만들기
		ShowCaret(hwnd);				//--빈 화면에 캐럿 표시
		SetCaretBlinkTime(300);
		wordcount = 0;
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);

		if (wParam == VK_BACK) //--- 백스페이스를 입력하면
		{
			if (cword == 0 && yPos == 0)
				break;
			//만일 cword가 0이라면 전줄로 간다
			if (cword <= 0)
			{
				yPos = yPos - 20;
				cword = lstrlen(str[yPos / 20]);
				wordcount = lstrlen(str[yPos / 20]);
			}
			for (int i = cword; i < wordcount; i++)
			{//캐럿 뒤의 글자들 앞으로 옮기기
				str[yPos / 20][i - 1] = str[yPos / 20][i];
			}
			str[yPos / 20][wordcount - 1] = '\0';
			wordcount--;
			cword--;
		}
		else if (wParam == VK_RETURN) //--- 엔터키를 입력하면: 문자열을 다음줄에 출력
		{
			wordcount = 0; //--- 인덱스 변경
			cword = 0;
			linecount++;
			yPos = yPos + 20;
			if (linecount % 10 == 0 && linecount >= 10)//10이면
			{//linecount가 10이 되면 엔터*2에서 linecount++를 빼고 커서 위치에서 덮어쓰기
				yPos = 0;

			}
		}
		else if (wParam == VK_ESCAPE)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < MAXWORD; j++)
				{
					str[i][j] = '\0';
				}
			}
			linecount = 0;
			wordcount = 0;
			cword = 0;
			yPos = 0;
		}
		else if (wParam == VK_TAB)
		{
			for (int i = 0; i < 4; i++)
			{
				if (wordcount >= MAXWORD - 1)
				{//인덱스 변경
					wordcount = 0; //--- 인덱스 변경
					cword = 0;
					linecount++;
					yPos = yPos + 20;
					break;
				}
				str[yPos / 20][cword++] = ' ';
				wordcount++;
			}
		}
		else if (wParam == '+')
		{
			for (int i = 0; i <= linecount; i++)
			{
				for (int j = 0; j < MAXWORD; j++)
				{
					if (str[i][j] >= '0' && str[i][j] < '9')
						str[i][j]++;
				}
			}
		}
		else if (wParam == '-')
		{
			for (int i = 0; i <= linecount; i++)
			{
				for (int j = 0; j < MAXWORD; j++)
				{
					if (str[i][j] > '0' && str[i][j] <= '9')
						str[i][j]--;
				}
			}
		}
		else
		{
			printf("cword : %d // wordcount : %d\nyPos/20 : %d // linecount : %d\n\n", cword, wordcount, yPos / 20, linecount);//CMD
			//Maxword Insert
			if (wordcount >= MAXWORD && insert == 1)
			{
				wordcount = 0; //--- 인덱스 변경
				cword = 0;
				linecount++;
				yPos = yPos + 20;
				if (linecount % 10 == 0 && linecount >= 10)//10이면
				{//linecount가 10이 되면 엔터*2에서 linecount++를 빼고 커서 위치에서 덮어쓰기
					yPos = 0;
				}
			}
			//Defualt Insert
			if (wordcount < MAXWORD && insert == 1)
			{
				for (int i = wordcount; i >= cword; i--)
				{
					str[yPos / 20][i + 1] = str[yPos / 20][i];
				}
				wordcount++;
			}

			if (cword >= MAXWORD)
			{
				wordcount = 0; //--- 인덱스 변경
				cword = 0;
				linecount++;
				yPos = yPos + 20;
				if (yPos / 20 >= 10)//10이면
				{//linecount가 10이 되면 엔터*2에서 linecount++를 빼고 커서 위치에서 덮어쓰기
					yPos = 0;
				}
			}

			if (caps == -1 && ('a' <= wParam && wParam <= 'z'))//caps가 -1이면 대문자 출력
			{
				str[yPos / 20][cword++] = toupper(wParam); //--- 그 외에는 문자를 캐럿 뒤에 붙인다.
			}
			else
				str[yPos / 20][cword++] = wParam; //--- 그 외에는 문자를 캐럿 뒤에 붙인다.

			if (cword - 1 == wordcount)//문장 마지막에서만 문장길이가 늘어남
				wordcount++;

		}
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT 메시지 발생

		break;

	case WM_KEYDOWN:
		hdc = GetDC(hwnd);

		if (wParam == VK_LEFT)
		{
			if (cword > 0)
			{
				cword--;
			}
		}
		else if (wParam == VK_RIGHT)
		{
			if (cword < wordcount)
			{
				cword++;
			}
		}
		else if (wParam == VK_UP)
		{
			if (lstrlen(str[yPos / 20 - 1]) < cword)
			{
				yPos = yPos - 20;
				cword = lstrlen(str[yPos / 20]);
				wordcount = lstrlen(str[yPos / 20]);
				ReleaseDC(hwnd, hdc);
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
			if (yPos > 0)
			{
				yPos = yPos - 20;
				wordcount = lstrlen(str[yPos / 20]);
			}
		}
		else if (wParam == VK_DOWN)
		{
			if (lstrlen(str[yPos / 20 + 1]) < cword)
			{
				yPos = yPos + 20;
				cword = lstrlen(str[yPos / 20]);
				wordcount = lstrlen(str[yPos / 20]);
				ReleaseDC(hwnd, hdc);
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
			if (yPos < linecount * 20)
			{
				yPos = yPos + 20;
				wordcount = lstrlen(str[yPos / 20]);

			}
		}
		else if (wParam == VK_F1)
		{
			caps = caps * -1;
		}
		else if (wParam == VK_F2)
		{
			password *= -1;
		}
		//???
		else if (wParam == VK_F3)
		{
			int temp = linecount;
			for (int i = MAXLINE; i > 0; i--)
			{
				for (int j = 0; j < MAXWORD; j++)
				{
					str[i][j] = str[i - 1][j];
				}
			}
			for (int j = 0; j < MAXWORD; j++)
			{
				str[0][j] = '\0';
			}
			linecount = temp;
			if (linecount < 9)
				linecount++;
		}
		else if (wParam == VK_F4)
		{
			for (int i = 0; i < MAXWORD; i++)
			{
				str[yPos / 20][i] = '\0';
				wordcount = 0;
				cword = 0;
			}
		}
		else if (wParam == VK_DELETE)
		{
			int start = 0;
			int end = 0;
			bool bcword = false;
			bool endLoop = false;
			for (end = 0; end <= wordcount; end++)
			{
				if (cword == end)
					bcword = true;

				if (bcword == true)//캐럿 위치를 알아내면 공백까지 더하고 끝내라
				{
					while (true)
					{
						if (str[yPos / 20][end] == ' ' || str[yPos / 20][end] == '\0')
						{
							endLoop = true;
							break;
						}
						if (endLoop)
							break;
						end++;
					}
				}
				if (endLoop)
					break;
				if (str[yPos / 20][end] == ' ')//공백마다 단어 초기화
					start = end;


			}
			printf("start : %d // end : %d\n", start, end);

			for (int loop = start; loop < end; loop++)
			{
				for (int i = start; i < wordcount; i++)
				{//캐럿 뒤의 글자들 앞으로 옮기기
					str[yPos / 20][i] = str[yPos / 20][i + 1];
				}
				str[yPos / 20][wordcount - 1] = '\0';
				if (wordcount >= 0)
					wordcount--;
				if (cword >= 0)
					cword--;
			}

			if (wordcount <= 0)
			{
				cword = 0;
				wordcount = 0;
			}
		}
		else if (wParam == VK_HOME)
		{
			cword = 0;
		}
		else if (wParam == VK_END)
		{
			cword = wordcount;
		}
		else if (wParam == VK_INSERT)
		{
			insert *= -1;
		}
		else if (wParam == VK_NEXT)
		{
			round *= -1;
		}
		else if (wParam == VK_PRIOR)
		{
			blank *= -1;
		}
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT 메시지 발생

		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);


		if (password == 1)
		{
			for (int i = 0; i <= linecount; i++)
			{
				if (i >= MAXLINE)
					break;
				TextOut(hdc, 0, i * 20, L"*****************************************************************************************************************************************************************", lstrlen(str[i]));//출력
			}
		}
		else
		{
			//시작시 (, \0만날 시 )
			//공백 발견시 bool값으로 true면) false면 (
			//프린트에서만
			if (round == 1)
			{
				int rj = 0;
				int tempCword = 0;
				//괄호넣기
				for (int i = 0; i <= linecount; i++)
				{
					tempCword = 0;
					roundstr[i][rj++] = '(';
					for (int j = 0; 0 < MAXWORD; j++)
					{
						if (str[i][j] == '\0')
							break;

						if (str[i][0] == ' ' && j == 0)
						{
							while (true)
							{
								if (str[i][j] != ' ')
									break;
								j++;
							}
						}

						if (str[i][j] != ' ')
						{
							roundstr[i][rj++] = str[i][j];
							tempCword++;
						}
						else
						{
							roundstr[i][rj++] = ')';
							roundstr[i][rj++] = '(';
							tempCword++;
							tempCword++;
							while (str[i][j] == ' ')
							{
								j++;
								tempCword++;
							}
							j--;
							tempCword--;
						}

					}
					roundstr[i][rj] = ')';
					tempCword++;
					rj = 0;
				}

				for (int i = 0; i <= linecount; i++)
				{
					if (i >= MAXLINE)
						break;
					TextOut(hdc, 0, i * 20, roundstr[i], lstrlen(roundstr[i]));//출력		
				}
				GetTextExtentPoint32(hdc, roundstr[yPos / 20], tempCword, &size);
				SetCaretPos(size.cx, yPos); //--- 캐럿 위치하기
				EndPaint(hwnd, &ps);
				break;
			}
			if (blank == 1)
			{
				int blankCword = cword;
				;
				int bj = 0;
				for (int i = 0; i <= linecount; i++)
				{
					for (int j = 0; j < MAXWORD; j++)
					{
						if (str[i][j] == ' ')
						{
							if (i == yPos / 20)
								blankCword--;
						}
						else
						{
							blankstr[i][bj++] = str[i][j];

						}
					}
					bj = 0;
				}
				for (int i = 0; i <= linecount; i++)
				{
					if (i >= MAXLINE)
						break;
					TextOut(hdc, 0, i * 20, blankstr[i], lstrlen(blankstr[i]));//출력		
				}

				GetTextExtentPoint32(hdc, blankstr[yPos / 20], blankCword, &size);
				SetCaretPos(size.cx, yPos); //--- 캐럿 위치하기
				EndPaint(hwnd, &ps);
				break;
			}

			for (int i = 0; i <= linecount; i++)
			{
				if (i >= MAXLINE)
					break;
				TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//출력
			}
		}
		GetTextExtentPoint32(hdc, str[yPos / 20], cword, &size); //--- 문자열 길이 알아내기
		SetCaretPos(size.cx, yPos); //--- 캐럿 위치하기
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwnd); //--- 캐럿 숨기기
		DestroyCaret(); //--- 캐럿 삭제하기
		PostQuitMessage(0);
		break;
	}
}

