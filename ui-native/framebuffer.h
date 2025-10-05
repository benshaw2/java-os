// ui-native/framebuffer.h

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

int fb_init();
void fb_close();
void fb_clear(uint32_t color);
void fb_draw_pixel(int x, int y, uint32_t color);
void fb_draw_rect(int x, int y, int width, int height, uint32_t color);

#endif

