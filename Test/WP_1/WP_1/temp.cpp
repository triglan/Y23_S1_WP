/*
TextOut(hdc, 0, 0, L"Hello World", strlen("Hello World"));//방법1
wsprintf(lpOut, L”% d*% d = % d”, x, y, x* y);//방법2
TextOut(hdc, x, y, lpOut, lstrlen(lpOut));

rect1.left = 0;
rect1.top = 0;
rect1.right = 260;
rect1.bottom = 290;
SetBkColor(hdc, RGB(br1, bg1, bb1));
SetTextColor(hdc, RGB(r1, g1, b1));
wsprintf(lpOut, L"abcdefghijklmnopqrstuvwxyzsl;gjreghioilajsdajsufhoefhweioufbhoabcdefghij");
DrawText(hdc, lpOut, lstrlen(lpOut), &rect1, DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=

BOOL OffsetRect (LPRECT lprc, int dx, int dy);
– 주어진 Rect를 dx, dy만큼 이동한다.
BOOL InflateRect (LPRECT lprc, int dx, int dy);
– 주어진 Rect를 dx, dy만큼 늘이거나 줄인다.
BOOL IntersectRect (LPRECT lprcDest, CONST RECT *lprcSrc1, CONST RECT lprcSrc2);
– 두 RECT (lprcSrc1, lprcSrc2)가 교차되었는지 검사한다.
– lprcDest: 교차된 RECT 부분의 좌표값이 저장된다.
BOOL UnionRect (LPRECT lprcDest, CONST RECT *lprcSrc1, CONST RECT *lprcSrc2)
– 두 RECT (lprcSrc1, lprcSrc2) 를 union 시킨다.
– lprcDest: 두 사각형을 합한 사각형의 좌표값이 저장된다.
BOOL PtInRect (CONST RECT *lprc, POINT pt);
– 특정 좌표 pt가 lprc 영역 안에 있는지 검사한다.

*/