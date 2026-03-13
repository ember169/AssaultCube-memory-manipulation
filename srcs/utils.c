#include "../include/libs.h"

void    offset_scan(t_main *main)
{
    int current_value = 100; 
    int read_value = 0;

    printf("[ ] Scanning offsets...\n");
    for (uint32_t offset = 0; offset < 0x400; offset += 4) 
    {
        ReadProcessMemory(main->process.hprocess, (LPCVOID)(main->player.base_addr + offset), &read_value, 4, NULL);
        
        if (read_value == current_value)
        {
            printf("    > Hit found : 0x%X (Valeur: %d)\n", offset, read_value);
        }
    }
}

void    set_cursor_position(int x, int y)
{
    // \033[%d;%dH place le curseur à la ligne Y et colonne X
    // On ajoute 1 car les terminaux commencent à 1,1
    printf("\033[%d;%dH", y + 1, x + 1);
}

void    refresh_debug_ui(t_main *main)
{
    // int i;

    set_cursor_position(0, UI_START_LINE);
    printf("=== ASSAULTCUBE DEBUG ESP ===\n");
    printf("\nPlayers: %d | Base: 0x%X\n", main->ent.player_count, main->process.base_addr);
    printf("------------------------------------------\n");
    // Local player
    printf("[Local]: X:%.2f  Y:%.2f  Z:%.2f    \n", 
            main->player.x, main->player.y, main->player.z);
    printf("------------------------------------------\n");
    // Other players
    // i = 0;
    // while (i < main->ent.player_count)
    // {
    //     // ProcessMemoryRead();
    //     printf("[Bot %02d]: 0x%08X | X:%7.2f Y:%7.2f Z:%7.2f    \n", 
    //             i, 
    //             main->ent.bots[i].base_addr, 
    //             main->ent.bots[i].x, 
    //             main->ent.bots[i].y, 
    //             main->ent.bots[i].z);
    //     i++;
    // }
}

char    *GetLastErrorAsString(void)
{
    DWORD   errorMessageID;
    LPSTR   messageBuffer;

    errorMessageID = GetLastError();
    if (!errorMessageID)
        return (NULL);
    messageBuffer = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, 
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        (LPSTR)&messageBuffer, 0, NULL);

    return (messageBuffer);
}

void    draw_crosshair(t_main *main)
{
    HDC     hdc = GetDC(main->overlay);
    RECT    rect;
    HPEN    greenPen;
    HGDIOBJ oldPen;

    if (!hdc)
        return ;
    GetClientRect(main->process.hwindow, &rect);

    greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    oldPen = SelectObject(hdc, greenPen);

    int mid_w = rect.right / 2;
    int mid_h = rect.bottom / 2;
    MoveToEx(hdc, mid_w - 5, mid_h, NULL);
    LineTo(hdc, mid_w + 5, mid_h);
    MoveToEx(hdc, mid_w, mid_h - 5, NULL);
    LineTo(hdc, mid_w, mid_h + 5);

    SelectObject(hdc, oldPen);
    DeleteObject(greenPen);
    ReleaseDC(main->overlay, hdc);
}

