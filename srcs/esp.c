#include "../include/libs.h"

int WorldToScreen(float matrix[16], float pos[3], float screen[2], int width, int height)
{
    // Calcul du W (Profondeur) - On utilise souvent la 4ème ligne pour cet offset
    float w = pos[0] * matrix[3] + pos[1] * matrix[7] + pos[2] * matrix[11] + matrix[15];

    if (w < 0.1f) return 0;

    // Calcul de X et Y 
    // Si la boîte est décalée horizontalement, on vérifie matrix[0, 4, 8, 12]
    float x = pos[0] * matrix[0] + pos[1] * matrix[4] + pos[2] * matrix[8] + matrix[12];
    float y = pos[0] * matrix[1] + pos[1] * matrix[5] + pos[2] * matrix[9] + matrix[13];

    float ndc_x = x / w;
    float ndc_y = y / w;

    // Conversion Pixels
    screen[0] = (width / 2.0f * ndc_x) + (width / 2.0f);
    screen[1] = -(height / 2.0f * ndc_y) + (height / 2.0f);

    return 1;
}

static void clear_overlay(HWND overlay, int w, int h) {
    HDC hdc = GetDC(overlay);
    if (!hdc)
        return ;
    RECT rect = {0, 0, w, h};
    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);
    ReleaseDC(overlay, hdc);
}

static void draw_rectangle(t_main *main, int left, int top, int right, int bottom)
{
    HDC hdc = GetDC(main->overlay);
    if (!hdc) return;

    HPEN linePen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    HGDIOBJ oldPen = SelectObject(hdc, linePen);

    // Haut
    MoveToEx(hdc, left, top, NULL);
    LineTo(hdc, right, top);
    // Bas
    MoveToEx(hdc, left, bottom, NULL);
    LineTo(hdc, right, bottom);
    // Gauche
    MoveToEx(hdc, left, top, NULL);
    LineTo(hdc, left, bottom);
    // Droite
    MoveToEx(hdc, right, top, NULL);
    LineTo(hdc, right, bottom);

    SelectObject(hdc, oldPen);
    DeleteObject(linePen);
    ReleaseDC(main->overlay, hdc);
}

void    draw_enemies(t_main *main_data)
{
    RECT rect;
    float view_matrix[16];

    ReadProcessMemory(main_data->process.hprocess, (LPCVOID)(main_data->process.base_addr + OFF_VIEW_MATRIX), &view_matrix, sizeof(view_matrix), NULL);
    GetClientRect(main_data->process.hwindow, &rect);
    
    int w = rect.right;
    int h = rect.bottom;
    clear_overlay(main_data->overlay, w, h);
    // draw_crosshair(main_data);
    for (int i = 0; i < main_data->ent.player_count; i++)
    {
        // 2. ON DÉFINIT LES DEUX POINTS DANS LE MONDE (3D)
        float bot_feet[3] = { main_data->ent.bots[i].x, 
                            main_data->ent.bots[i].y, 
                            main_data->ent.bots[i].z - 4.2f };

        // On ajoute 4.5f uniquement sur le Z
        float bot_head[3] = { bot_feet[0], bot_feet[1], bot_feet[2] + 4.5f };

        float screen_feet[2], screen_head[2];

        // 3. ON PROJETTE LES DEUX POINTS SUR L'ÉCRAN (2D)
        if (WorldToScreen(view_matrix, bot_feet, screen_feet, w, h) && 
            WorldToScreen(view_matrix, bot_head, screen_head, w, h)) 
        {
            // 4. ON CALCULE LES DIMENSIONS DE LA BOX
            float box_h = screen_feet[1] - screen_head[1]; 
            float box_w = box_h / 2.0f;

            int left   = (int)(screen_feet[0] - (box_w / 2));
            int right  = (int)(screen_feet[0] + (box_w / 2));
            int top    = (int)screen_head[1];
            int bottom = (int)screen_feet[1];

            // 5. ON DESSINE
            draw_rectangle(main_data, left, top, right, bottom);
        }
    }
}
