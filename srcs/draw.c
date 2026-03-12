#include "../include/libs.h"

void    draw_crosshair(HWND layered_window)
{
    HDC         hdc;
    HPEN        redpen;
    HGDIOBJ     oldpen;
    RECT        rect;
    int         center_x;
    int         center_y;

    // Get context
    hdc = GetDC(layered_window);

    // Get size and set center position
    GetClientRect(layered_window, &rect);
    center_x = (rect.right - rect.left) / 2;
    center_y = (rect.bottom - rect.top) / 2;

    // Clean layered window with magenta brush
    HBRUSH hTransBrush = CreateSolidBrush(RGB(255, 0, 255));
    FillRect(hdc, &rect, hTransBrush);
    DeleteObject(hTransBrush);

    // Create and select tools
    redpen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    oldpen = SelectObject(hdc, redpen);

    // Draw line top->botton
    MoveToEx(hdc, center_x - 20, center_y, NULL);
    LineTo(hdc, center_x + 20, center_y);
    // Draw line left->right
    MoveToEx(hdc, center_x, center_y - 20, NULL);
    LineTo(hdc, center_x, center_y + 20);

    // Free all
    SelectObject(hdc, oldpen);
    DeleteObject(redpen);
    ReleaseDC(layered_window, hdc);
}