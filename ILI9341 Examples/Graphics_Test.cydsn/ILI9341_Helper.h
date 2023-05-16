/** 
 * @file ST7789_Helper.h
 * @brief File containing function declarations to test the ST7789.
 * 
 * @author Davide Marzorati
*/

#ifndef __ST7789_HELPER
    #define __ST7789_HELPER
    
    #include "cytypes.h"
    #include "ST7789.h"
    #include "ST7789_GFX.h"
    
    /**
    * @brief Test fill screen on the display with several colors.
    * @param st7789 ST7789 object.
    */
    void ST7789_TestFillScreen(ST7789 *st7789);
    
    /**
    * @brief Test lines on the display. Normal mode.
    * @param st7789: ST7789 object.
    * @param color: color of the lines
    */
    void ST7789_TestLines(ST7789 *st7789,uint16_t color);
    
    /**
    * @brief Test lines on the display. Fast mode.
    * @param st7789: ST7789 object.
    * @param color1: color of first lines
    * @param color2: color of second lines
    */
    void ST7789_TestFastLines(ST7789 *st7789,
                               uint16_t color1,
                               uint16_t color2);
    
    /**
    * @brief Test rectangles on the display.
    * @param st7789: ST7789 object.
    * @param color: color of the rectangles
    */
    void ST7789_TestRects(ST7789 *st7789,uint16_t color);
    
    /**
    * @brief Test filled rectangles on the display.
    * @param st7789: ST7789 object.
    * @param color1: edge color
    * @param color2: fill color
    */
    void ST7789_TestFilledRects(ST7789 *st7789,
                                 uint16_t color1,
                                 uint16_t color2);
    
    /**
    * @brief Test filled circles on the display.
    * @param st7789: ST7789 object.
    * @param radius: radius of the circles
    * @param color: color of the circles
    */
    void ST7789_TestFilledCircles(ST7789 *st7789,
                                   uint8_t radius, 
                                   uint16_t color);
    
    /**
    * @brief Test cicles on the display.
    * @param st7789: ST7789 object.
    * @param radius: radius of the circles.
    * @param color: color of the circles
    */
    void ST7789_TestCircles(ST7789 *st7789,
                             uint8_t radius, 
                             uint16_t color);
    
    /**
    * @brief Test triangles on the display.
    * @param st7789: ST7789 object.
    */
    void ST7789_TestTriangles(ST7789 *st7789);
    
    /**
    * @brief Test filled triangles on the display.
    * @param st7789: ST7789 object.
    */
    void ST7789_TestFilledTriangles(ST7789 *st7789);
    
    /**
    * @brief Test round rectangles on the display.
    * @param st7789: ST7789 object.
    */
    void ST7789_TestRoundRects(ST7789 *st7789);
    
    /**
    * @brief Test filled round rectangles on the display.
    * @param st7789: ST7789 object.
    */
    void ST7789_TestFilledRoundRects(ST7789 *st7789);

#endif

/* [] END OF FILE */
