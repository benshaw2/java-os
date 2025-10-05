// ui-native/framebuffer.c

#include "framebuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

static int fb_fd = -1;
static uint8_t* fb_ptr = NULL;
static long int fb_size = 0;
static int fb_width = 0;
static int fb_height = 0;
static int fb_bpp = 0;
static int fb_stride = 0;

int fb_init() {
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;

    fb_fd = open("/dev/fb0", O_RDWR);
    if (fb_fd < 0) {
        perror("Error opening framebuffer");
        return -1;
    }

    if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo)) {
        perror("FBIOGET_FSCREENINFO");
        return -1;
    }

    if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo)) {
        perror("FBIOGET_VSCREENINFO");
        return -1;
    }

    fb_width = vinfo.xres;
    fb_height = vinfo.yres;
    fb_bpp = vinfo.bits_per_pixel;
    fb_stride = finfo.line_length;
    fb_size = fb_stride * fb_height;

    fb_ptr = (uint8_t*)mmap(0, fb_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
    if ((intptr_t)fb_ptr == -1) {
        perror("mmap");
        return -1;
    }

    return 0;
}

void fb_close() {
    if (fb_ptr) munmap(fb_ptr, fb_size);
    if (fb_fd >= 0) close(fb_fd);
}

void fb_clear(uint32_t color) {
    for (int y = 0; y < fb_height; ++y) {
        for (int x = 0; x < fb_width; ++x) {
            fb_draw_pixel(x, y, color);
        }
    }
}

void fb_draw_pixel(int x, int y, uint32_t color) {
    if (x < 0 || x >= fb_width || y < 0 || y >= fb_height) return;

    int offset = y * fb_stride + x * (fb_bpp / 8);
    *((uint32_t*)(fb_ptr + offset)) = color;
}

void fb_draw_rect(int x, int y, int w, int h, uint32_t color) {
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            fb_draw_pixel(j, i, color);
        }
    }
}

