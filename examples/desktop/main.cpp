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
    if (!api) while(1) { asm volatile("hlt"); }

    // İlk çizimler
    api->clear(0x1E1E2E);
    api->draw_rect(0, 0, api->screen_width, 40, 0x252538);
    DE_DRAW_TEXT(api, 32, 120, "Terminal", 0xFFFFFF);
    DE_DRAW_TEXT(api, api->screen_width - 150, 15, "KuvixOS V2.0", 0xA0A0A0);

    // Saat için değişkenler
    char time_str[9];
    char last_time[9] = ""; // Saati sadece değiştiğinde güncellemek için

    // DEDK V2 Render Döngüsü
    while(1) {
        // 1. Saati Kernel'dan çek
        api->get_time(time_str);

        // 2. Eğer saat değiştiyse ekrana bas
        // (strcmp kullanabilmen için string.h'in dahil olması lazım)
        // Eğer kernel tarafında kendi string.h kütüphanen varsa onu kullan.
        bool changed = false;
        for(int i = 0; i < 9; i++) {
            if(time_str[i] != last_time[i]) changed = true;
        }

        if(changed) {
            // Eski saatin olduğu yeri arka plan rengiyle temizle (Bar rengi: 0x252538)
            api->draw_rect(api->screen_width - 90, 15, 80, 20, 0x252538);
            
            // Yeni saati çiz
            api->draw_text(api->screen_width - 90, 15, time_str, 0xFFFFFF);
            
            // Ekranı güncelle
            api->update_display();
            
            // last_time'ı güncelle
            for(int i = 0; i < 9; i++) last_time[i] = time_str[i];
        }

        // 3. İşlemciyi tamamen durdurma, küçük bir bekleme yap
        // Eğer api->sleep() yoksa, bir miktar "nop" veya boş döngü çevirebilirsin
        // ama hlt yaparsan saat güncellenmez!
        for(volatile int i = 0; i < 1000000; i++); 
    }
}