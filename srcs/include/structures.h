#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_config
{
    BOOL    infinite_ammo;
    BOOL    god_mod;
    BOOL    esp;
}   t_config;

typedef struct  s_process
{
    HWND        hwindow;
    DWORD       pid;
    HANDLE      hprocess;
    uintptr_t   base_addr;
}   t_process;

typedef struct t_bot
{
    uintptr_t   base_addr;
    float       x;
    float       y;
    float       z;
    int         health;
}   t_bot;

typedef struct s_entity
{
    uintptr_t   list_ptr;
    uintptr_t   count_addr;
    int         player_count;
    t_bot       *bots;
}   t_entity;


typedef struct  s_player
{
    uintptr_t    base_addr;
    uintptr_t    health_addr;
    uintptr_t    ammo_addr;
    float        x;
    float        y;
    float        z;
}   t_player;

typedef struct  s_main
{
    t_process   process;
    t_player    player;
    t_config    config;
    t_entity    ent;
}   t_main;

#endif