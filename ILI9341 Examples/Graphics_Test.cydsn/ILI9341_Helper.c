
#include "ST7789_Helper.h"

#ifndef min
    #define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

void ST7789_TestFillScreen(ST7789 *st7789) {
    // Fill screen with different colors
    ST7789_FillScreen(st7789, ST7789_BLACK);
    ST7789_FillScreen(st7789, ST7789_RED);
    ST7789_FillScreen(st7789, ST7789_GREEN);
    ST7789_FillScreen(st7789, ST7789_BLUE);
    ST7789_FillScreen(st7789, ST7789_BLACK);
}

void ST7789_TestLines(ST7789 *st7789, uint16_t color) {
    // Test line showing in normal mode
    int x1, y1, x2, y2;       // Coordinates
    int w = st7789->width,   // Screen width
        h = st7789->height;  // Screen height
    
    // fill screen with black
    ST7789_FillScreen(st7789, ST7789_BLACK);
    
    // Draw lines 
    x1 = y1 = 0;
    y2 = h - 1;
    for(x2=0; x2<w; x2+=6)
        ST7789_DrawLine(st7789, x1, y1, x2, y2, color);
  
    x2 = w - 1;
    for(y2=0; y2<h; y2+=6)
        ST7789_DrawLine(st7789,x1, y1, x2, y2, color);
        
    // Fill screen again
    ST7789_FillScreen(st7789, ST7789_BLACK);
    x1  = w - 1;
    y1  = 0;
    y2  = h - 1;

    // Draw lines
    for(x2=0; x2<w; x2+=6)
        ST7789_DrawLine(st7789, x1, y1, x2, y2, color);
    x2 = 0;
    for(y2=0; y2<h; y2+=6)
        ST7789_DrawLine(st7789, x1, y1, x2, y2, color);
    // Fill screen again
    ST7789_FillScreen(st7789,ST7789_BLACK);
    
    // Reset coordinates
    x1    = 0;
    y1    = h - 1;
    y2    = 0;
    // Draw lines
    for(x2=0; x2<w; x2+=6) {
        ST7789_DrawLine(st7789,x1, y1, x2, y2, color);   
    }
    
    x2    = w - 1;
    for(y2=0; y2<h; y2+=6) {
        ST7789_DrawLine(st7789,x1, y1, x2, y2, color);
    }
    // Fill screen again
    ST7789_FillScreen(st7789,ST7789_BLACK);

    x1    = w - 1;
    y1    = h - 1;
    y2    = 0;
    // Draw lines
    for(x2=0; x2<w; x2+=6) {
        ST7789_DrawLine(st7789,x1, y1, x2, y2, color);
    }
    x2    = 0;
    for(y2=0; y2<h; y2+=6) {
        ST7789_DrawLine(st7789,x1, y1, x2, y2, color);
    }
}

void ST7789_TestFastLines(ST7789 *st7789, uint16_t color1, uint16_t color2) {
    // Test line drawing in fast mode
    int x, y, w = st7789->width, h = st7789->height;

    ST7789_FillScreen(st7789, ST7789_BLACK);
    for(y=0; y<h; y+=5) 
        ST7789_DrawFastHLine(st7789, 0, y, w, color1);
    for(x=0; x<w; x+=5) 
        ST7789_DrawFastVLine(st7789, x, 0, h, color2);
}

void ST7789_TestRects(ST7789 *st7789, uint16_t color) {
    // Test rectangles drawing
    int n, i, i2,
        cx = st7789->width  / 2,
        cy = st7789->height / 2;

    ST7789_FillScreen(st7789, ST7789_BLACK);
    n = min(st7789->width, st7789->height);
    for(i=2; i<n; i+=6) {
        i2 = i / 2;
        ST7789_DrawRect(st7789, cx-i2, cy-i2, i, i, color);
    }
}

void ST7789_TestFilledRects(ST7789 *st7789, uint16_t color1, uint16_t color2) {
    // Test filled rectangles drawing
    int n, i, i2,
        cx = st7789->width  / 2 - 1,
        cy = st7789->height / 2 - 1;

    ST7789_FillScreen(st7789, ST7789_BLACK);
    n = min(st7789->width , st7789->height);
    for(i=n; i>0; i-=6) {
        i2    = i / 2;
        ST7789_FillRect(st7789,cx-i2, cy-i2, i, i, color1);
        ST7789_DrawRect(st7789,cx-i2, cy-i2, i, i, color2);
    }

}

void ST7789_TestFilledCircles(ST7789 *st7789, uint8_t radius, uint16_t color) {
    // Test filled circles
    int x, y, w = st7789->width, h = st7789->height, r2 = radius * 2;

    ST7789_FillScreen(st7789, ST7789_BLACK);
    for(x=radius; x<w; x+=r2) {
        for(y=radius; y<h; y+=r2) {
        ST7789_FillCircle(st7789, x, y, radius, color);
        }
    }
}

void ST7789_TestCircles(ST7789 *st7789, uint8_t radius, uint16_t color) {
    // Test circles
    int x, y, r2 = radius * 2,
        w = st7789->width  + radius,
        h = st7789->height + radius;
    for(x=0; x<w; x+=r2) {
        for(y=0; y<h; y+=r2) {
        ST7789_DrawCircle(st7789, x, y, radius, color);
        }
    }
}

void ST7789_TestTriangles(ST7789 *st7789) {
    // Test triangles
    int n, i, 
        cx = st7789->width  / 2 - 1,
        cy = st7789->height / 2 - 1;

    ST7789_FillScreen(st7789, ST7789_BLACK);
    n = min(cx, cy);

    for(i=0; i<n; i+=5) {
        ST7789_DrawTriangle(st7789,
        cx    , cy - i, // peak
        cx - i, cy + i, // bottom left
        cx + i, cy + i, // bottom right
        ST7789_Color565(i, i, i));
    }
}

void ST7789_TestFilledTriangles(ST7789 *st7789) {
    // Test filled triangles
    int i,
        cx = st7789->width  / 2 - 1,
        cy = st7789->height / 2 - 1;

  ST7789_FillScreen(st7789, ST7789_BLACK);
  for(i=min(cx,cy); i>10; i-=5) {
    ST7789_FillTriangle(st7789, cx, cy - i, cx - i, cy + i, cx + i, cy + i,
    ST7789_Color565(0, i*10, i*10));
    ST7789_DrawTriangle(st7789, cx, cy - i, cx - i, cy + i, cx + i, cy + i,
    ST7789_Color565(i*10, i*10, 0));
  }
}

void ST7789_TestRoundRects(ST7789 *st7789) {
    // Test round rectangles
    int w, i, i2,
        cx = st7789->width  / 2 - 1,
        cy = st7789->height / 2 - 1;

    ST7789_FillScreen(st7789, ST7789_BLACK);
    w = min(st7789->width, st7789->height);
    for(i=0; i<w; i+=6) {
        i2 = i / 2;
        ST7789_DrawRoundRect(st7789, cx-i2, cy-i2, i, i, i/8, ST7789_Color565(i, 0, 0));
    }
}

void ST7789_TestFilledRoundRects(ST7789 *st7789) {
    // Test filled round rectangles
    int i, i2,
        cx = st7789->width  / 2 - 1,
        cy = st7789->height / 2 - 1;

    ST7789_FillScreen(st7789, ST7789_BLACK);

    for(i=min(st7789->width, st7789->height); i>20; i-=6) {
        i2 = i / 2;
        ST7789_FillRoundRect(st7789, cx-i2, cy-i2, i, i, i/8, ST7789_Color565(0, i, 0));
    }
}

/* [] END OF FILE */
