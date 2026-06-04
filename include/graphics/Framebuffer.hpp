// include/graphics/Framebuffer.hpp
#pragma once
#include <kernel/drivers/video/de_api.h>
#include <stdint.h>

class Framebuffer {
public:
    static void init(int width, int height, DE_API* api);
    static void clear(uint32_t color);
    static void put_pixel(int x, int y, uint32_t color);
    static void draw_rectangle(int x, int y, int width, int height, uint32_t color);
    static void present();

private:
    static DE_API* m_api;
    static uint32_t* m_back_buffer;
    static int m_width;
    static int m_height;
};