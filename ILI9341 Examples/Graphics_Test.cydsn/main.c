/**
* @brief Main program for ST7789 graphics test.
* 
* @author Davide Marzorati
* @date April 12, 2019
*/
#include "project.h"
#include "ST7789_Helper.h"


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ST7789 st7789;
    // Start the SPI Master component
    SPIM_1_Start();
    CyDelay(500);
    
    // Start the display and change default orientation
    ST7789_Start(&st7789);
    ST7789_SetRotation(&st7789, 3);

    // Test fill screen
    ST7789_TestFillScreen(&st7789);
    CyDelay(500);
    
    // Test lines
    ST7789_TestLines(&st7789,ST7789_CYAN);
    CyDelay(500);
    
    // Test lines - fast mode
    ST7789_TestFastLines(&st7789, ST7789_RED, ST7789_BLUE);
    CyDelay(500);
    
    // Test rectangles
    ST7789_TestRects(&st7789, ST7789_GREEN);
    CyDelay(500);
    
    // Test filled rectangles
    ST7789_TestFilledRects(&st7789, ST7789_YELLOW, ST7789_MAGENTA);
    CyDelay(500);
    
    // Test filled circles
    ST7789_TestFilledCircles(&st7789, 10, ST7789_MAGENTA);
    CyDelay(500);
    
    // Test circles
    ST7789_TestCircles(&st7789, 10, ST7789_WHITE);
    CyDelay(500);
    
    // Test triangles
    ST7789_TestTriangles(&st7789);
    CyDelay(500);
    
    // Test filled triangles
    ST7789_TestFilledTriangles(&st7789);
    CyDelay(500);
    
    // Test rounded rects
    ST7789_TestRoundRects(&st7789);
    CyDelay(500);
    
    // Test filled round rects
    ST7789_TestFilledRoundRects(&st7789);
    CyDelay(500);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}



/* [] END OF FILE */
