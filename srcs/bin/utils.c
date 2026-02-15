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
