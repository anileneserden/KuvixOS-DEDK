// src/graphics/Framebuffer.cpp
#include <graphics/Framebuffer.hpp>

// Static üyenin tanımlanması
DE_API* Framebuffer::m_api = nullptr;

void Framebuffer::init(DE_API* api) {
    m_api = api;
}

void Framebuffer::set_console_enabled(bool enabled) {
    // NOT: Eğer kernel'ın sağladığı DE_API içinde console_set_enabled yoksa,
    // kernel tarafında de_api.h'a bunu eklemen veya doğrudan syscall yapman gerekir.
    // Şimdilik API üzerinden geldiğini varsayarak güvenli çağrı yapıyoruz:
    if (m_api && m_api->log) { 
        // Konsol durumunu log üzerinden veya api genişletildiyse doğrudan tetikle
        m_api->log(enabled ? "[DEDK] Konsol aciliyor...\n" : "[DEDK] Konsol kapatiliyor...\n");
    }
}

void Framebuffer::clear(uint32_t color) {
    if (m_api && m_api->clear) {
        m_api->clear(color);
    }
}

void Framebuffer::present() {
    if (m_api && m_api->update_display) {
        m_api->update_display();
    }
}

void Framebuffer::put_pixel(int x, int y, uint32_t color) {
    if (m_api && m_api->put_pixel) {
        m_api->put_pixel(x, y, color);
    }
}