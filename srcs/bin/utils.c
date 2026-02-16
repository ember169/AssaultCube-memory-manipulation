#include "../include/libs.h"

void    offset_scan(t_main *main)
{
    int current_value = 100; 
    int read_value = 0;

    printf("[ ] Scanning offsets...\n");
    for (uint32_t offset = 0; offset < 0x400; offset += 4) 
    {
        ReadProcessMemory(main->process.hprocess, (LPCVOID)(main->player.base_addr + offset), &read_value, 4, NULL);
        
        if (read_value == current_value) {
            printf("    > Hit found : 0x%X (Valeur: %d)\n", offset, read_value);
        }
    }
}

void set_cursor_position(int x, int y) {
    // \033[%d;%dH place le curseur à la ligne Y et colonne X
    // On ajoute 1 car les terminaux commencent à 1,1
    printf("\033[%d;%dH", y + 1, x + 1);
}

void    refresh_debug_ui(t_main *main)
{
    int i;

    set_cursor_position(0, UI_START_LINE);
    printf("=== ASSAULTCUBE DEBUG ESP ===\n");
    printf("Players: %d | Base: 0x%X\n", main->ent.player_count, main->process.base_addr);
    printf("------------------------------------------\n");
    // Local player
    printf("[Local]: X:%.2f  Y:%.2f  Z:%.2f    \n", 
            main->player.x, main->player.y, main->player.z);
    printf("------------------------------------------\n");
    // Other players
    i = 0;
    while (i < main->ent.player_count)
    {
        // ProcessMemoryRead();
        printf("[Bot %02d]: 0x%08X | X:%7.2f Y:%7.2f Z:%7.2f    \n", 
                i, 
                main->ent.bots[i].base_addr, 
                main->ent.bots[i].x, 
                main->ent.bots[i].y, 
                main->ent.bots[i].z);
        i++;
    }
}