/*!
* Adafruit GFX Library adapted for PSoC MCU
* Author: Oliver Zhang
* Date: May 17, 2023
* 
* Written for Arduino platform by Limor "ladyada" Fried for Adafruit Industries.
*
* BSD license, all text here must be included in any redistribution.
*
*/

#ifndef ST7789_STRUCT
    #define ST7789_STRUCT
    #include "cytypes.h"
    #include "`$INSTANCE_NAME`_gfxfont.h"
     /**
     * @brief ST7789 Struct.
     *
     * This struct contains parameter useful for graphics handling.
    */

    typedef struct ST7789_Struct{
        int16_t        
            cursor_x,       ///< x location to start print()ing text
            cursor_y;       ///< y location to start print()ing text
        uint16_t
            textcolor,      ///< 16-bit background color for print()
            textbgcolor;    ///< 16-bit text color for print()
        uint8_t
            textsize,       ///< Desired magnification of text to print()
            rotation;       ///< Display rotation (0 thru 3)
        uint8_t
            wrap;           ///< If set, 'wrap' text at right edge of display
        uint16_t 
            width,          ///< Display width as modified by current rotation
            height;         ///< Display height as modified by current rotation
        uint8_t
            colstart,       ///< Some displays need this changed to offset
            rowstart,       ///< Some displays need this changed to offset
            colstart2,      ///< Offset from the right
            rowstart2;      ///< Offset from the bottom
        uint8_t cp437;      ///< If set, use correct CP437 charset (default is off)
        GFXfont *gfxFont;   ///< Pointer to special font
    } ST7789;
#endif

#ifndef _ADAFRUIT_`$INSTANCE_NAME`H_
#define _ADAFRUIT_`$INSTANCE_NAME`H_
    
#include "cytypes.h"
#include "`$INSTANCE_NAME`_gfxfont.h"

#define `$INSTANCE_NAME`_TFTWIDTH   172       ///< ST7789 max TFT width
#define `$INSTANCE_NAME`_TFTHEIGHT  320       ///< ST7789 max TFT height

#define `$INSTANCE_NAME`_CMD_DELAY  0x80

#define `$INSTANCE_NAME`_NOP        0x00      ///< No-op register
#define `$INSTANCE_NAME`_SWRESET    0x01      ///< Software reset register
#define `$INSTANCE_NAME`_RDDID      0x04      ///< Read display identification information
#define `$INSTANCE_NAME`_RDDST      0x09      ///< Read Display Status 

#define `$INSTANCE_NAME`_SLPIN      0x10      ///< Enter Sleep Mode
#define `$INSTANCE_NAME`_SLPOUT     0x11      ///< Sleep Out
#define `$INSTANCE_NAME`_PTLON      0x12      ///< Partial Mode ON
#define `$INSTANCE_NAME`_NORON      0x13      ///< Normal Display Mode ON

#define `$INSTANCE_NAME`_INVOFF     0x20      ///< Display Inversion OFF
#define `$INSTANCE_NAME`_INVON      0x21      ///< Display Inversion ON 
#define `$INSTANCE_NAME`_DISPOFF    0x28      ///< Display OFF 
#define `$INSTANCE_NAME`_DISPON     0x29      ///< Display ON
#define `$INSTANCE_NAME`_CASET      0x2A      ///< Column Address Set
#define `$INSTANCE_NAME`_RASET      0x2B      ///< Row Address Set
#define `$INSTANCE_NAME`_RAMWR      0x2C      ///< Memory Write
#define `$INSTANCE_NAME`_RAMRD      0x2E      ///< Memory Read

#define `$INSTANCE_NAME`_PTLAR      0x30      ///< Partial Area
#define `$INSTANCE_NAME`_TEOFF      0x34      ///< Tearing Effect Line OFF
#define `$INSTANCE_NAME`_TEON       0x35      ///< Teating Effect Line ON
#define `$INSTANCE_NAME`_MADCTL     0x36      ///< Memory Access Control
#define `$INSTANCE_NAME`_COLMOD     0x3A      ///< Interface Pixel Format

#define MADCTL_MY  0x80     ///< Bottom to top
#define MADCTL_MX  0x40     ///< Right to left
#define MADCTL_MV  0x20     ///< Reverse Mode
#define MADCTL_ML  0x10     ///< LCD refresh Bottom to top
#define MADCTL_RGB 0x00     ///< Red-Green-Blue pixel order

#define `$INSTANCE_NAME`_RDID1      0xDA      ///< Read ID 1
#define `$INSTANCE_NAME`_RDID2      0xDB      ///< Read ID 2
#define `$INSTANCE_NAME`_RDID3      0xDC      ///< Read ID 3
#define `$INSTANCE_NAME`_RDID4      0xDD      ///< Read ID 4

#define `$INSTANCE_NAME`_GAMMASET   0x26      ///< Gamma Set 

#define `$INSTANCE_NAME`_RDMODE     0x0A      ///< Read Display Power Mode 
#define `$INSTANCE_NAME`_RDMADCTL   0x0B      ///< Read Display MADCTL
#define `$INSTANCE_NAME`_RDPIXFMT   0x0C      ///< Read Display Pixel Format
#define `$INSTANCE_NAME`_RDIMGFMT   0x0D      ///< Read Display Image Format 
#define `$INSTANCE_NAME`_RDSELFDIAG 0x0F      ///< Read Display Self-Diagnostic Result

#define `$INSTANCE_NAME`_VSCRSADD   0x37      ///< Vertical Scrolling Start Address
#define `$INSTANCE_NAME`_PIXFMT     0x3A      ///< COLMOD: Pixel Format Set

#define `$INSTANCE_NAME`_FRMCTR1    0xB1      ///< Frame Rate Control (In Normal Mode/Full Colors)
#define `$INSTANCE_NAME`_FRMCTR2    0xB2      ///< Frame Rate Control (In Idle Mode/8 colors)
#define `$INSTANCE_NAME`_FRMCTR3    0xB3      ///< Frame Rate control (In Partial Mode/Full Colors)
#define `$INSTANCE_NAME`_INVCTR     0xB4      ///< Display Inversion Control
#define `$INSTANCE_NAME`_DFUNCTR    0xB6      ///< Display Function Control

#define `$INSTANCE_NAME`_PWCTR1     0xC0      ///< Power Control 1
#define `$INSTANCE_NAME`_PWCTR2     0xC1      ///< Power Control 2
#define `$INSTANCE_NAME`_PWCTR3     0xC2      ///< Power Control 3
#define `$INSTANCE_NAME`_PWCTR4     0xC3      ///< Power Control 4
#define `$INSTANCE_NAME`_PWCTR5     0xC4      ///< Power Control 5
#define `$INSTANCE_NAME`_VMCTR1     0xC5      ///< VCOM Control 1
#define `$INSTANCE_NAME`_VMCTR2     0xC7      ///< VCOM Control 2

#define `$INSTANCE_NAME`_GMCTRP1    0xE0      ///< Positive Gamma Correction
#define `$INSTANCE_NAME`_GMCTRN1    0xE1      ///< Negative Gamma Correction
//#define `$INSTANCE_NAME`_PWCTR6     0xFC

// COLMOD address
#define `$INSTANCE_NAME`_RGB_INTERFACE_SHIFT 4
#define `$INSTANCE_NAME`_COLOR_FORMAT_SHIFT 0

typedef enum
{
    `$INSTANCE_NAME`_RGB_INTERFACE_65K = 5 << `$INSTANCE_NAME`_RGB_INTERFACE_SHIFT,
    `$INSTANCE_NAME`_RGB_INTERFACE_262K = 6 << `$INSTANCE_NAME`_RGB_INTERFACE_SHIFT
} RGB_INTERFACE_OPTS;

typedef enum
{
    `$INSTANCE_NAME`_COLOR_FORMAT_12 = 3 << `$INSTANCE_NAME`_COLOR_FORMAT_SHIFT,
    `$INSTANCE_NAME`_COLOR_FORMAT_16 = 5 << `$INSTANCE_NAME`_COLOR_FORMAT_SHIFT,
    `$INSTANCE_NAME`_COLOR_FORMAT_18 = 6 << `$INSTANCE_NAME`_COLOR_FORMAT_SHIFT,
    `$INSTANCE_NAME`_COLOR_FORMAT_16M = 7 << `$INSTANCE_NAME`_COLOR_FORMAT_SHIFT
} COLOR_FORMAT_OPTS;

typedef enum
{
    MADCTL_LATCH_ORDER_SHIFT = 2,
    MADCTL_RGB_ORDER_SHIFT = 3,
    MADCTL_LINE_ORDER_SHIFT = 4,
    MADCTL_PAGE_COL_ORDER_SHIFT = 5,
    MADCTL_COL_ORDER_SHIFT = 6,
    MADCTL_PAGE_ORDER_SHIFT = 7
} MADCTL_SHIFTS;


// Color definitions
#define `$INSTANCE_NAME`_BLACK       0x0000      ///<   0,   0,   0
#define `$INSTANCE_NAME`_NAVY        0x000F      ///<   0,   0, 128
#define `$INSTANCE_NAME`_DARKGREEN   0x03E0      ///<   0, 128,   0
#define `$INSTANCE_NAME`_DARKCYAN    0x03EF      ///<   0, 128, 128
#define `$INSTANCE_NAME`_MAROON      0x7800      ///< 128,   0,   0
#define `$INSTANCE_NAME`_PURPLE      0x780F      ///< 128,   0, 128
#define `$INSTANCE_NAME`_OLIVE       0x7BE0      ///< 128, 128,   0
#define `$INSTANCE_NAME`_LIGHTGREY   0xC618      ///< 192, 192, 192
#define `$INSTANCE_NAME`_DARKGREY    0x7BEF      ///< 128, 128, 128
#define `$INSTANCE_NAME`_BLUE        0x001F      ///<   0,   0, 255
#define `$INSTANCE_NAME`_GREEN       0x07E0      ///<   0, 255,   0
#define `$INSTANCE_NAME`_CYAN        0x07FF      ///<   0, 255, 255
#define `$INSTANCE_NAME`_RED         0xF800      ///< 255,   0,   0
#define `$INSTANCE_NAME`_MAGENTA     0xF81F      ///< 255,   0, 255
#define `$INSTANCE_NAME`_YELLOW      0xFFE0      ///< 255, 255,   0
#define `$INSTANCE_NAME`_WHITE       0xFFFF      ///< 255, 255, 255
#define `$INSTANCE_NAME`_ORANGE      0xFD20      ///< 255, 165,   0
#define `$INSTANCE_NAME`_GREENYELLOW 0xAFE5      ///< 173, 255,  47
#define `$INSTANCE_NAME`_PINK        0xFC18      ///< 255, 128, 192

// Allow overloading of ST7789_WritePixel function
#define `$INSTANCE_NAME`_WritePixel(_1, ...) _Generic((_1),          \
                                        uint16_t: `$INSTANCE_NAME`_WritePixelColor, \
                                        default: `$INSTANCE_NAME`_WritePixelFull \
                                    )(_1, __VA_ARGS__)
                                    
    


    
void      `$INSTANCE_NAME`_Start(ST7789 *`$INSTANCE_NAME`);
void      `$INSTANCE_NAME`_SetRotation(ST7789 *`$INSTANCE_NAME`, uint8_t r);
void      `$INSTANCE_NAME`_InvertDisplay(uint8_t i);
void      `$INSTANCE_NAME`_ScrollTo(uint16_t y);

// Required Non-Transaction
void      `$INSTANCE_NAME`_DrawPixel(ST7789 *`$INSTANCE_NAME`, int16_t x, int16_t y, 
            uint16_t color);

// Transaction API
void      `$INSTANCE_NAME`_StartWrite(void);
void      `$INSTANCE_NAME`_EndWrite(void);
/*void      `$INSTANCE_NAME`_WritePixel(ST7789 *st7789, int16_t x, int16_t y, 
            uint16_t color);*/
void      `$INSTANCE_NAME`_WritePixelFull(ST7789 *st7789, int16_t x, int16_t y, 
            uint16_t color);
void      `$INSTANCE_NAME`_WriteFillRect(ST7789 *st7789, int16_t x, int16_t y,
            int16_t w, int16_t h, uint16_t color);
void      `$INSTANCE_NAME`_WriteFastVLine(ST7789 *st7789, int16_t x, int16_t y,
            int16_t h, uint16_t color);
void      `$INSTANCE_NAME`_WriteFastHLine(ST7789 *st7789, int16_t x, int16_t y,
            int16_t w, uint16_t color);

// Transaction API not used by GFX
void      `$INSTANCE_NAME`_SetAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void      `$INSTANCE_NAME`_WritePixels(uint16_t * colors, uint32_t len);
void      `$INSTANCE_NAME`_WritePixelColor(uint16_t color);
void      `$INSTANCE_NAME`_WritePixelFast(int16_t sw, int16_t sh, int16_t x, int16_t y, uint16_t color);
void      `$INSTANCE_NAME`_WriteColor(uint16_t color, uint32_t len);
void      `$INSTANCE_NAME`_PushColor(uint16_t color);

// Recommended Non-Transaction
void      `$INSTANCE_NAME`_DrawFastVLine(ST7789 *ili3941, int16_t x, int16_t y,
            int16_t h, uint16_t color);
void      `$INSTANCE_NAME`_DrawFastHLine(ST7789 *ili3941, int16_t x, int16_t y,
            int16_t w, uint16_t color);
void      `$INSTANCE_NAME`_FillRect(ST7789 *st7789, int16_t x, int16_t y,
            int16_t w, int16_t h, uint16_t color);
void      `$INSTANCE_NAME`_FillScreen(ST7789 *ili1341, uint16_t color);
void      `$INSTANCE_NAME`_DrawRGBBitmap(ST7789 *st7789, int16_t x, int16_t y,
                uint16_t *pcolors, int16_t w, int16_t h);

uint8_t   `$INSTANCE_NAME`_ReadCommand8(uint8_t reg, uint8_t index);

uint16_t  `$INSTANCE_NAME`_Color565(uint8_t r, uint8_t g, uint8_t b);

#endif





/* [] END OF FILE */
