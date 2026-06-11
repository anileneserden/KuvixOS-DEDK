// include/kernel/de_api.h
#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*de_clear_t)(uint32_t color);
typedef void (*de_put_pixel_t)(int x, int y, uint32_t color);
typedef void (*de_draw_rect_t)(int x, int y, int w, int h, uint32_t color);
typedef void (*de_draw_text_t)(int x, int y, const char* text, uint32_t color);
typedef void (*de_update_display_t)(void);
typedef void (*de_log_t)(const char* str);

typedef struct {
    int screen_width;
    int screen_height;
    
    de_clear_t clear;
    de_put_pixel_t put_pixel;
    de_draw_rect_t draw_rect;
    de_draw_text_t draw_text;
    de_update_display_t update_display;
    de_log_t log;
} DE_API;

#ifdef __cplusplus
}
#endif