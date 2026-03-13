#include "../include/libs.h"

static void get_bot_coords(t_main *main, int i)
{
    SIZE_T      lp_byte_read;

    ReadProcessMemory(main->process.hprocess, (LPCVOID)(main->ent.list_ptr + (i * 4)),\
     &main->ent.bots[i].base_addr, 4, &lp_byte_read);
    if (main->ent.bots[i].base_addr != 0)
    {
        float pos[3];
        if (ReadProcessMemory(main->process.hprocess, (LPCVOID)(main->ent.bots[i].base_addr + 0x4), &pos, sizeof(pos), NULL))
        {
            main->ent.bots[i].x = pos[0];
            main->ent.bots[i].y = pos[1];
            main->ent.bots[i].z = pos[2];
        }
    }
}

static void get_player_coords(t_main *main)
{
    if (main->player.base_addr != 0)
    {
        float   pos[3];
        if (ReadProcessMemory(main->process.hprocess, (LPCVOID)(main->player.base_addr + 0x4), &pos, sizeof(pos), NULL))
        {
            main->player.x = pos[0];
            main->player.y = pos[1];
            main->player.z = pos[2];
        }
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
            get_player_coords(main);
            while(i < main->ent.player_count) 
            {
                get_bot_coords(main, i);
                i++;
            }
            draw_enemies(main);
            refresh_debug_ui(main);
        }
    }
}