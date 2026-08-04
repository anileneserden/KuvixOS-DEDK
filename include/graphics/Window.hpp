#pragma once
#include <stdint.h>

struct Window {
    int x, y;          // Ekrandaki konumu
    int width, height; // Boyutları
    const char* title; // Başlık çubuğu yazısı
    uint32_t bg_color; // Pencere içi arka plan rengi
    bool is_dragging;  // Fareyle sürükleniyor mu?
    int drag_offset_x; // Sürükleme sırasında fare farkı
    int drag_offset_y;
};