// include/kernel/de_api.h
#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*de_clear_t)(uint32_t color);
typedef void (*de_put_pixel_t)(int x, int y, uint32_t color);
typedef void (*de_update_display_t)(void);
typedef void (*de_log_t)(const char* str);

typedef struct {
    int screen_width;
    int screen_height;
    void (*clear)(uint32_t color);
    void (*put_pixel)(int x, int y, uint32_t color);
    void (*update_display)(void);
    void (*log)(const char* str);
} DE_API;

#ifdef __cplusplus
}
#endif