#include "../include/libs.h"

/*****
***        Mandatory message handler function for Windows32 API CreateWindowExA
 *****/
LRESULT CALLBACK    window_message_management(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:

            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

/*****
***        Initializes the layered window and required structures / classes
 *****/
int init_overlay(HWND *layered_window, HWND h_game_window)
{
    WNDCLASSEXA blueprint = {0};
    RECT rect;

    // --- Class init (window Blueprint) ---
    blueprint.cbSize = sizeof(WNDCLASSEXA);
    blueprint.style = CS_HREDRAW | CS_VREDRAW;
    blueprint.lpfnWndProc = window_message_management;
    blueprint.hInstance = GetModuleHandle(NULL);
    blueprint.lpszClassName = "OverlayClass";
    blueprint.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    if (!RegisterClassExA(&blueprint) && GetLastError() != 1410)
    {
        DWORD   err = GetLastError();
        if (err != ERROR_CLASS_ALREADY_EXISTS)
        {
            LPSTR buf = GetLastErrorAsString();
            printf("[!] ERROR: %s", buf);
            LocalFree(buf);
            return (0);
        }
    }

    // --- Game window size calculation ---
    GetWindowRect(h_game_window, &rect);

    // --- Window creation ---
    *layered_window = CreateWindowExA(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
        "OverlayClass",
        "Overlay",
        WS_POPUP | WS_VISIBLE,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL, NULL, 
        blueprint.hInstance, 
        NULL);

    if (!*layered_window)
    {
        LPSTR buf;
        buf = GetLastErrorAsString();
        printf("[!] ERROR: %s", buf);
        LocalFree(buf);
        return (0);
    }

    // --- Transparency (magenta = invisible) ---
    SetLayeredWindowAttributes(*layered_window, RGB(255, 0, 255), 0, LWA_COLORKEY);

    return (1);
}