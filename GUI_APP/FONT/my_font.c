#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 32 px
 * Bpp: 4
 * Opts: --no-compress --format lvgl --font C:\Users\fish\Desktop\heiti.ttf -o C:\Users\fish\Desktop\my_font.c --bpp 4 --size 32 --symbols 正点原子
 ******************************************************************************/

#ifndef MY_FONT
#define MY_FONT 1
#endif

#if MY_FONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+539F "原" */
    0x0, 0x0, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
    0x44, 0x44, 0x44, 0x44, 0x44, 0x55, 0x0, 0x0,
    0xf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0xff,
    0xeb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb,
    0xbb, 0xbb, 0xcc, 0x0, 0x0, 0xe, 0xf9, 0x0,
    0x0, 0x0, 0x0, 0x9a, 0x60, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xef, 0x90, 0x0, 0x0,
    0x0, 0xe, 0xf9, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xe, 0xf9, 0x0, 0x0, 0x0, 0x2,
    0xff, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xef, 0x90, 0x4, 0xbb, 0xbb, 0xdf, 0xfb,
    0xbb, 0xbb, 0xbb, 0xbb, 0x10, 0x0, 0x0, 0xe,
    0xf9, 0x0, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf1, 0x0, 0x0, 0x0, 0xef, 0x90,
    0x5, 0xff, 0x32, 0x22, 0x22, 0x22, 0x22, 0x28,
    0xff, 0x10, 0x0, 0x0, 0xe, 0xf9, 0x0, 0x4f,
    0xf1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xf1,
    0x0, 0x0, 0x0, 0xef, 0x90, 0x4, 0xff, 0x10,
    0x0, 0x0, 0x0, 0x0, 0x6, 0xff, 0x10, 0x0,
    0x0, 0xe, 0xf9, 0x0, 0x4f, 0xfe, 0xee, 0xee,
    0xee, 0xee, 0xee, 0xef, 0xf1, 0x0, 0x0, 0x0,
    0xef, 0x90, 0x4, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x10, 0x0, 0x0, 0xe, 0xf9,
    0x0, 0x4f, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x6f, 0xf1, 0x0, 0x0, 0x0, 0xff, 0x80, 0x4,
    0xff, 0x10, 0x0, 0x0, 0x0, 0x0, 0x6, 0xff,
    0x10, 0x0, 0x0, 0xf, 0xf7, 0x0, 0x5f, 0xf3,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x8f, 0xf1, 0x0,
    0x0, 0x1, 0xff, 0x60, 0x5, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x20, 0x0, 0x0,
    0x3f, 0xf4, 0x0, 0x5d, 0xdd, 0xdd, 0xde, 0xff,
    0xdd, 0xdd, 0xdd, 0xd2, 0x0, 0x0, 0x6, 0xff,
    0x20, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xf1, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xf0, 0x0,
    0x0, 0x0, 0x0, 0x6, 0xff, 0x10, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xc, 0xfd, 0x0, 0x0, 0xa,
    0xa0, 0x0, 0x6f, 0xf1, 0x0, 0x9b, 0x0, 0x0,
    0x0, 0x0, 0xff, 0x90, 0x0, 0x6, 0xff, 0x80,
    0x6, 0xff, 0x10, 0x5f, 0xfc, 0x10, 0x0, 0x0,
    0x5f, 0xf5, 0x0, 0x3, 0xff, 0xd0, 0x0, 0x6f,
    0xf1, 0x0, 0x9f, 0xfd, 0x20, 0x0, 0xc, 0xff,
    0x0, 0x3, 0xff, 0xe1, 0x0, 0x6, 0xff, 0x10,
    0x0, 0x7f, 0xfe, 0x20, 0x3, 0xff, 0xa0, 0x5,
    0xff, 0xe2, 0x0, 0x0, 0x7f, 0xf1, 0x0, 0x0,
    0x6f, 0xfe, 0x20, 0xcf, 0xf3, 0x6, 0xff, 0xe2,
    0x0, 0x37, 0x7d, 0xff, 0x10, 0x0, 0x0, 0x6f,
    0xf3, 0x6f, 0xfc, 0x0, 0xa, 0xd2, 0x0, 0x1,
    0xff, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x73, 0x0,
    0x4d, 0x40, 0x0, 0x0, 0x0, 0x0, 0xc, 0xff,
    0xc4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0,

    /* U+5B50 "子" */
    0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x10,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f,
    0xff, 0xe7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0xff, 0xe6,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x9, 0xff, 0xf7, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x6, 0xef, 0xfa, 0x10, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3,
    0xef, 0xfe, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0xff,
    0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0x40,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0x40, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4, 0xff, 0x40, 0x0, 0x0,
    0x0, 0x0, 0x1, 0x21, 0x4f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf6, 0x4f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf5, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4,
    0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff,
    0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0x40,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0x40, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4, 0xff, 0x40, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4, 0xff, 0x40, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4, 0xff, 0x40, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5,
    0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1, 0x11, 0x3c, 0xff,
    0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x5, 0xff, 0xff, 0xff, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xdf, 0xff, 0xf7, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7a, 0x85, 0x10, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0,

    /* U+6B63 "正" */
    0x0, 0x3, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x30, 0x0, 0x2,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x10, 0x0, 0x2f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf1, 0x0, 0x0, 0x32, 0x22, 0x22,
    0x22, 0x22, 0x2e, 0xfa, 0x22, 0x22, 0x22, 0x22,
    0x23, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xef, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe,
    0xf9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xef, 0x90,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xf9, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xdd,
    0x20, 0x0, 0x0, 0xef, 0x90, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xf2, 0x0,
    0x0, 0xe, 0xf9, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x9, 0xff, 0x10, 0x0, 0x0,
    0xef, 0x90, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0,
    0x0, 0x0, 0x8f, 0xf1, 0x0, 0x0, 0xe, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf7, 0x0, 0x0, 0x0,
    0x8, 0xff, 0x10, 0x0, 0x0, 0xef, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x70, 0x0, 0x0, 0x0, 0x8f,
    0xf1, 0x0, 0x0, 0xe, 0xfa, 0x22, 0x22, 0x22,
    0x22, 0x31, 0x0, 0x0, 0x0, 0x8, 0xff, 0x10,
    0x0, 0x0, 0xef, 0x90, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x8f, 0xf1, 0x0, 0x0,
    0xe, 0xf9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x8, 0xff, 0x10, 0x0, 0x0, 0xef,
    0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8f, 0xf1, 0x0, 0x0, 0xe, 0xf9, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8,
    0xff, 0x10, 0x0, 0x0, 0xef, 0x90, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xf1,
    0x0, 0x0, 0xe, 0xf9, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0x10, 0x0,
    0x0, 0xef, 0x90, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x8f, 0xf1, 0x0, 0x0, 0xe,
    0xf9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8, 0xff, 0x10, 0x0, 0x0, 0xef, 0x90,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xf3, 0x4f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x31, 0x65, 0x54, 0x44, 0x44, 0x44,
    0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x45, 0x55,
    0x61,

    /* U+70B9 "点" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x10,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xfa, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1f, 0xf9, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1f, 0xf8, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1f, 0xf8, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xfa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f,
    0xf9, 0x22, 0x22, 0x22, 0x22, 0x33, 0x43, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xf8,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xf8, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0x22, 0x22, 0x22, 0x3f, 0xf9, 0x22, 0x22,
    0x22, 0x22, 0x20, 0x0, 0x0, 0x0, 0x0, 0x1f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf2, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf2, 0x0, 0x0, 0x0, 0x0, 0xf, 0xfa, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0xf, 0xfa, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xf1, 0x0,
    0x0, 0x0, 0x0, 0xf, 0xfa, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xf1, 0x0, 0x0,
    0x0, 0x0, 0xf, 0xfa, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xf0, 0x0, 0x0, 0x0,
    0x0, 0xf, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7f, 0xf0, 0x0, 0x0, 0x0, 0x0,
    0xf, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7f, 0xf1, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf1, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf2, 0x0, 0x0, 0x0, 0x0, 0x2, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x20,
    0x0, 0x0, 0x0, 0x3, 0x50, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x9, 0xff, 0x40, 0x0, 0x74, 0x0,
    0x0, 0x2b, 0x80, 0x0, 0x0, 0x6e, 0x20, 0x0,
    0x0, 0xf, 0xfe, 0x0, 0xe, 0xfc, 0x0, 0x0,
    0xbf, 0xf2, 0x0, 0x3, 0xff, 0xc0, 0x0, 0x0,
    0x6f, 0xf7, 0x0, 0x8, 0xff, 0x30, 0x0, 0x3f,
    0xfa, 0x0, 0x0, 0x9f, 0xf6, 0x0, 0x0, 0xef,
    0xe0, 0x0, 0x2, 0xff, 0xa0, 0x0, 0xb, 0xff,
    0x30, 0x0, 0xe, 0xff, 0x10, 0x7, 0xff, 0x70,
    0x0, 0x0, 0xcf, 0xf1, 0x0, 0x2, 0xff, 0xc0,
    0x0, 0x6, 0xff, 0xa0, 0x1f, 0xff, 0x10, 0x0,
    0x0, 0x6f, 0xf5, 0x0, 0x0, 0xbf, 0xf1, 0x0,
    0x0, 0xdf, 0xf3, 0x3, 0xb7, 0x0, 0x0, 0x0,
    0x2a, 0x30, 0x0, 0x0, 0x39, 0x10, 0x0, 0x0,
    0x5c, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 512, .box_w = 29, .box_h = 29, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 421, .adv_w = 512, .box_w = 30, .box_h = 28, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 841, .adv_w = 512, .box_w = 29, .box_h = 26, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1218, .adv_w = 512, .box_w = 30, .box_h = 31, .ofs_x = 1, .ofs_y = -4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x7b1, 0x17c4, 0x1d1a
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 21407, .range_length = 7451, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t my_font = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};

#endif /*#if MY_FONT*/

