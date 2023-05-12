#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <stdlib.h>
#include "resource.h"

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LPCTSTR IpszWindowName = L"window programing 1";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR LpszCmdParam, int nCmdShow) {
	srand(time(NULL));
	HWND hWnd;
	HBITMAP hBitmap;
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);



	hWnd = CreateWindow(IpszClass, IpszWindowName, WS_OVERLAPPEDWINDOW, 400, 0, 800, 800, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

typedef struct Picture {
	int x, y;
	int Fx, Fy;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;
	HDC hDC, mDC, kDC;
	HBITMAP hBitmap, kBitmap;
	static RECT rt;
	static Picture Picturev[5];
	static Picture Pictureh[5];
	static Picture Picture[25];
	static int mx, my;
	static int Fx, Fy;
	static int Mousex, Mousey, Afterx, Aftery;
	static int x, y, movei;
	static int Mod, Slash, PSlash, Divide, oldDivide;
	static char VK;
	static BOOL Start, FullPicture, Reverse, RClick, Move, Clear;
	static TCHAR msg[5];

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, 1, 5, NULL);
		Move = FALSE; //블럭 움직임
		Start = FALSE; //시작여부
		FullPicture = FALSE; //전체그림
		Reverse = FALSE; //반전
		RClick = FALSE; //오른클릭
		Mod = 1; //그림 종류
		mx = 800; //그림크기x
		my = 800; //그림크기y
		Slash = 3; //나누는 개수
		PSlash = 8; //그림개수
		Fx = 800 / Slash, Fy = 800 / Slash; //조각 크기
		for (int i = 0; i < PSlash + 1; i++) {
			Picture[i].x = rand() % Slash * (mx / Slash);
			Picture[i].y = rand() % Slash * (my / Slash);
			Picture[i].Fx = rand() % Slash * Fx;
			Picture[i].Fy = rand() % Slash * Fy;
			for (int j = 0; j < i; j++) {
				if (Picture[i].x == Picture[j].x &&
					Picture[i].y == Picture[j].y) {
					i--;
				}
				else if (Picture[i].Fx == Picture[j].Fx &&
					Picture[i].Fy == Picture[j].Fy) {
					i--;
				}
			}
		}
		for (int i = 0; i < Slash; i++) {
			Picturev[i].x = i * (mx / Slash);
			Picturev[i].y = 0;
			Picturev[i].Fx = i * Fx;
			Picturev[i].Fy = 0;
		}
		for (int i = 0; i < Slash; i++) {
			Pictureh[i].y = i * (my / Slash);
			Pictureh[i].x = 0;
			Pictureh[i].Fy = i * Fy;
			Pictureh[i].Fx = 0;
		}
		break;

	case WM_LBUTTONDOWN:
		Mousex = LOWORD(IParam);
		Mousey = HIWORD(IParam);
		RClick = TRUE;
		if (Divide == 1) {
			for (int i = 0; i < Slash; i++) {
				if (Picturev[i].Fx <= Mousex && Mousex <= Picturev[i].Fx + Fx) {
					x = Picturev[i].Fx; movei = i;
				}
			}
		}
		if (Divide == 2) {
			for (int i = 0; i < Slash; i++) {
				if (Pictureh[i].Fy <= Mousey && Mousey <= Pictureh[i].Fy + Fy) {
					y = Pictureh[i].Fy; movei = i;
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		RClick = FALSE;
		RECT rc, rc1, rc2;
		rc1.left = Picturev[movei].Fx;
		rc1.right = Picturev[movei].Fx + Fx;
		rc1.top = 0;
		rc1.bottom = 10;
		if (Divide == 1) {
			for (int i = 0; i < Slash; i++) {
				rc2.left = Picturev[i].Fx;
				rc2.top = 0;
				rc2.right = Picturev[i].Fx + Fx;
				rc2.bottom = 10;
				if (IntersectRect(&rc, &rc1, &rc2) && movei != i) {
					Picturev[movei].Fx = Picturev[i].Fx;
					Picturev[i].Fx = x;
					break;
				}
			}
		}
		if (Divide == 2) {

			rc1.top = Pictureh[movei].Fy;
			rc1.bottom = Pictureh[movei].Fy + Fy;
			rc1.left = 0;
			rc1.right = 10;
			for (int i = 0; i < Slash; i++) {
				rc2.top = Pictureh[i].Fy;
				rc2.left = 0;
				rc2.bottom = Pictureh[i].Fy + Fy;
				rc2.right = 10;
				if (IntersectRect(&rc, &rc1, &rc2) && movei != i) {
					Pictureh[movei].Fy = Pictureh[i].Fy;
					Pictureh[i].Fy = y;
					break;
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		if (RClick == TRUE) {
			Afterx = LOWORD(IParam);
			Aftery = HIWORD(IParam);
			if (Move == FALSE && Divide == 0) {
				if (abs(Mousex - Afterx) > abs(Mousey - Aftery)) {
					if (Mousex > Afterx) VK = 'L';
					if (Mousex < Afterx) VK = 'R';
				}
				if (abs(Mousex - Afterx) < abs(Mousey - Aftery)) {
					if (Mousey > Aftery) VK = 'U';
					if (Mousey < Aftery) VK = 'D';
				}
			}
			else if (Divide == 1) {
				Picturev[movei].Fx = Afterx - Fx / 2;
			}
			else if (Divide == 2) {
				Pictureh[movei].Fy = Aftery - Fy / 2;
			}
		}
		break;
	case WM_TIMER:
		if (Start == TRUE && Clear == FALSE) {
			if (Move == FALSE) {
				if (VK == 'L') {
					for (int i = 0; i < PSlash; i++) {
						if (Picture[PSlash].Fx == Picture[i].Fx - Fx &&
							Picture[PSlash].Fy == Picture[i].Fy) {
							Move = TRUE;
							x = Picture[i].Fx, y = Picture[i].Fy, movei = i;
						}
					}
				}
				if (VK == 'R') {
					for (int i = 0; i < PSlash; i++) {
						if (Picture[PSlash].Fx == Picture[i].Fx + Fx &&
							Picture[PSlash].Fy == Picture[i].Fy) {
							Move = TRUE;
							x = Picture[i].Fx, y = Picture[i].Fy, movei = i;
						}
					}
				}
				if (VK == 'U') {
					for (int i = 0; i < PSlash; i++) {
						if (Picture[PSlash].Fy == Picture[i].Fy - Fy &&
							Picture[PSlash].Fx == Picture[i].Fx) {
							Move = TRUE;
							x = Picture[i].Fx, y = Picture[i].Fy, movei = i;
						}
					}
				}
				if (VK == 'D') {
					for (int i = 0; i < PSlash; i++) {
						if (Picture[PSlash].Fy == Picture[i].Fy + Fy &&
							Picture[PSlash].Fx == Picture[i].Fx) {
							Move = TRUE;
							x = Picture[i].Fx, y = Picture[i].Fy, movei = i;
						}
					}
				}
			}
			else {
				if (VK == 'L') {
					Picture[movei].Fx -= 5;
					if (Picture[movei].Fx <= Picture[PSlash].Fx) {
						Picture[movei].Fx = Picture[PSlash].Fx;
						Picture[PSlash].Fx = x;
						Mousex = 0;
						Mousey = 0;
						Afterx = 0;
						Aftery = 0;
						VK = 0;
						Move = FALSE;
					}
				}
				if (VK == 'R') {
					Picture[movei].Fx += 5;
					if (Picture[movei].Fx >= Picture[PSlash].Fx) {
						Picture[movei].Fx = Picture[PSlash].Fx;
						Picture[PSlash].Fx = x;
						Mousex = 0;
						Mousey = 0;
						Afterx = 0;
						Aftery = 0;
						VK = 0;
						Move = FALSE;
					}
				}
				if (VK == 'U') {
					Picture[movei].Fy -= 5;
					if (Picture[movei].Fy <= Picture[PSlash].Fy) {
						Picture[movei].Fy = Picture[PSlash].Fy;
						Picture[PSlash].Fy = y;
						Mousex = 0;
						Mousey = 0;
						Afterx = 0;
						Aftery = 0;
						VK = 0;
						Move = FALSE;
					}
				}
				if (VK == 'D') {
					Picture[movei].Fy += 5;
					if (Picture[movei].Fy >= Picture[PSlash].Fy) {
						Picture[movei].Fy = Picture[PSlash].Fy;
						Picture[PSlash].Fy = y;
						Mousex = 0;
						Mousey = 0;
						Afterx = 0;
						Aftery = 0;
						VK = 0;
						Move = FALSE;
					}
				}
			}
			int count = 0;
			for (int i = 0; i < PSlash; i++) {
				if (Picture[i].Fx / Fx == Picture[i].x / (mx / Slash) &&
					Picture[i].Fy / Fy == Picture[i].y / (my / Slash)) {
					count++;
				}
			}
			if (count == 8 && Move == FALSE) {
				Clear = TRUE;
				wsprintf(msg, L"Clear");
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_PICTURE_PICTURE_1:
			Mod = 1;
			mx = 800;
			my = 800;
			for (int i = 0; i < PSlash; i++) {
				Picture[i].x = rand() % Slash * (mx / Slash);
				Picture[i].y = rand() % Slash * (my / Slash);
				for (int j = 0; j < i; j++) {
					if (Picture[i].x == Picture[j].x &&
						Picture[i].y == Picture[j].y) {
						i--;
					}
				}
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_PICTURE_PICTURE_2:
			Mod = 2;
			mx = 800;
			my = 800;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_DEVIDEPICTURE_PICTURE_3:
			Slash = 3;
			PSlash = 8;
			Fx = 1200 / Slash, Fy = 700 / Slash;
			for (int i = 0; i < PSlash + 1; i++) {
				Picture[i].x = rand() % Slash * (mx / Slash);
				Picture[i].y = rand() % Slash * (my / Slash);
				Picture[i].Fx = rand() % Slash * Fx;
				Picture[i].Fy = rand() % Slash * Fy;
				for (int j = 0; j < i; j++) {
					if (Picture[i].x == Picture[j].x &&
						Picture[i].y == Picture[j].y) {
						i--;
					}
					else if (Picture[i].Fx == Picture[j].Fx &&
						Picture[i].Fy == Picture[j].Fy) {
						i--;
					}
				}
			}
			for (int i = 0; i < Slash; i++) {
				Picturev[i].x = i * (mx / Slash);
				Picturev[i].y = 0;
				Picturev[i].Fx = i * Fx;
				Picturev[i].Fy = 0;
			}
			for (int i = 0; i < Slash; i++) {
				Pictureh[i].y = i * (my / Slash);
				Pictureh[i].x = 0;
				Pictureh[i].Fy = i * Fy;
				Pictureh[i].Fx = 0;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_DEVIDEPICTURE_PICTURE_4:
			Slash = 4;
			PSlash = 15;
			Fx = 800 / Slash, Fy = 800 / Slash;
			for (int i = 0; i < PSlash + 1; i++) {
				Picture[i].x = rand() % Slash * (mx / Slash);
				Picture[i].y = rand() % Slash * (my / Slash);
				Picture[i].Fx = rand() % Slash * Fx;
				Picture[i].Fy = rand() % Slash * Fy;
				for (int j = 0; j < i; j++) {
					if (Picture[i].x == Picture[j].x &&
						Picture[i].y == Picture[j].y) {
						i--;
					}
					else if (Picture[i].Fx == Picture[j].Fx &&
						Picture[i].Fy == Picture[j].Fy) {
						i--;
					}
				}
			}
			for (int i = 0; i < Slash; i++) {
				Picturev[i].x = i * (mx / Slash);
				Picturev[i].y = 0;
				Picturev[i].Fx = i * Fx;
				Picturev[i].Fy = 0;
			}
			for (int i = 0; i < Slash; i++) {
				Pictureh[i].y = i * (my / Slash);
				Pictureh[i].x = 0;
				Pictureh[i].Fy = i * Fy;
				Pictureh[i].Fx = 0;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_DEVIDEPICTURE_PICTURE_5:
			Slash = 5;
			PSlash = 24;
			Fx = 800 / Slash, Fy = 800 / Slash;
			for (int i = 0; i < PSlash + 1; i++) {
				Picture[i].x = rand() % Slash * (mx / Slash);
				Picture[i].y = rand() % Slash * (my / Slash);
				Picture[i].Fx = rand() % Slash * Fx;
				Picture[i].Fy = rand() % Slash * Fy;
				for (int j = 0; j < i; j++) {
					if (Picture[i].x == Picture[j].x &&
						Picture[i].y == Picture[j].y) {
						i--;
					}
					else if (Picture[i].Fx == Picture[j].Fx &&
						Picture[i].Fy == Picture[j].Fy) {
						i--;
					}
				}
			}
			for (int i = 0; i < Slash; i++) {
				Picturev[i].x = i * (mx / Slash);
				Picturev[i].y = 0;
				Picturev[i].Fx = i * Fx;
				Picturev[i].Fy = 0;
			}
			for (int i = 0; i < Slash; i++) {
				Pictureh[i].y = i * (my / Slash);
				Pictureh[i].x = 0;
				Pictureh[i].Fy = i * Fy;
				Pictureh[i].Fx = 0;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_GAME_GAMESTART:
			Start = TRUE;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_GAME_SHOW:
			if (FullPicture == FALSE) FullPicture = TRUE;
			else if (FullPicture == TRUE) FullPicture = FALSE;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_GAME_REVERSE:
			if (Reverse == FALSE) Reverse = TRUE;
			else if (Reverse == TRUE) Reverse = FALSE;
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_GAME_Quit:
			PostQuitMessage(0);
			KillTimer(hWnd, 1);
			return 0;
			break;
		}
		break;
	case WM_CHAR:
		if (wParam == 'v') {
			if (Divide != 1) {
				Divide = 1;
			}
			else if (Divide == 1) {
				Divide = 0;
			}
		}
		if (wParam == 'h') {
			if (Divide != 2) {
				Divide = 2;
			}
			else if (Divide == 2) {
				Divide = 0;
			}
		}
		if (wParam == 's') {
			Start = TRUE;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		if (wParam == 'f') {
			if (FullPicture == FALSE) FullPicture = TRUE;
			else if (FullPicture == TRUE) FullPicture = FALSE;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		if (wParam == 'q') {
			PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &rt);
		hDC = BeginPaint(hWnd, &ps);
		kDC = CreateCompatibleDC(hDC);
		kBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
		SelectObject(kDC, kBitmap);
		hBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		mDC = CreateCompatibleDC(kDC);
		SelectObject(mDC, hBitmap);
		if (Mod == 2) {
			DeleteDC(mDC);
			DeleteObject(hBitmap);
			hBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
			mDC = CreateCompatibleDC(kDC);
			SelectObject(mDC, hBitmap);
		}

		//시작 전
		if (Start == FALSE) {
			if (Reverse == TRUE) {
				StretchBlt(kDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, Fx * Slash, Fy * Slash, NOTSRCCOPY);
			}
			else {
				StretchBlt(kDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, Fx * Slash, Fy * Slash, SRCCOPY);
			}
		}

		// 시작
		else {
			if (Reverse == TRUE) {
				if (Divide == 1) {
					for (int i = 0; i < Slash; i++) {
						StretchBlt(kDC, Picturev[i].Fx, 0, Fx, rt.bottom, mDC, Picturev[i].x, Picturev[i].y, mx / Slash, my, NOTSRCCOPY);
					}
					StretchBlt(kDC, Picturev[movei].Fx, 0, Fx, rt.bottom, mDC, Picturev[movei].x, Picturev[movei].y, mx / Slash, my, NOTSRCCOPY);
				}
				else if (Divide == 2) {
					for (int i = 0; i < Slash; i++) {
						StretchBlt(kDC, 0, Pictureh[i].Fy, rt.right, Fy, mDC, Pictureh[i].x, Pictureh[i].y, mx, my / Slash, NOTSRCCOPY);
					}
					StretchBlt(kDC, 0, Pictureh[movei].Fy, rt.right, Fy, mDC, Pictureh[movei].x, Pictureh[movei].y, mx, my / Slash, NOTSRCCOPY);
				}
				else if (FullPicture == TRUE) {
					StretchBlt(kDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, Fx * Slash, Fy * Slash, NOTSRCCOPY);
				}
				else {
					for (int i = 0; i < PSlash; i++) {
						StretchBlt(kDC, Picture[i].Fx, Picture[i].Fy, Fx, Fy, mDC, Picture[i].x, Picture[i].y, mx / Slash, my / Slash, NOTSRCCOPY);
					}
				}
			}
			else {
				if (Divide == 1) {
					for (int i = 0; i < Slash; i++) {
						StretchBlt(kDC, Picturev[i].Fx, 0, Fx, rt.bottom, mDC, Picturev[i].x, Picturev[i].y, mx / Slash, my, SRCCOPY);
					}
					StretchBlt(kDC, Picturev[movei].Fx, 0, Fx, rt.bottom, mDC, Picturev[movei].x, Picturev[movei].y, mx / Slash, my, SRCCOPY);
				}
				else if (Divide == 2) {
					for (int i = 0; i < Slash; i++) {
						StretchBlt(kDC, 0, Pictureh[i].Fy, rt.right, Fy, mDC, Pictureh[i].x, Pictureh[i].y, mx, my / Slash, SRCCOPY);
					}
					StretchBlt(kDC, 0, Pictureh[movei].Fy, rt.right, Fy, mDC, Pictureh[movei].x, Pictureh[movei].y, mx, my / Slash, SRCCOPY);
				}
				else if (FullPicture == TRUE) {
					StretchBlt(kDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, Fx * Slash, Fy * Slash, SRCCOPY);
				}
				else {
					for (int i = 0; i < PSlash; i++) {
						StretchBlt(kDC, Picture[i].Fx, Picture[i].Fy, Fx, Fy, mDC, Picture[i].x, Picture[i].y, mx / Slash, my / Slash, SRCCOPY);
					}
				}
			}
		}

		if (Clear == TRUE) {
			TextOut(kDC, 500, 500, msg, 5);
		}


		BitBlt(hDC, 0, 0, rt.right, rt.bottom, kDC, 0, 0, SRCCOPY);
		DeleteDC(kDC); //--- 생성한 메모리 DC 삭제: 계속 사용할 경우 전역변수 또는 정적 변수로 선언해도 무방함.
		DeleteObject(kBitmap);
		DeleteDC(mDC);
		DeleteObject(hBitmap);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, IParam));
}