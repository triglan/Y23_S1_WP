#include <windows.h> //--- ������ ��� ����
#include <tchar.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
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
float Length(int x1, int y1, int x2, int y2) {
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
BOOL incircle(int x1, int y1, int x2, int y2) {
	if (Length(x1, y1, x2, y2) <= 10) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	//���³�Ÿ���� ����
	static int s = 0;//1���� 0������ 2�Ʒ� 3��
	static int t = 0;
	static int k = 1;
	static int mov = 0;//1���� 
	static int stop = 0;
	static int speed = 500;
	static int j = 0;
	static int num = 0;

	static int hx = 0, hy = 0;
	static int hx1 = 20, hy1 = 20;
	static int oldx[20];//, oldy = 0, oldx1 = 0, oldy1 = 0;
	static int oldx1[20];
	static int oldy[20];
	static int oldy1[20];
	POINT oldpt[20];
	for (int i = 0; i < 20; i++) {
		oldpt[i].x = (oldx[i] + oldx1[i]) / 2;
		oldpt[i].y = (oldy[i] + oldy1[i]) / 2;//= {(oldx[0] + oldx1[0]) / 2,(oldy[0] + oldy1[0]) / 2};
	}
	static RECT rect[20];
	static int rcount = 0;
	HBRUSH rbrush = CreateSolidBrush(RGB(255, 0, 0));
	POINT pt = { (hx + hx1) / 2,(hy + hy1) / 2 };
	RECT hrect = { hx,hy,hx1,hy1 };
	static int mx = 0, my = 0;//RGB(234, 23, 134)
	static int hcol1 = 234;
	static int hcol2 = 23;
	static int hcol3 = 123;
	static int col1[20];
	static int col2[20];
	static int col3[20];
	static int oldcol1[20];
	static int oldcol2[20];
	static int oldcol3[20];
	static RECT rectj[20];
	static HBRUSH hbrj[20]; //= CreateSolidBrush(RGB(255, 0, 0));


	static int one1 = 0;
	HBRUSH hBrush, oldBrush;

	srand((unsigned)time(NULL));
	if (one1 == 0) {
		for (int i = 0; i < 20; i++) {
			oldx[i] = 0;
			oldx1[i] = 0;
			oldy[i] = 0;
			oldy1[i] = 0;
			col1[i] = rand() % 256;
			col2[i] = rand() % 256;
			col2[i] = rand() % 256;
			rectj[i].left = 5 + 20 * (rand() % 40), rectj[i].top = 5 + 20 * (rand() % 40);//��ȣ �־����
			rectj[i].right = rectj[i].left + 10, rectj[i].bottom = rectj[i].top + 10;
		}
		one1 = 1;
	}
	for (int i = 0; i < 20; i++) {
		hbrj[i] = CreateSolidBrush(RGB(col1[i], col2[i], col3[i]));
	}

	//--- �޽��� ó���ϱ�
	switch (uMsg) {
	case WM_CREATE:
		SetTimer(hWnd, 1, speed, NULL);//500
		SetTimer(hWnd, 2, 1000, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);//PtInRect(&rectj[i],pt)!=TRUE

		for (int i = 0; i < 20; i++) {
			if (PtInRect(&rectj[i], pt) && !(col1[i] == 255 && col3[i] == 255 && col2[i] == 255)) {
				oldcol1[num] = col1[i];
				oldcol2[num] = col2[i];
				oldcol3[num] = col3[i];
				col1[i] = 255;
				col2[i] = 255;
				col3[i] = 255;
				num++;
			}
			FillRect(hdc, &rectj[i], hbrj[i]);

		}
		for (int i = 0; i < rcount; i++) {
			FillRect(hdc, &rect[i], rbrush);
		}
		for (int j = 0; j < num; j++) {
			if (j == 0) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);
			}
			else if (j == 1) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);

			}
			else if (j == 2) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);
			}
			else if (j == 3) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);

			}
			else if (j == 4) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);
			}
			else if (j == 5) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);
			}
			else if (j == 6) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);

			}
			else if (j == 7) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);
			}
			else if (j == 8) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);
			}
			else if (j == 9) {
				hBrush = CreateSolidBrush(RGB(oldcol1[j], oldcol2[j], oldcol3[j]));
				oldBrush = SelectObject(hdc, hBrush);

			}
			else {
				break;
			}
			Ellipse(hdc, oldx[j], oldy[j], oldx1[j], oldy1[j]);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);

		}


		for (int i = 0; i < 41; i++) {
			MoveToEx(hdc, 0, 20 * i, NULL);
			LineTo(hdc, 800, 20 * i);
		}
		for (int i = 0; i < 41; i++) {
			MoveToEx(hdc, 20 * i, 0, NULL);
			LineTo(hdc, 20 * i, 800);
		}
		hBrush = CreateSolidBrush(RGB(hcol1, hcol2, hcol3));
		oldBrush = SelectObject(hdc, hBrush);
		Ellipse(hdc, hx, hy, hx1, hy1);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);

		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			printf("Ÿ�̸� ������ ");
			if (mov == 0) {
				if (s == 1) {// 1���� 0������ 2�Ʒ� 3��
					if (stop == 0) {//����ϱ�!!!! �ھ������ �־�� �ϴµ� �׳� �־��ֱ⸸ �ϸ� ��
						for (int i = 1; i < 10; i++) {
							oldx[10 - i] = oldx[9 - i];
							oldx1[10 - i] = oldx1[9 - i];
							oldy[10 - i] = oldy[9 - i];
							oldy1[10 - i] = oldy1[9 - i];

						}

						oldx[0] = hx;
						oldx1[0] = hx1;
						oldy[0] = hy;
						oldy1[0] = hy1;

					}
					if (j == 1) {
						hx -= 20;
						hx1 -= 20;
						hy -= 20;
						hy1 -= 20;
						j = 2;
						//InvalidateRgn(hWnd, NULL, TRUE);
						//break;
					}
					else if (j == 2) {
						hx -= 20;
						hx1 -= 20;
						hy += 20;
						hy1 += 20;
						j = 0;
						//InvalidateRgn(hWnd, NULL, TRUE);
						//break;
					}

					hx -= 20;
					hx1 -= 20;
					pt.x -= 20;

					for (int i = 0; i < num; i++) {
						if (PtInRect(&hrect, oldpt[i])) {
							stop = 0;
						}
					}
					for (int i = 0; i < rcount; i++) {
						if (PtInRect(&rect[i], pt)) {
							hx += 20;
							hx1 += 20;
							s = 3;
						}
					}
					if (t <= 10) {
						t++;
					}
					if (hx == -20) {
						hy += 20;
						hx += 20;
						hy1 += 20;
						hx1 += 20;
						if (hy == 800) {
							hy -= 20;
							hy1 -= 20;
							//break;
						}
						s = 0;
					}

				}
				else if (s == 0) {
					if (stop == 0) {
						for (int i = 1; i < 10; i++) {
							if (t >= 10 - i) {
								oldx[10 - i] = oldx[9 - i];
								oldx1[10 - i] = oldx1[9 - i];
								oldy[10 - i] = oldy[9 - i];
								oldy1[10 - i] = oldy1[9 - i];
							}
						}
						if (t >= 0) {
							oldx[0] = hx;
							oldx1[0] = hx1;
							oldy[0] = hy;
							oldy1[0] = hy1;
						}
					}
					if (j == 1) {
						hx += 20;
						hx1 += 20;
						hy -= 20;
						hy1 -= 20;
						j = 2;
						//InvalidateRgn(hWnd, NULL, TRUE);
						//break;
					}
					else if (j == 2) {
						hx += 20;
						hx1 += 20;
						hy += 20;
						hy1 += 20;
						j = 0;
						//InvalidateRgn(hWnd, NULL, TRUE);
						//break;
					}
					hx += 20;
					hx1 += 20;
					pt.x += 20;

					for (int i = 0; i < num; i++) {
						if (PtInRect(&hrect, oldpt[i])) {
							stop = 0;
						}
					}
					for (int i = 0; i < rcount; i++) {
						if (PtInRect(&rect[i], pt)) {
							hx -= 20;
							hx1 -= 20;
							s = 2;
							//InvalidateRgn(hWnd, NULL, TRUE);
							//break;
						}
					}
					if (t <= 10) {
						t++;
					}
					if (hx == 800) {
						hy += 20;
						hx -= 20;
						hy1 += 20;
						hx1 -= 20;
						if (hy == 800) {
							hy -= 20;
							hy1 -= 20;
							//break;
						}
						s = 1;
					}
				}//�� �Ʒ� �������
				else if (s == 2) {//�Ʒ�
					if (stop == 0) {
						for (int i = 1; i < 10; i++) {
							if (t >= 10 - i) {
								oldx[10 - i] = oldx[9 - i];
								oldx1[10 - i] = oldx1[9 - i];
								oldy[10 - i] = oldy[9 - i];
								oldy1[10 - i] = oldy1[9 - i];
							}
						}
						if (t >= 0) {
							oldx[0] = hx;
							oldx1[0] = hx1;
							oldy[0] = hy;
							oldy1[0] = hy1;
						}
					}
					if (j == 1) {
						hx -= 20;
						hx1 -= 20;
						hy += 20;
						hy1 += 20;
						j = 2;
						//InvalidateRgn(hWnd, NULL, TRUE);
						//break;
					}
					else if (j == 2) {
						hx += 20;
						hx1 += 20;
						hy += 20;
						hy1 += 20;
						j = 0;
						//InvalidateRgn(hWnd, NULL, TRUE);
						//break;
					}
					hy += 20;
					hy1 += 20;
					pt.y += 20;

					for (int i = 0; i < num; i++) {
						if (PtInRect(&hrect, oldpt[i])) {
							stop = 0;
						}
					}
					for (int i = 0; i < rcount; i++) {
						if (PtInRect(&rect[i], pt)) {
							hy -= 20;
							hy1 -= 20;
							s = 0;
						}
					}
					if (t <= 10) {
						t++;
					}
					if (hy == 800) {
						hx += 20;
						hy -= 20;
						hx1 += 20;
						hy1 -= 20;
						if (hx == 800) {
							hx -= 20;
							hx1 -= 20;
							//break;
						}
						s = 3;
					}
				}
				else if (s == 3) {//��
					if (stop == 0) {
						for (int i = 1; i < 10; i++) {
							if (t >= 10 - i) {
								oldx[10 - i] = oldx[9 - i];
								oldx1[10 - i] = oldx1[9 - i];
								oldy[10 - i] = oldy[9 - i];
								oldy1[10 - i] = oldy1[9 - i];
							}
						}
						if (t >= 10) {
							oldx[0] = hx;
							oldx1[0] = hx1;
							oldy[0] = hy;
							oldy1[0] = hy1;
						}
					}
					if (j == 1) {
						hx += 20;
						hx1 += 20;
						hy -= 20;
						hy1 -= 20;
						j = 2;
						//InvalidateRgn(hWnd, NULL, TRUE);
						//break;
					}
					else if (j == 2) {
						hx -= 20;
						hx1 -= 20;
						hy -= 20;
						hy1 -= 20;
						j = 0;
						//InvalidateRgn(hWnd, NULL, TRUE);
						//break;
					}
					hy -= 20;
					hy1 -= 20;
					pt.y -= 20;

					for (int i = 0; i < num; i++) {
						if (PtInRect(&hrect, oldpt[i])) {
							stop = 0;
						}
					}
					for (int i = 0; i < rcount; i++) {
						if (PtInRect(&rect[i], pt)) {
							hy += 20;
							hy1 += 20;
							s = 1;
						}
					}
					if (t <= 4) {
						t++;
					}
					if (hy == -20) {
						hx += 20;
						hy += 20;
						hx1 += 20;
						hy1 += 20;
						if (hx == 800) {
							hx -= 20;
							hx1 -= 20;
							//break;
						}
						s = 2;
					}
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case 2:
			if (k == 0) {
				hx += 5;
				hx1 -= 5;
				hy += 5;
				hy1 -= 5;
				k = 1;
			}

			//InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == '+') {
			speed = speed - 50;
			KillTimer(hWnd, 1);
			SetTimer(hWnd, 1, speed, NULL);
			printf("speed up");

		}
		else if (wParam == '-') {
			speed = speed + 50;
			KillTimer(hWnd, 1);
			SetTimer(hWnd, 1, speed, NULL);
			printf("speed down");

		}
		else if (wParam == 'q') {
			PostQuitMessage(0);
		}
		else if (wParam == 'j') {
			j = 1;
		}
		else if (wParam == 't') {//RGB(234, 23, 134)
			int tmp1, tmp2, tmp3;
			tmp1 = hcol1;
			hcol1 = oldcol1[0];
			for (int i = 0; i < num - 1; i++) {
				oldcol1[i] = oldcol1[i + 1];
			}
			oldcol1[num - 1] = tmp1;
			tmp2 = hcol2;
			hcol2 = oldcol2[0];
			for (int i = 0; i < num - 1; i++) {
				oldcol2[i] = oldcol2[i + 1];
			}
			oldcol2[num - 1] = tmp2;
			tmp3 = hcol3;
			hcol3 = oldcol3[0];
			for (int i = 0; i < num - 1; i++) {
				oldcol3[i] = oldcol3[i + 1];
			}
			oldcol3[num - 1] = tmp3;

		}
		else if (wParam == 's' || wParam == 'S') {
			if (mov == 0) {
				mov = 1;
				printf("1111");
			}
			else if (mov == 1) {
				mov = 0;
			}
		}
		//InvalidateRgn(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_KEYDOWN:////1���� 0������ 2�Ʒ� 3��
		hdc = GetDC(hWnd);
		if (wParam == VK_UP) {
			s = 3;
		}
		else if (wParam == VK_DOWN) {
			s = 2;
		}
		else if (wParam == VK_LEFT) {
			s = 1;
		}
		else if (wParam == VK_RIGHT) {
			s = 0;
		}
		//InvalidateRgn(hWnd, NULL, TRUE);

		ReleaseDC(hWnd, hdc);
		break;

	case WM_MOUSEMOVE:
		break;

	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (rcount >= 20) {
			break;
		}
		rect[rcount].left = (mx / 20) * 20;
		rect[rcount].right = rect[rcount].left + 20;
		rect[rcount].top = (my / 20) * 20;
		rect[rcount].bottom = rect[rcount].top + 20;
		rcount++;
		//InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);//1���� 0������ 2�Ʒ� 3��
		//for (int i = 0; i < rcount; i++) {
		//	if (incircle((oldx[i] + oldx1[i]) / 2, (oldy[i] + oldy1[i]) / 2, mx, my)) {
		//		stop = 1;
		//		break;
		//	}
		//}
		if (incircle((oldx[0] + oldx1[0]) / 2, (oldy[0] + oldy1[0]) / 2, mx, my)) {
			stop = 1;
		}
		else if (incircle((hx + hx1) / 2, (hy + hy1) / 2, mx, my)) {
			hx -= 5;
			hx1 += 5;
			hy -= 5;
			hy1 += 5;
			k = 0;
		}
		else if (s == 0) {
			if (mx < hx) {
				s = 1;
			}
			if (hx<mx && hy>my) {
				s = 3;
			}
			if (hx < mx && hy < my) {
				s = 2;
			}
		}
		else if (s == 1) {
			if (hx < mx) {
				s = 0;
			}
			if (hx > mx && hy > my) {
				s = 3;
			}
			if (hx > mx && hy < my) {
				s = 2;
			}
		}
		else if (s == 2) {
			if (hy > my) {
				s = 3;
			}
			if (hx < mx && hy < my) {
				s = 0;
			}
			if (hx > mx && hy < my) {
				s = 1;
			}
		}
		else if (s == 3) {
			if (hy < my) {
				s = 2;
			}
			if (hx < mx && hy > my) {
				s = 0;
			}
			if (hx > mx && hy > my) {
				s = 1;
			}
		}
		printf("���� \n");
		//InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //--- ���� �� �޽��� ���� ������ �޽����� OS��
}