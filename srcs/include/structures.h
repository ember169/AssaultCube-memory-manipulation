#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct  s_process
{
    HWND        hwindow;
    DWORD       pid;
    HANDLE      hprocess;
    uintptr_t   base_addr;
}   t_process;

typedef struct  s_player
{
    uintptr_t    base_addr;
    uintptr_t    health_addr;
    uintptr_t    ammo_addr;
}   t_player;

typedef struct  s_main
{
    t_process   process;
    t_player    player;
}   t_main;

#endif