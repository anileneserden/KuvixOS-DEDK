// examples/desktop/main.cpp
#include <kernel/drivers/video/de_api.h>
#include <graphics/Framebuffer.hpp>
#include <graphics/Grid.hpp>

extern "C" __attribute__((section(".text._start"))) void _start(DE_API* api) {
    // Güvenlik Kontrolü: API boş gelirse sistemi kilitle
    if (!api) {
        while(1) { asm volatile("hlt"); }
    }

    // Ekran boyutlarını doğrudan kernel yapısından alıyoruz
    int screen_width = api->screen_width;
    int screen_height = api->screen_height;
    
    // Framebuffer modülünü başlat
    Framebuffer::init(screen_width, screen_height, api);
    
    // Grid sistemini başlatıyoruz:
    // Hücre boyutu: 64x64 piksel, Boşluk (Spacing): 24 piksel, Üst panel marjı: 40 piksel
    DesktopGrid::init(screen_width, screen_height, 64, 24, 40);

    // 1. Masaüstü Arka Planını Çiz (KuvixOS Gece Mavisi)
    Framebuffer::clear(0x1A2B3C);

    // 2. Üst Bar / Paneli Çiz (Koyu Gri)
    Framebuffer::draw_rectangle(0, 0, screen_width, 40, 0x2D2D2D);

    // 3. SİMÜLASYON: 5 Farklı rengi olan sahte masaüstü kısayol ikonları tanımlıyoruz
    // Yarın bir gün .desktop dosyalarını okuduğumuzda bu döngü dinamik olacak
    uint32_t icon_colors[] = {
        0x2ECC71, // Yeşil İkon (Örn: Dosya Yöneticisi)
        0xE74C3C, // Kırmızı İkon (Örn: Tarayıcı/Terminal)
        0x3498DB, // Mavi İkon (Örn: Sistem Ayarları)
        0xF1C40F, // Sarı İkon (Örn: Hesap Makinesi)
        0x9B59B6  // Mor İkon (Örn: KuvixOS Mağaza)
    };

    // İkonları grid mimarisine göre ekrana yerleştiriyoruz
    for (int i = 0; i < 5; i++) {
        // Matematiksel olarak i. indeks için ekrandaki güvenli (X, Y) koordinatını iste
        Point icon_pos = DesktopGrid::get_slot_position(i);
        
        // Grid'den dönen koordinata 64x64 boyutunda ikon karelerini çiziyoruz
        Framebuffer::draw_rectangle(icon_pos.x, icon_pos.y, 64, 64, icon_colors[i]);
    }

    // 4. Sahnemizi VRAM'e bas ve ekranı tazelet
    Framebuffer::present();

    // İşlemciyi uyku modunda tutarak masaüstünü ekranda kilitle
    while(1) { 
        asm volatile("hlt"); 
    }
}