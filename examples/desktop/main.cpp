// examples/desktop/main.cpp
#include <kernel/de_api.h>
#include <graphics/Framebuffer.hpp>

extern "C" __attribute__((section(".text._start"))) void _start(DE_API* api) {
    if (!api) {
        while(1) { asm volatile("hlt"); }
    }

    // 1. Framebuffer C++ sınıfımızı kernel API'si ile besle
    Framebuffer::init(api);

    // 2. İLK HAMLE: Konsolu kapat
    Framebuffer::set_console_enabled(false);

    // 3. EKRANI TEMİZLE (KuvixOS Mavisi)
    Framebuffer::clear(0x1A2B3C);

    // 4. GRAFİK TESTİ: Kırmızı Kare Çiz
    for (int y = 150; y < 250; y++) {
        for (int x = 150; x < 250; x++) {
            Framebuffer::put_pixel(x, y, 0xFF0000);
        }
    }

    // 5. EKRANA BAS (Present)
    Framebuffer::present();

    // Sonsuz döngü
    while(1) { 
        asm volatile("hlt"); 
    }
}