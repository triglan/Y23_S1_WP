LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static CImage img, imgSprite[3];
    static int xPos = 0, yPos = 0;
    HBRUSH hBrush, oldBrush;
    HPEN hpen, oldpen;

    static int w, h;
    static RECT rect;
    PAINTSTRUCT ps;
    HDC hdc;
    HDC mdc, MemDCImage;
    static HBITMAP hBitmap;


    static int num = 0;
    //--- �޽��� ó���ϱ�
    switch (uMsg) {
    case WM_CREATE:
        img.Load(L"bitmap1.bmp"); //--- background
        imgSprite[0].Load(L"bitmap3.bmp"); //--- sprite image
        imgSprite[1].Load(L"bitmap6.bmp");
        imgSprite[2].Load(L"bitmap5.bmp");
        GetClientRect(hWnd, &rect);

        SetTimer(hWnd, 1, 500, NULL);

        break;
    case WM_PAINT:

        hdc = BeginPaint(hWnd, &ps);
        hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
        mdc = CreateCompatibleDC(hdc);

        (HBITMAP)SelectObject(mdc, hBitmap);

        w = img.GetWidth();
        h = img.GetHeight();

        img.Draw(mdc, 0, 0, rect.right, rect.bottom, 0, 0, w, h); //--- �޸� DC�� ��� �׸���
        //TransparentBlt(mdc, xPos, yPos, 100, 100, 
        //imgSprite[num].GetDC(), 0, 0, 100, 100, RGB(255, 255, 255));
       
        imgSprite[num].Draw(mdc, xPos, yPos, 100, 100, 0, 0, 100, 100);
        //--- �޸� DC�� ��������Ʈ �׸���

        BitBlt(hdc, 0, 0, rect.right, rect.bottom, mdc, 0, 0, SRCCOPY); //--- �޸� DC�� �׸��� ȭ�� DC�� �����ϱ�
       
        DeleteObject(hBitmap);
        DeleteDC(mdc);
        
        InvalidateRect(hWnd, NULL, false);
        EndPaint(hWnd, &ps);
        break;
    case WM_TIMER:
        switch (wParam) {
        case 1://TransparentBlt(MemDC, 50, 50, 50, 50, MemDCImage, 0, 0, 100, 100, RGB(255, 255, 255));
            num += 1;
            if (num == 2) {
                num = 0;
            }

        }
        InvalidateRect(hWnd, NULL, false);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam); //--- ���� �� �޽��� ���� ������ �޽����� OS��
}