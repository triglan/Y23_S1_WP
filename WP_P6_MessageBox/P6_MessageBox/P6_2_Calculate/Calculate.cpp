#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include "resource.h"
#include<cmath>
#include <sstream> // stringstream을 사용하기 위해 추가
#include <iomanip> // 소수점 자릿수를 조절하기 위해 추가
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlalog_Proc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);//
//HINSTANCE g_hInst;//
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 400, 400, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
int curvenum;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc, mdc;
	HBITMAP hBitmap;
	HBRUSH hbr, oldbr;
	HPEN hPen, oldPen;
	//--- 메시지 처리하기
	switch (uMsg) {
	case WM_CREATE:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)&Dlalog_Proc);
		break;
	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)&Dlalog_Proc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}
BOOL CALLBACK Dlalog_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hbutton;

	TCHAR editText[100] = { '\0' };
	TCHAR teditText[100] = { '\0' };
	int num[100] = { 0 };
	TCHAR cal[100] = { '\0' };
	TCHAR temp[10] = { '\0' };

	int i = 0, c = 0;
	int ten = 10;
	int tempc = 0;
	float result = 0;
	int editTextLength;

	std::stringstream ss;
	std::string resultString;
	TCHAR singleChar[2];
	TCHAR singleint[10];

	switch (iMsg) {
	case WM_INITDIALOG:
		//hbutton = GetDlgItem(hDlg, ID_TEST); //--- ID_TEST 라는 id의 버튼 핸들 가져오기
		//EnableWindow(hbutton, FALSE);
		break;
	case IDOK:
	{
		SetDlgItemText(hDlg, IDC_EDIT1, L"");
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1 :
		{
			_tcscpy_s(temp, _countof(temp), _T("7"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON2 :
		{
			_tcscpy_s(temp, _countof(temp), _T("8"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON3 :
		{
			_tcscpy_s(temp, _countof(temp), _T("9"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON4 :
		{
			_tcscpy_s(temp, _countof(temp), _T("/"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON5 :
		{
			_tcscpy_s(temp, _countof(temp), _T("4"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON6 :
		{
			_tcscpy_s(temp, _countof(temp), _T("5"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON7 :
		{
			_tcscpy_s(temp, _countof(temp), _T("6"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON8 :
		{
			_tcscpy_s(temp, _countof(temp), _T("*"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON9:
		{
			_tcscpy_s(temp, _countof(temp), _T("1"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON10 :
		{
			_tcscpy_s(temp, _countof(temp), _T("2"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON11:
		{
			_tcscpy_s(temp, _countof(temp), _T("3"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON12:
		{
			_tcscpy_s(temp, _countof(temp), _T("-"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON13:
		{
			_tcscpy_s(temp, _countof(temp), _T("0"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON14:// 1/x
		{
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			while (1) {
				if (editText[i] == '\0')
					break;
				if (editText[i] >= '0' && editText[i] <= '9')
					num[c] = (num[c] * 10) + (editText[i] - 48);
				else if (editText[i] == '+' || editText[i] == '-' || editText[i] == '*' || editText[i] == '/') {
					cal[c] = editText[i];
					c++;
				}
				i++;
			}
			result = num[0];
			result = 1 / result;
			ss << std::fixed << std::setprecision(2) << result; // 소수점 둘째 자리까지 출력
			resultString = ss.str();
			SetDlgItemTextA(hDlg, IDC_EDIT1, resultString.c_str());
		}
			break;
		case IDC_BUTTON15:// 10^x
		{
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			while (1) {
				if (editText[i] == '\0')
					break;
				if (editText[i] >= '0' && editText[i] <= '9')
					num[c] = (num[c] * 10) + (editText[i] - 48);
				else if (editText[i] == '+' || editText[i] == '-' || editText[i] == '*' || editText[i] == '/') {
					cal[c] = editText[i];
					c++;
				}
				i++;
			}
			for (int j = 0; j < num[0] - 1; j++)
			{
				ten = ten * 10;
			}
			SetDlgItemInt(hDlg, IDC_EDIT1, ten, TRUE);
		}
			break;
		case IDC_BUTTON16://+
			break;
		case IDC_BUTTON17://순서 바꾸기
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			while (1) {
				if (editText[i] == '\0')
					break;
				if (editText[i] >= '0' && editText[i] <= '9')
					num[c] = (num[c] * 10) + (editText[i] - 48);
				else if (editText[i] == '+' || editText[i] == '-' || editText[i] == '*' || editText[i] == '/') {
					cal[c] = editText[i];
					c++;
				}
				i++;
			}
			for (int j = 0; j <= c / 2; j++)
			{
				temp[0] = num[j];
				num[j] = num[c - j];
				num[c - j] = temp[0];
			}
			for (int j = 0; j <= c; j++)
			{
				_sntprintf_s(singleint, _countof(singleint), _TRUNCATE, _T("%d"), num[j]);
				lstrcat(teditText, singleint);
				singleChar[0] = cal[j];
				singleChar[1] = '\0';
				lstrcat(teditText, singleChar);
			}
			SetDlgItemText(hDlg, IDC_EDIT1, teditText);

			break;
		case IDC_BUTTON18://CE
		{
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			while (1) {
				if (editText[i] == '\0')
					break;
				if (editText[i] == '+' || editText[i] == '-' || editText[i] == '*' || editText[i] == '/') {
					c++;
				}
				i++;
			}
			i = 0;
			while (1) {
				if (editText[i] == '+' || editText[i] == '-' || editText[i] == '*' || editText[i] == '/') {
					tempc++;
				}
				if (tempc < c)
					teditText[i] = editText[i];
				else
					break;
				i++;
			}
			SetDlgItemText(hDlg, IDC_EDIT1, teditText);
		}
			break;
		case IDC_BUTTON19://C
			SetDlgItemText(hDlg, IDC_EDIT1, L"");
			break;
		case IDC_BUTTON20://=
		{
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			while (1) {
				if (editText[i] == '\0')
					break;
				if (editText[i] >= '0' && editText[i] <= '9')
					num[c] = (num[c] * 10) + (editText[i] - 48);
				else if (editText[i] == '+' || editText[i] == '-' || editText[i] == '*' || editText[i] == '/') {
					cal[c] = editText[i];
					c++;
				}
				i++;
			}
			result = num[0];
			for (int j = 0; j < c; j++)
			{
				if (cal[j] == '+') {
					result = result + num[j + 1];
				}
				if (cal[j] == '-') {
					result = result - num[j + 1];
				}
				if (cal[j] == '*') {
					result = result * num[j + 1];
				}
				if (cal[j] == '/') {
					result = result / num[j + 1];
				}
			}
			ss << std::fixed << std::setprecision(2) << result; // 소수점 둘째 자리까지 출력
			resultString = ss.str();
			SetDlgItemTextA(hDlg, IDC_EDIT1, resultString.c_str());
		}
			break;
		case IDC_BUTTON21://ROOT
		{
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			while (1) {
				if (editText[i] == '\0')
					break;
				if (editText[i] >= '0' && editText[i] <= '9')
					num[c] = (num[c] * 10) + (editText[i] - 48);
				else if (editText[i] == '+' || editText[i] == '-' || editText[i] == '*' || editText[i] == '/') {
					cal[c] = editText[i];
					c++;
				}
				i++;
			}
			num[0] = sqrt(num[0]);
			SetDlgItemInt(hDlg, IDC_EDIT1, num[0], TRUE);
		}
			break;
		case IDC_BUTTON22://*10
		{
			_tcscpy_s(temp, _countof(temp), _T("0"));
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			lstrcat(editText, temp);
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON23://backspace
		{
			GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
			while (1) {
				if (editText[i] == '\0')
					break;
				if (editText[i] >= '0' && editText[i] <= '9')
					num[c] = (num[c] * 10) + (editText[i] - 48);
				else if (editText[i] == '+' || editText[i] == '-' || editText[i] == '*' || editText[i] == '/') {
					c++;
				}
				i++;
			}
			result = num[0];
			editTextLength = wcslen(editText);
			if (num[c] < 10) {
				editText[editTextLength - 1] = L'0';
				SetDlgItemText(hDlg, IDC_EDIT1, editText);
				break;
			}
			if (editTextLength > 0) {
				editText[editTextLength - 1] = L'\0';
			}
			SetDlgItemText(hDlg, IDC_EDIT1, editText);
		}
			break;
		case IDC_BUTTON24://종료

			PostQuitMessage(0);
			break;
		}
		InvalidateRect(GetParent(hDlg), NULL, FALSE);
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	}
	return 0;
}