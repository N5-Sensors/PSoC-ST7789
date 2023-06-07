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

#include "`$INSTANCE_NAME`.h"
#include "`$CS_PIN`.h"
#include "`$DC_PIN`.h"
#include "`$SPI_Master`.h"

#ifndef HIGH
    #define HIGH 1
#endif
#ifndef LOW
    #define LOW 0
#endif

#define NUM_DATA_BYTES_MAX 4

/*
 * Control Pins
 * */
#define `$DC_PIN`_HIGH()   `$DC_PIN`_Write(HIGH)   ///< set DataCommand pin high
#define `$DC_PIN`_LOW()    `$DC_PIN`_Write(LOW)    ///< set DataCommand pin low
#define `$CS_PIN`_HIGH()   `$CS_PIN`_Write(HIGH)   ///< set DataCommand pin high
#define `$CS_PIN`_LOW()    `$CS_PIN`_Write(LOW)    ///< set DataCommand pin low

/*
* Software SPI Macros
*/

#define `$INSTANCE_NAME`_SPI_WRITE(v)           `$INSTANCE_NAME`_SpiWrite(v)                ///< Software SPI write 8 bits
#define `$INSTANCE_NAME`_SPI_WRITE16(s)         `$INSTANCE_NAME`_SPI_WRITE((s) >> 8); `$INSTANCE_NAME`_SPI_WRITE(s)  ///< Software SPI write 16 bits
#define `$INSTANCE_NAME`_SPI_WRITE32(l)         `$INSTANCE_NAME`_SPI_WRITE((l) >> 24); `$INSTANCE_NAME`_SPI_WRITE((l) >> 16); `$INSTANCE_NAME`_SPI_WRITE((l) >> 8); `$INSTANCE_NAME`_SPI_WRITE(l)   ///< Software SPI write 32 bits
#define `$INSTANCE_NAME`_SPI_WRITE_PIXELS(c,l)  for(uint32_t i=0; i<(l); i+=2){ `$INSTANCE_NAME`_SPI_WRITE(((uint8_t*)(c))[i+1]); `$INSTANCE_NAME`_SPI_WRITE(((uint8_t*)(c))[i]); }   ///< Software SPI write 'l' pixels (16 bits each)

/*
* Private function prototypes
*/
void        `$INSTANCE_NAME`_WriteCommand(uint8_t cmd);
void        `$INSTANCE_NAME`_SpiWrite(uint8_t data);
uint8_t     `$INSTANCE_NAME`_SpiRead(void);

/**************************************************************************/
/*!
*    @brief  Pass 8-bit (each) R,G,B, get back 16-bit packed color
*            This function converts 8-8-8 RGB data to 16-bit 5-6-5
*    @param    red   Red 8 bit color
*    @param    green Green 8 bit color
*    @param    blue  Blue 8 bit color
*    @return   Unsigned 16-bit down-sampled color in 5-6-5 format
*/
/**************************************************************************/
uint16_t `$INSTANCE_NAME`_Color565(uint8_t red, uint8_t green, uint8_t blue) {
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | ((blue & 0xF8) >> 3);
}

/**************************************************************************/
/*!
*    @brief   Sends over the SPI the register changes to the ST7789 chip
*    @param   cmdByte the command byte
*    @param   dataBytes the pointer to the data bytes
*    @param   numDataBytes the number of data bytes to send
*    
*/
/**************************************************************************/
static void sendCommand(uint8_t cmdByte, uint8_t *dataBytes, uint8_t numDataBytes)
{
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteCommand(cmdByte);
    
    for (uint8_t i = 0; i < numDataBytes; i++)
    {
        `$INSTANCE_NAME`_SpiWrite(dataBytes[i]);
    }

    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*    @brief   Initialize ST7789 chip
*    Connects to the ST7789 over SPI and sends initialization procedure commands
*    @param   st7789 ST7789 object to store width and height dimensions
*/
/**************************************************************************/
void `$INSTANCE_NAME`_Start(ST7789 *st7789)
{    
    // Software reset'
    sendCommand(`$INSTANCE_NAME`_SWRESET, NULL, 0);
    CyDelay(150);
    
    // Out of sleep mode
    sendCommand(`$INSTANCE_NAME`_SLPOUT, NULL, 0);
    CyDelay(10);

    // Set color mode
    uint8_t data[NUM_DATA_BYTES_MAX] = {
        `$INSTANCE_NAME`_RGB_INTERFACE_65K | `$INSTANCE_NAME`_COLOR_FORMAT_16
    };
    sendCommand(`$INSTANCE_NAME`_COLMOD, data, 1);
    CyDelay(10);

    // Memory access control direction
    data[0] = 1 << MADCTL_RGB_ORDER_SHIFT;
    sendCommand(`$INSTANCE_NAME`_MADCTL, data, 1);
    
    // Column address set
    data[0] = 0x00;
    data[1] = 0x00;
    data[2] = 0x00;
    data[3] = 240;
    
    sendCommand(`$INSTANCE_NAME`_CASET, data, NUM_DATA_BYTES_MAX);
    
    // Row address set
    data[0] = 0x00;
    data[1] = 0x00;
    data[2] = `$INSTANCE_NAME`_TFTHEIGHT >> 8;
    data[3] = `$INSTANCE_NAME`_TFTHEIGHT & 0xFF;
    sendCommand(`$INSTANCE_NAME`_RASET, data, NUM_DATA_BYTES_MAX);

    // hack
    sendCommand(`$INSTANCE_NAME`_INVON, NULL, 0);
    CyDelay(10);

    // Normal display on
    sendCommand(`$INSTANCE_NAME`_NORON, NULL, 0);
    CyDelay(10);

    // Main screen turn on
    sendCommand(`$INSTANCE_NAME`_DISPON, NULL, 0);
    CyDelay(10);
    
    // Set struct parameters
    st7789->rowstart = (int)((320 - `$INSTANCE_NAME`_TFTHEIGHT) / 2);
    st7789->rowstart2 = st7789->rowstart;

    st7789->colstart = (int)((240 - `$INSTANCE_NAME`_TFTWIDTH) / 2);
    st7789->colstart2 = st7789->colstart;
    st7789->width   = `$INSTANCE_NAME`_TFTWIDTH;
    st7789->height  = `$INSTANCE_NAME`_TFTHEIGHT;
    st7789->cp437   = 1;
    st7789->wrap    = 1;
    
}

/**************************************************************************/
/*!
    @brief   Set origin of (0,0) and orientation of TFT display
    @param   m  The index for rotation, from 0-3 inclusive
*/
/**************************************************************************/
void `$INSTANCE_NAME`_SetRotation(ST7789 *st7789, uint8_t m) {
    st7789->rotation = m & 3; // can't be higher than 3

    uint8_t madctl = 0;
    switch (st7789->rotation) {
        case 0:
            madctl = MADCTL_MX | MADCTL_MY | MADCTL_RGB;
            st7789->cursor_x = st7789->colstart;
            st7789->cursor_y = st7789->rowstart;
            st7789->width  = `$INSTANCE_NAME`_TFTWIDTH;
            st7789->height = `$INSTANCE_NAME`_TFTHEIGHT;
            break;
        case 1:
            madctl = MADCTL_MY | MADCTL_MV | MADCTL_RGB;
            st7789->cursor_x = st7789->rowstart;
            st7789->cursor_y = st7789->colstart2;
            st7789->width  = `$INSTANCE_NAME`_TFTHEIGHT;
            st7789->height = `$INSTANCE_NAME`_TFTWIDTH;
            break;
        case 2:
            madctl = MADCTL_RGB;
            st7789->cursor_x = st7789->colstart2;
            st7789->cursor_y = st7789->rowstart2;
            st7789->width  = `$INSTANCE_NAME`_TFTWIDTH;
            st7789->height = `$INSTANCE_NAME`_TFTHEIGHT;
            break;
        case 3:
            madctl = MADCTL_MX | MADCTL_MV | MADCTL_RGB;
            st7789->cursor_x = st7789->rowstart2;
            st7789->cursor_y = st7789->colstart;
            st7789->width  = `$INSTANCE_NAME`_TFTHEIGHT;
            st7789->height = `$INSTANCE_NAME`_TFTWIDTH;
            break;
    }

    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_MADCTL);
    `$INSTANCE_NAME`_SpiWrite(madctl);
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
    @brief   Enable/Disable display color inversion
    @param   invert True to invert, False to have normal color
*/
/**************************************************************************/
void `$INSTANCE_NAME`_InvertDisplay(uint8_t invert) {
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteCommand(invert ? `$INSTANCE_NAME`_INVON : `$INSTANCE_NAME`_INVOFF);
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
    @brief   Scroll display memory
    @param   y How many pixels to scroll display by
*/
/**************************************************************************/
void `$INSTANCE_NAME`_ScrollTo(uint16_t y) {
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_VSCRSADD);
    `$INSTANCE_NAME`_SPI_WRITE16(y);
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*   @brief   Set the "address window".
*    
*   Set the address window. The rectangle we will write to RAM with 
*   the next chunk of SPI data writes. The ST7789 will automatically 
*   wrap the data as each row is filled
*   @param   x  TFT memory 'x' origin
*   @param   y  TFT memory 'y' origin
*   @param   w  Width of rectangle
*   @param   h  Height of rectangle
*/
/**************************************************************************/
void `$INSTANCE_NAME`_SetAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    uint32_t xa = ((uint32_t) x << 16) | ( x + w - 1 );
    uint32_t ya = ((uint32_t) y << 16) | ( y + h - 1 );
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_CASET); //column addr set
    `$INSTANCE_NAME`_SPI_WRITE32(xa);
    
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_RASET); //row addr set
    `$INSTANCE_NAME`_SPI_WRITE32(ya);//y start
    
    `$INSTANCE_NAME`_WriteCommand(`$INSTANCE_NAME`_RAMWR); //write to RAM
}

/**************************************************************************/
/*!
*   @brief   Blit 1 pixel of color without setting up SPI transaction
*   @param   color 16-bits of 5-6-5 color data
*/
/**************************************************************************/
void `$INSTANCE_NAME`_PushColor(uint16_t color) {
    `$INSTANCE_NAME`_SPI_WRITE16(color);
}

/**************************************************************************/
/*
* @brief Fills the TFT display with the given color
* @param color The color to fill the screen with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_FillScreen(ST7789 *st7789, uint16_t color){
    // Fill a fullscreen rect   
    `$INSTANCE_NAME`_FillRect(st7789, 0,0, st7789->width, st7789->height, color);
}

/**************************************************************************/
/*!
*    @brief   Blit 'len' pixels of color without setting up SPI transaction
*    @param   colors Array of 16-bit 5-6-5 color data
*    @param   len Number of 16-bit pixels in colors array
*/
/**************************************************************************/
void `$INSTANCE_NAME`_WritePixels(uint16_t * colors, uint32_t len){
    `$INSTANCE_NAME`_SPI_WRITE_PIXELS((uint8_t*)colors , len * 2);
}

/**************************************************************************/
/*!
*    @brief   Blit 'len' pixels of a single color without setting up SPI transaction
*    @param   color 16-bits of 5-6-5 color data
*    @param   len Number of 16-bit pixels you want to write out with same color
*/
/**************************************************************************/
void `$INSTANCE_NAME`_WriteColor(uint16_t color, uint32_t len){

    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;
    for (uint32_t t = len; t; t--){
        `$INSTANCE_NAME`_SpiWrite(hi);
        `$INSTANCE_NAME`_SpiWrite(lo);
    }
}

// Here we have two version of WritePixel - so that we can overload it
// depending on the passed arguments

/**************************************************************************/
/*!
*   @brief  Draw a single pixel, DOES NOT set up SPI transaction
*    @param    x  TFT X location
*    @param    y  TFT Y location
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_WritePixelFull(ST7789 *st7789, int16_t x, int16_t y, uint16_t color) {
    if((x < 0) ||(x >= st7789->width) || (y < 0) || (y >= st7789->height)) return;
    `$INSTANCE_NAME`_SetAddrWindow(x,y,1,1);
    `$INSTANCE_NAME`_WriteColor(color, 1);
}

// New write pixel

void `$INSTANCE_NAME`_WritePixelFast(int16_t sw, int16_t sh, int16_t x, int16_t y, uint16_t color)
{
    if((x < 0) ||(x >= sw) || (y < 0) || (y >= sh)) return;
    `$INSTANCE_NAME`_SetAddrWindow(x,y,1,1);
    `$INSTANCE_NAME`_WriteColor(color, 1);
}
/**************************************************************************/
/*!
*   @brief  Draw a single pixel, DOES NOT set up SPI transaction
*    @param    x  TFT X location
*    @param    y  TFT Y location
*    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_WritePixelColor(uint16_t color) {
     `$INSTANCE_NAME`_SPI_WRITE16(color);
}

/**************************************************************************/
/*!
*   @brief  Fill a rectangle, DOES NOT set up SPI transaction
*   @param    x  TFT X location begin
*   @param    y  TFT Y location begin
*   @param    w  Width of rectangle
*   @param    h  Height of rectangle
*   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_WriteFillRect(ST7789 *st7789, int16_t x, int16_t y,
    int16_t w, int16_t h, uint16_t color){
    if((x >= st7789->width) || (y >= st7789->height)) return;
    int16_t x2 = x + w - 1, y2 = y + h - 1;
    if((x2 < 0) || (y2 < 0)) return;

    // Clip left/top
    if(x < 0) {
        x = 0;
        w = x2 + 1;
    }
    if(y < 0) {
        y = 0;
        h = y2 + 1;
    }

    // Clip right/bottom
    if(x2 >= st7789->width)  w = st7789->width  - x;
    if(y2 >= st7789->height) h = st7789->height - y;

    int32_t len = (int32_t)w * h;
    `$INSTANCE_NAME`_SetAddrWindow(x, y, w, h);
    `$INSTANCE_NAME`_WriteColor(color, len);
}

/**************************************************************************/
/*!
*   @brief  Draw a vertical line, DOES NOT set up SPI transaction
*   @param    x  TFT X location begin
*   @param    y  TFT Y location begin
*   @param    l  Length of line in pixels
*   @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_WriteFastVLine(ST7789 *st7789, int16_t x, int16_t y, int16_t l, uint16_t color){
    `$INSTANCE_NAME`_WriteFillRect(st7789, x, y, 1, l, color);
}

/**************************************************************************/
/*!
*   @brief  Draw a horizontal line, DOES NOT set up SPI transaction
*   @param    x  TFT X location begin
*   @param    y  TFT Y location begin
*   @param    l  Length of line in pixels
*   @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_WriteFastHLine(ST7789 *st7789, int16_t x, int16_t y, int16_t l, uint16_t color){
    `$INSTANCE_NAME`_WriteFillRect(st7789, x, y, l, 1, color);
}

/**************************************************************************/
/*!
*   @brief  Draw a single pixel, includes code for SPI transaction
*   @param    x  TFT X location
*   @param    y  TFT Y location
*   @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawPixel(ST7789 *st7789, int16_t x, int16_t y, uint16_t color){
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WritePixel(st7789, x, y, color);
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*   @brief  Draw a vertical line, includes code for SPI transaction
*   @param    x  TFT X location begin
*   @param    y  TFT Y location begin
*   @param    l  Length of line in pixels
*   @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawFastVLine(ST7789 *st7789, int16_t x, int16_t y,
        int16_t l, uint16_t color) {
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteFastVLine(st7789, x, y, l, color);
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*   @brief  Draw a horizontal line, includes code for SPI transaction
*   @param    x  TFT X location begin
*   @param    y  TFT Y location begin
*   @param    l  Length of line in pixels
*   @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawFastHLine(ST7789 *st7789, int16_t x, int16_t y,
        int16_t l, uint16_t color) {
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteFastHLine(st7789, x, y, l, color);
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*   @brief  Fill a rectangle, includes code for SPI transaction
*   @param    x  TFT X location begin
*   @param    y  TFT Y location begin
*   @param    w  Width of rectangle
*   @param    h  Height of rectangle
*   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void `$INSTANCE_NAME`_FillRect(ST7789 *st7789, int16_t x, int16_t y, int16_t w, int16_t h,
        uint16_t color) {
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteFillRect(st7789, x,y,w,h,color);
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*   @brief  Draw RGB rectangle of data from RAM to a location on screen
*   
*   Adapted from https://github.com/PaulStoffregen/ST7789_t3
*   by Marc MERLIN. See examples/pictureEmbed to use this.
*   5/6/2017: function name and arguments have changed for compatibility
*   with current GFX library and to avoid naming problems in prior
*   implementation.  Formerly drawBitmap() with arguments in different order.
*    @param    x  TFT X location begin
*    @param    y  TFT Y location begin
*    @param    pcolors Pointer to 16-bit color data
*    @param    w  Width of pcolors rectangle
*    @param    h  Height of pcolors rectangle
*/
/**************************************************************************/
void `$INSTANCE_NAME`_DrawRGBBitmap(ST7789 *st7789, int16_t x, int16_t y,
  uint16_t *pcolors, int16_t w, int16_t h) {

    int16_t x2, y2; // Lower-right coord
    if(( x             >= st7789->width ) ||      // Off-edge right
       ( y             >= st7789->height) ||      // " top
       ((x2 = (x+w-1)) <  0      ) ||      // " left
       ((y2 = (y+h-1)) <  0)     ) return; // " bottom

    int16_t bx1=0, by1=0, // Clipped top-left within bitmap
            saveW=w;      // Save original bitmap width value
    if(x < 0) { // Clip left
        w  +=  x;
        bx1 = -x;
        x   =  0;
    }
    if(y < 0) { // Clip top
        h  +=  y;
        by1 = -y;
        y   =  0;
    }
    if(x2 >= st7789->width ) w = st7789->width  - x; // Clip right
    if(y2 >= st7789->height) h = st7789->height - y; // Clip bottom

    pcolors += by1 * saveW + bx1; // Offset bitmap ptr to clipped top-left
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_SetAddrWindow(x, y, w, h); // Clipped area
    while(h--) { // For each (clipped) scanline...
      `$INSTANCE_NAME`_WritePixels(pcolors, w); // Push one (clipped) row
      pcolors += saveW; // Advance pointer by one full (unclipped) line
    }
    `$INSTANCE_NAME`_EndWrite();
}

/**************************************************************************/
/*!
*   @brief  Read 8 bits of data from ST7789 configuration memory. NOT from RAM!
*           
*   Read 8 bits of data from ST7789 configuration memory. NOT from RAM!
*   This is highly undocumented/supported, it's really a hack but kinda works?
*   @param    command  The command register to read data from
*   @param    index  The byte index into the command to read from
*   @return   Unsigned 8-bit data read from ST7789 register
*/
/**************************************************************************/
uint8_t `$INSTANCE_NAME`_ReadCommand8(uint8_t command, uint8_t index) {
    
    `$INSTANCE_NAME`_StartWrite();
    `$INSTANCE_NAME`_WriteCommand(0xD9);  // woo sekret command?
    `$INSTANCE_NAME`_SpiWrite(0x10 + index);
    `$INSTANCE_NAME`_WriteCommand(command);
    uint8_t r = `$INSTANCE_NAME`_SpiRead();
    `$INSTANCE_NAME`_EndWrite();
    return r;
}

/**************************************************************************/
/*!
*   @brief  Begin SPI transaction.
*/
/**************************************************************************/
void `$INSTANCE_NAME`_StartWrite(void){
    `$CS_PIN`_LOW();
}

/**************************************************************************/
/*!
*   @brief  End SPI transaction.
*/
/**************************************************************************/
void `$INSTANCE_NAME`_EndWrite(void){
    `$CS_PIN`_HIGH();
}

/**************************************************************************/
/* @brief Write a 8-bit data to command/register (D/C line low).
*
*  Write a 8-bit data to command/register (D/C line low). Does not set up 
*  SPI transaction.
*  @param cmd The command/register to transmit
*/
/**************************************************************************/
void `$INSTANCE_NAME`_WriteCommand(uint8_t cmd)
{ 
    `$DC_PIN`_LOW(); 
    `$INSTANCE_NAME`_SpiWrite(cmd); 
    `$DC_PIN`_HIGH();
}

/**************************************************************************/
/*!
*   @brief  Read 8-bit data via hardware or software SPI.
*    
*   Read 8-bit data via SPI. Does not set up SPI transaction.
*   @returns One byte of data from SPI
*/
/**************************************************************************/
uint8_t `$INSTANCE_NAME`_SpiRead(void) {

    return `$SPI_Master`_ReadRxData();
}

/**************************************************************************/
/*!
* @brief Write 8-bit data via SPI. 
*
* Write 8-bit data via SPI. Does not set up SPI transaction.
* @param b The byte to be transferred
*/
/**************************************************************************/
void `$INSTANCE_NAME`_SpiWrite(uint8_t b) {
    //SPIM_1_PutArray(b,1);
    `$SPI_Master`_WriteTxData(b);
    // Without this delay, SPI write operation won't work
    //while (0 != (SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE));
    CyDelayUs(1);
}

/* [] END OF FILE */

