// src/graphics/Framebuffer.cpp
#include <graphics/Framebuffer.hpp>

// Statik üyelerin tanımları
DE_API* Framebuffer::m_api = nullptr;
uint32_t* Framebuffer::m_back_buffer = nullptr;
int Framebuffer::m_width = 0;
int Framebuffer::m_height = 0;

void Framebuffer::init(int width, int height, DE_API* api) {
    m_width = width;
    m_height = height;
    m_api = api;
    m_back_buffer = nullptr; // Şimdilik arka tamponu boşa çıkarıyoruz
}

void Framebuffer::clear(uint32_t color) {
    if (m_api) {
        m_api->clear(color); // Doğrudan kernel temizlesin
    }
}

void Framebuffer::put_pixel(int x, int y, uint32_t color) {
    // Sınır kontrolü
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return;
    
    if (m_api) {
        m_api->put_pixel(x, y, color); // Doğrudan VRAM'e yaz
    }
}

void Framebuffer::draw_rectangle(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            put_pixel(x + j, y + i, color);
        }
    }
}

void Framebuffer::present() {
    if (m_api) {
        m_api->update_display(); // Kernel'a ekranı tazelet
    }
}