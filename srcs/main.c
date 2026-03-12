#include "../include/libs.h"

int main(void)
{
    t_main  main_data;
    HWND    layered_window = NULL;
    MSG     msg;
    RECT    rect;
    HWND    current_focus = NULL;


    gather_addresses(&main_data, "AssaultCube");
    _beginthreadex(NULL, 0, hack_thread, &main_data, 0, NULL);

    if (!init_overlay(&layered_window, main_data.process.hwindow))
        return (1);

    while (1)
    {
        // --- Win messages loop (mandatory but useless in our case) ---
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        current_focus = GetForegroundWindow();
        if (current_focus == main_data.process.hwindow || current_focus == layered_window)
        {
            // --- Layered position update (if game window moves) ---
            GetWindowRect(main_data.process.hwindow, &rect);
            SetWindowPos(layered_window, HWND_TOPMOST, rect.left, rect.top, 
                        rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
            draw_crosshair(layered_window);

            // --- User inputs ---
            if (GetAsyncKeyState(VK_F1) & 1)
            {
                main_data.config.infinite_ammo = !main_data.config.infinite_ammo;
                printf("[F1] Ammo: %d\n", main_data.config.infinite_ammo);
            }
            if (GetAsyncKeyState(VK_F3) & 1)
            {
                main_data.config.esp = !main_data.config.esp;
                printf("[F3] ESP: %d\n", main_data.config.esp);
            }

        }
        else
            ShowWindow(layered_window, SW_HIDE);

        Sleep(10);
    }
    return (0);
}

