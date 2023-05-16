/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _`$INSTANCE_NAME`_GFX_H
#define _`$INSTANCE_NAME`_GFX_H
    
#include "cytypes.h"
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_gfxfont.h"
#include "stdlib.h" // size_t data type   
        
// TRANSACTION API / CORE DRAW API
void    `$INSTANCE_NAME`_WriteLine(ST7789 *st7789, int16_t x0, int16_t y0,
            int16_t x1, int16_t y1, uint16_t color);
void    `$INSTANCE_NAME`_DrawLine(ST7789 *st7789, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
            uint16_t color);

void    `$INSTANCE_NAME`_DrawCircle(ST7789 *st7789, int16_t x0, int16_t y0,
            int16_t r, uint16_t color);
void    `$INSTANCE_NAME`_DrawCircleHelper(ST7789 *st7789, int16_t x0, int16_t y0,
            int16_t r, uint8_t cornername, uint16_t color);
void    `$INSTANCE_NAME`_FillCircle(ST7789 *st7789, int16_t x0, int16_t y0, int16_t r,
            uint16_t color);
void    `$INSTANCE_NAME`_FillCircleHelper(ST7789 *st7789, int16_t x0, int16_t y0, int16_t r,
            uint8_t cornername, int16_t delta, uint16_t color);

void    `$INSTANCE_NAME`_DrawRect(ST7789 *st7789, int16_t x, int16_t y, int16_t w, int16_t h,
            uint16_t color);
void    `$INSTANCE_NAME`_DrawRoundRect(ST7789 *st7789, int16_t x, int16_t y, int16_t w,
            int16_t h, int16_t r, uint16_t color);
void    `$INSTANCE_NAME`_FillRoundRect(ST7789 *st7789, int16_t x, int16_t y, int16_t w,
            int16_t h, int16_t r, uint16_t color);

void    `$INSTANCE_NAME`_DrawTriangle(ST7789 *st7789, int16_t x0, int16_t y0,
            int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void    `$INSTANCE_NAME`_FillTriangle(ST7789 *st7789, int16_t x0, int16_t y0,
            int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

void    `$INSTANCE_NAME`_DrawBitmapConstNoBg(ST7789 *st7789, int16_t x, int16_t y,
            const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
void    `$INSTANCE_NAME`_DrawBitmapNoBg(ST7789 *st7789, int16_t x, int16_t y,
            uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
void    `$INSTANCE_NAME`_DrawBitmapConstBg(ST7789 *st7789, int16_t x, int16_t y,
            const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color, uint16_t bg);
void    `$INSTANCE_NAME`_DrawBitmapBg(ST7789 *st7789, int16_t x, int16_t y,
            uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);

void    `$INSTANCE_NAME`_DrawXBitmap(ST7789 *st7789, int16_t x, int16_t y,
            const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);

void    `$INSTANCE_NAME`_DrawGrayscaleBitmapConstNoMask(ST7789 *st7789, int16_t x, int16_t y,
            const uint8_t bitmap[], int16_t w, int16_t h);
void    `$INSTANCE_NAME`_DrawGrayscaleBitmapNoMask(ST7789 *st7789, int16_t x, int16_t y,
            uint8_t *bitmap, int16_t w, int16_t h);
void    `$INSTANCE_NAME`_DrawGrayscaleBitmapConstMask(ST7789 *st7789, int16_t x, int16_t y,
            const uint8_t bitmap[], const uint8_t mask[],
            int16_t w, int16_t h);
void    `$INSTANCE_NAME`_DrawGrayscaleBitmapMask(ST7789 *st7789, int16_t x, int16_t y,
            uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h);

void    `$INSTANCE_NAME`_DrawChar(ST7789 *st7789, int16_t x, int16_t y, unsigned char c,
            uint16_t color, uint16_t bg, uint8_t size);
size_t  `$INSTANCE_NAME`_Write(ST7789 *st7789, uint8_t c);
void    `$INSTANCE_NAME`_SetCursor(ST7789 *st7789, int16_t x, int16_t y);
int16_t `$INSTANCE_NAME`_GetCursorX(ST7789 *st7789);
int16_t `$INSTANCE_NAME`_GetCursorY(ST7789 *st7789);
void    `$INSTANCE_NAME`_SetTextSize(ST7789 *st7789, uint8_t s);
uint8_t `$INSTANCE_NAME`_GetRotation(ST7789 *st7789);
void    `$INSTANCE_NAME`_Cp437(ST7789 *st7789, uint8_t x);
void    `$INSTANCE_NAME`_SetFont(ST7789 *st7789, const GFXfont *f);
void    `$INSTANCE_NAME`_CharBounds(ST7789 *st7789, char c, int16_t *x, int16_t *y,
            int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);
void    `$INSTANCE_NAME`_GetTextBounds(ST7789 *st7789, char *str, int16_t x, int16_t y,
            int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);

size_t `$INSTANCE_NAME`_WriteString(ST7789 *st7789, const uint8_t *buffer, size_t size);

size_t `$INSTANCE_NAME`_Print(ST7789 *st7789, const char[]);
size_t `$INSTANCE_NAME`_PrintChar(ST7789 *st7789, char);

size_t `$INSTANCE_NAME`_Println(ST7789 *st7789, const char[]);
size_t `$INSTANCE_NAME`_PrintlnChar(ST7789 *st7789, char);

#endif

/* [] END OF FILE */
