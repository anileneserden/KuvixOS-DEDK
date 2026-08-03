#include <kernel/drivers/video/de_api.h>

// 10x14 Fare Ok Matrisi
// 0: Saydam, 1: Siyah Kenarlık (0x000000), 2: Beyaz İç Dolgu (0xFFFFFF)
static const int CURSOR_WIDTH = 10;
static const int CURSOR_HEIGHT = 14;

static const uint8_t cursor_map[14][10] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 2, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 2, 2, 1, 0, 0, 0, 0, 0, 0},
    {1, 2, 2, 2, 1, 0, 0, 0, 0, 0},
    {1, 2, 2, 2, 2, 1, 0, 0, 0, 0},
    {1, 2, 2, 2, 2, 2, 1, 0, 0, 0},
    {1, 2, 2, 2, 2, 2, 2, 1, 0, 0},
    {1, 2, 2, 2, 2, 1, 1, 1, 1, 0},
    {1, 2, 2, 1, 2, 1, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 2, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 2, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static void draw_cursor(DE_API* api, int x, int y) {
    if (!api || !api->put_pixel) return;

    for (int cy = 0; cy < CURSOR_HEIGHT; cy++) {
        for (int cx = 0; cx < CURSOR_WIDTH; cx++) {
            uint8_t pixel_type = cursor_map[cy][cx];
            if (pixel_type == 0) continue;

            int target_x = x + cx;
            int target_y = y + cy;

            if (target_x >= api->screen_width || target_y >= api->screen_height) continue;

            uint32_t color = (pixel_type == 1) ? 0x000000 : 0xFFFFFF;
            api->put_pixel(target_x, target_y, color);
        }
    }
}

extern "C" __attribute__((section(".text._start"), used, cdecl)) void _start(DE_API* api) {
    if (!api) return;

    de_mouse_state_t mouse_state;
    
    // Klavyeyle imleci test etmek için yedek koordinatlar
    int kbd_cursor_x = 100;
    int kbd_cursor_y = 100;

    while (1) {
        // 1. Klavyeden tuş oku (W, A, S, D ile test için)
        if (api->get_key) {
            char key = api->get_key();
            if (key == 'w' || key == 'W') kbd_cursor_y -= 5;
            if (key == 's' || key == 'S') kbd_cursor_y += 5;
            if (key == 'a' || key == 'A') kbd_cursor_x -= 5;
            if (key == 'd' || key == 'D') kbd_cursor_x += 5;
        }

        // 2. Fare konumunu oku
        if (api->get_mouse) {
            api->get_mouse(&mouse_state);
        }

        // 3. Ekranı temizle (Catppuccin Base)
        if (api->clear_screen) {
            api->clear_screen(0x1E1E2E);
        }

        // 4. Üst Görev Çubuğunu Çiz
        if (api->draw_rect) {
            uint32_t bar_color = mouse_state.left_button ? 0x45475A : 0x181825;
            api->draw_rect(0, 0, api->screen_width, 35, bar_color);
            
            // Klavyeyle hareket eden yeşil test kutusu
            api->draw_rect(kbd_cursor_x, kbd_cursor_y, 10, 10, 0xA6E3A1);
        }

        // 5. Gerçek Fare İmlecini Çiz
        draw_cursor(api, mouse_state.x, mouse_state.y);

        // 6. Ekranı Güncelle
        if (api->update_display) {
            api->update_display();
        }
    }
}