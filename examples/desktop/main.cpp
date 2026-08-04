#include <kernel/drivers/video/de_api.h>
#include <graphics/Window.hpp>

// 10x14 Fare Ok Matrisi
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
    
    // Pencere Tanımı
    Window win;
    win.x = 150;
    win.y = 100;
    win.width = 320;
    win.height = 200;
    win.title = "KuvixOS";
    win.bg_color = 0x313244;
    win.is_dragging = false;
    win.drag_offset_x = 0;
    win.drag_offset_y = 0;

    int last_mouse_left = 0;

    while (1) {
        // 1. Fare konumunu güvenli bir şekilde oku
        if (api->get_mouse) {
            api->get_mouse(&mouse_state);
        }

        // 2. Basitleştirilmiş ve Güvenli Sürükleme Mantığı
        int title_bar_height = 24;
        
        // Sol tuşa yeni basıldı mı? (Edge detection)
        int left_click_started = (mouse_state.left_button && !last_mouse_left);

        if (left_click_started) {
            // Tıklama başlık çubuğunun içinde mi?
            if (mouse_state.x >= win.x && mouse_state.x <= (win.x + win.width) &&
                mouse_state.y >= win.y && mouse_state.y <= (win.y + title_bar_height)) {
                win.is_dragging = true;
                win.drag_offset_x = mouse_state.x - win.x;
                win.drag_offset_y = mouse_state.y - win.y;
            }
        } 
        
        // Sol tuş bırakıldıysa sürüklemeyi bitir
        if (!mouse_state.left_button) {
            win.is_dragging = false;
        }

        // Eğer sürükleniyorsa pencere konumunu güncelle
        if (win.is_dragging) {
            win.x = mouse_state.x - win.drag_offset_x;
            win.y = mouse_state.y - win.drag_offset_y;
        }

        last_mouse_left = mouse_state.left_button;

        // 3. Ekranı Temizle
        if (api->clear_screen) {
            api->clear_screen(0x1E1E2E);
        }

        // 4. Üst Görev Çubuğu
        if (api->draw_rect) {
            api->draw_rect(0, 0, api->screen_width, 35, 0x181825);
        }

        // 5. Pencereyi Çiz (Başlık + Gövde)
        if (api->draw_rect) {
            api->draw_rect(win.x, win.y, win.width, title_bar_height, 0x89B4FA); // Başlık
            api->draw_rect(win.x, win.y + title_bar_height, win.width, win.height - title_bar_height, win.bg_color); // Gövde
        }

        // 6. Pencere Başlığı
        if (api->draw_text) {
            api->draw_text(win.x + 8, win.y + 4, win.title, 0x11111B);
        }

        // 7. Fare İmlecini Çiz
        draw_cursor(api, mouse_state.x, mouse_state.y);

        // 8. Ekranı Güncelle
        if (api->update_display) {
            api->update_display();
        }
    }
}