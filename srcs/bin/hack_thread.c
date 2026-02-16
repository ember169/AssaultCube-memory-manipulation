#include "../include/libs.h"

static void get_bot_coords(t_main *main, int i)
{
    SIZE_T      lp_byte_read;

    ReadProcessMemory(main->process.hprocess, (LPCVOID)(main->ent.list_ptr + (i * 4)),\
     &main->ent.bots[i].base_addr, 4, &lp_byte_read);
    if (main->ent.bots[i].base_addr != 0)
    {
        // Offsets: X = 0x34 | Y = 0x38 | Z = 0x3C
        ReadProcessMemory(main->process.hprocess, (LPCVOID)(main->ent.bots[i].base_addr + 0x4),\
        &main->ent.bots[i].x, 4, &lp_byte_read);
        ReadProcessMemory(main->process.hprocess, (LPCVOID)(main->ent.bots[i].base_addr + 0x8),\
        &main->ent.bots[i].y, 4, &lp_byte_read);
        ReadProcessMemory(main->process.hprocess, (LPCVOID)(main->ent.bots[i].base_addr + 0xC),\
        &main->ent.bots[i].z, 4, &lp_byte_read);
    }
}

unsigned int    __stdcall hack_thread(void *arg)
{
    t_main  *main;
    int     val;
    int     i;

    main =  (t_main *)arg;
    while (1)
    {
        if (main->config.infinite_ammo && main->player.ammo_addr != 0)
        {
            val = 999;
            WriteProcessMemory(main->process.hprocess, (LPVOID)main->player.ammo_addr,\
             &val, sizeof(int), NULL);
        }
        if (main->config.god_mod && main->player.health_addr != 0)
        {
            val = 999;
            WriteProcessMemory(main->process.hprocess, (LPVOID)main->player.health_addr,\
             &val, sizeof(int), NULL);
        }
        if (main->config.esp)
        {
            i = 0;
            while(i < main->ent.player_count) 
            {
                get_bot_coords(main, i);
                i++;
            }
            refresh_debug_ui(main);
        }
        sleep(10);
    }
}