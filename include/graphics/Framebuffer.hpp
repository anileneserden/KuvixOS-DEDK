// include/graphics/Framebuffer.hpp
#pragma once
#include <stdint.h>
#include <kernel/de_api.h>

class Framebuffer {
private:
    static DE_API* m_api;

public:
    // Kernel'dan gelen API işaretçisini sınıfa kaydeden ilklendirici
    static void init(DE_API* api);

    // İstediğin o 3 kritik fonksiyon:
    static void set_console_enabled(bool enabled);
    static void clear(uint32_t color);
    static void present();
    
    // Piksel çizim fonksiyonu (İleride dock ve imleç için gerekecek)
    static void put_pixel(int x, int y, uint32_t color);
};