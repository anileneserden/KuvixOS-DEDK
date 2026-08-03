#include <kernel/drivers/video/de_api.h>

extern "C" __attribute__((section(".text._start"), used, cdecl)) void _start(DE_API* api) {
    if (!api) return;

    // Ekranı Catppuccin Base rengiyle (Koyu Lacivert / Mor) temizle
    if (api->clear_screen) {
        api->clear_screen(0x1E1E2E);
    }

    // Üst Görev Çubuğunu Çiz
    if (api->draw_rect) {
        api->draw_rect(0, 0, api->screen_width, 35, 0x181825);
    }

    // Ekranı Tazele
    if (api->update_display) {
        api->update_display();
    }

    while (1) {
        __asm__ __volatile__("nop");
    }
}