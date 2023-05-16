/**
* @brief Main program for ST7789 graphics test.
* 
* @author Davide Marzorati
* @date April 12, 2019
*/
#include "project.h"
#include "dragon.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ST7789 st7789;
    SPIM_1_Start();
    UART_1_Start();
    UART_1_PutString("ST7789 Test!\r\n");
    
    ST7789_Start(&st7789);
    ST7789_SetRotation(&st7789, 3);
 
    for(;;)
    {
        /* Place your application code here. */
        for(uint8_t r=0; r<4; r++) {
            ST7789_SetRotation(&st7789, r);
            ST7789_FillScreen(&st7789,ST7789_BLACK);
            for(uint8_t j=1; j<20; j++) {
                ST7789_DrawRGBBitmap(
                    &st7789,
                    20 + j * (r + 3), // just some "randomness" - it will always be the same
                    40 + ( r + 2 ) * (j + 4), // just some "randomness" - it will always be the same
                    (uint16_t *)dragonBitmap,
                    DRAGON_WIDTH, DRAGON_HEIGHT);
                CyDelay(1); // Allow ESP8266 to handle watchdog & WiFi stuff
            }
            CyDelay(3000);
        }
    }
    
    for(;;)
    {
        /* Place your application code here. */
    }
}



/* [] END OF FILE */
