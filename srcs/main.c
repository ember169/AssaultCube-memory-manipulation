#include "../include/libs.h"

int main(void)
{
    t_main  main_data;
    MSG     msg;
    RECT    rect;
    HWND    current_focus = NULL;


    gather_addresses(&main_data, "AssaultCube");
    _beginthreadex(NULL, 0, hack_thread, &main_data, 0, NULL);

    if (!init_overlay(&main_data.overlay, main_data.process.hwindow))
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
        if (current_focus == main_data.process.hwindow || current_focus == main_data.overlay)
        {
            // --- Overlay position update (if game window moves) ---
            POINT pt = {0, 0};
            ClientToScreen(main_data.process.hwindow, &pt); // Convertit 0,0 (client) en coordécran
            
            GetClientRect(main_data.process.hwindow, &rect); // Récupère la largeur/hauteur réelle du jeu

            SetWindowPos(main_data.overlay, HWND_TOPMOST, 
                        pt.x, pt.y,            // Position exacte de la zone de rendu
                        rect.right, rect.bottom, // Taille exacte de la zone de rendu
                        SWP_SHOWWINDOW);

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
            ShowWindow(main_data.overlay, SW_HIDE);

        Sleep(5);
    }
    return (0);
}

