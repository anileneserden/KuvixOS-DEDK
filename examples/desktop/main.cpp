#include <kernel/drivers/video/de_api.h>

// --- KUVIXOS V2 STRING HİLESİ MAKROSU ---
// Flat binary formatında .rodata adres kaymasını engellemek için 
// string değerini dinamik olarak işlemci yığınında (stack) oluşturur.
#define DE_DRAW_TEXT(api_ptr, x, y, literal_str, color) \
    do { \
        char _stack_str[] = literal_str; \
        (api_ptr)->draw_text((x), (y), _stack_str, (color)); \
    } while(0)

extern "C" __attribute__((section(".text._start"))) void _start(DE_API* api) {
    // Güvenlik Kontrolü: API boş gelirse sistemi kilitle
    if (!api) {
        while(1) { asm volatile("hlt"); }
    }

    // 1. Arka Planı Çiz (Modern Koyu Tema: Gece Mavisi)
    api->clear(0x1E1E2E);

    // 2. Üst Bar / Paneli Çiz (Ekran genişliğinde, 40 piksel yüksekliğinde, Koyu Gri)
    api->draw_rect(0, 0, api->screen_width, 40, 0x252538);

    // 3. İlk Test İkonunu Çiz (50x50 boyutunda modern bir mavi kare)
    api->draw_rect(37, 60, 50, 50, 0x89B4FA);

    // 4. İkonun Altına Metin Bas (Yeni Güvenli Makro İle)
    // Artık char array tanımlama ameleliği bitti, doğrudan tırnak içinde yazabilirsin!
    DE_DRAW_TEXT(api, 32, 120, "Terminal", 0xFFFFFF);

    // Örnek: Üst bara saat veya sistem sürümü eklemek istersen:
    DE_DRAW_TEXT(api, api->screen_width - 130, 15, "KuvixOS V2.0", 0xA0A0A0);

    // 5. Sahnemizi VRAM'e yansıt (Present)
    api->update_display();

    // İşlemciyi uyku modunda tutarak ekranı bu şekilde kilitle
    while(1) { 
        asm volatile("hlt"); 
    }
}