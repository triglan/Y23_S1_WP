  WM_CREATE 윈도우가 생성될 때 발생 WM_RBUTTONDOWN 마우스 오른쪽 버튼을 누르면 발생
WM_NCACTIVATE 윈도우의 비 작업영역의 활성화 또는 비 활성화시
발생(윈도우 타이틀 바 색상 제어) WM_RBUTTONUP 마우스 오른쪽 버튼을 떼면 발생
WM_DESTROY 윈도우가 파괴되기 직전에 발생 WM_MOUSEMOVE 마우스가 움직이고 있으면 발생
WM_PAINT 윈도우가 다시 그려져야 하면 발생 WM_SETCURSOR 마우스의 아이콘을 재설정해야 할 때 발생
WM_LBUTTONDOWN 마우스 왼쪽 버튼을 누르면 발생 WM_TIMER 타이머 설정 시 주기적으로 발생
WM_LBUTTONUP 마우스 왼쪽 버튼을 떼면 발생 WM_COMMAND 메뉴, 버튼, 액셀러레이터 선택 시 발생typedef struct tagMSG {
	HWND hwnd; //--- 윈도우 핸들
	UINT message; //--- 메시지 id
	WPARAM wParam; //--- 메시지 전달 인자 1: 32 (또는 64) 비트 LONG_PTR
	LPARAM lParam; //--- 메시지 전달 인자 2: 32 (또는 64) 비트 UINT_PTR
	DWORD time; //--- 이벤트 발생 시각
	POINT pt; //--- 이벤트 발생 시 커서 위치
} MSG, * PMSG;

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

//윈도우 생성
#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 2";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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

