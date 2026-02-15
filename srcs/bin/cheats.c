#include "../include/libs.h"

void    infinite_ammo(t_main *main)
{
    int buf;
    int target;

    target = 20;
    while (1)
    {
        ReadProcessMemory(main->process.hprocess, (LPCVOID)main->player.ammo_addr, &buf, 4, NULL);
        if (buf < 20)
            WriteProcessMemory(main->process.hprocess, (LPVOID)main->player.ammo_addr, &target, sizeof(int), NULL);
        sleep(2);
    }
}