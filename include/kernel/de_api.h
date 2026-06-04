// include/kernel/de_api.h
#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Kernel'ın DEDK'ya sağlayacağı fonksiyonların tip tanımlamaları (Typedefs)
typedef void (*de_clear_t)(uint32_t color);
typedef void (*de_put_pixel_t)(int x, int y, uint32_t color);
typedef void (*de_update_display_t)(void);
typedef void (*de_log_t)(const char* str); // İleride seri port debug logu için hazır dursun

// Kernel'dan _start fonksiyonumuza parametre olarak gelecek ana API yapısı
typedef struct {
    de_clear_t         clear;          // Ekranı temizleme fonksiyon adresi
    de_put_pixel_t     put_pixel;      // Piksel çizme fonksiyon adresi
    de_update_display_t update_display; // Ekrana basma/Yenileme fonksiyon adresi
    de_log_t           log;            // Seri port log fonksiyon adresi
} DE_API;

#ifdef __cplusplus
}
#endif