#include "../include/libs.h"

int main(void)
{
    t_main  main;

    gather_addresses(&main, "AssaultCube");
    _beginthreadex(NULL, 0, hack_thread, &main, 0, NULL);
    printf("[x] Hack thread started...\n------\n");
    while (1)
    {
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            main.config.infinite_ammo = !main.config.infinite_ammo;
            printf("[F1] Infinite ammo: %s\n", main.config.infinite_ammo ? "ON" : "OFF");
        }
        // if (GetAsyncKeyState(VK_F2) & 1)
        // {
        //     main.config.god_mod = !main.config.god_mod;
        //     printf("[F2] God mod: %s\n", main.config.god_mod ? "ON" : "OFF");
        // }
        if (GetAsyncKeyState(VK_F3) & 1)
        {
            main.config.esp = !main.config.esp;
            printf("[F3] ESP: %s\n", main.config.esp ? "ON" : "OFF");
        }
        Sleep(10);
    }
    terminate(&main);
    return (0);
}

