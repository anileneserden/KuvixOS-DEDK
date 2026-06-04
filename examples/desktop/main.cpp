// examples/desktop/main.cpp
#include <kernel/drivers/video/de_api.h>
#include <graphics/Framebuffer.hpp>

extern "C" __attribute__((section(".text._start"))) void _start(DE_API* api) {
    if (!api) {
        while(1) { asm volatile("hlt"); }
    }

    // Ekran boyutlarını ata
    int screen_width = 1024;
    int screen_height = 768;

    Framebuffer::init(screen_width, screen_height, api);

    // Sahnemizi çiziyoruz
    Framebuffer::clear(0x1A2B3C);
    Framebuffer::draw_rectangle(0, 0, screen_width, 40, 0x2D2D2D);
    Framebuffer::draw_rectangle(150, 150, 400, 250, 0xEEEEEE);
    Framebuffer::draw_rectangle(150, 150, 400, 30, 0x007ACC);

    Framebuffer::present();

    while(1) { 
        asm volatile("hlt"); 
    }
}