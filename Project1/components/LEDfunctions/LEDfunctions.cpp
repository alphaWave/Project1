
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "LEDfunctions.h"
#include "../Adafruit_DotStar/include/Adafruit_DotStar.h"

Adafruit_DotStar stripInit()
{
    // This is how we declare a DotStar-object
    Adafruit_DotStar myStrip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
    // The last parameter is optional -- this is the color data order of the
    // DotStar strip, which has changed over time in different production runs.
    // Your code just uses R,G,B colors, the library then reassigns as needed.
    // Default is DOTSTAR_BRG, so change this if you have an earlier strip.

    // Hardware SPI is a little faster, but must be wired to specific pins
    // (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
    // Adafruit_DotStar myStrip(NUMPIXELS, DOTSTAR_BRG);

    myStrip.begin(); // Initialize pins for output
    myStrip.show();  // Turn all LEDs off ASAP

    return myStrip;
}

void ledRunning(bool isColored, int delayTimeInMs)
{
    Adafruit_DotStar myStrip = stripInit();

    int head = 0;
    int tail = -10; // Index of first 'on' and 'off' pixels
    int brightness = 10;
    int32_t color = 0xFFFFFF; // initialize LEDs with white
    if (isColored)
    {
        color = 0xFF0000; // 'On' color (starts red)
    }
    const TickType_t delay = delayTimeInMs / portTICK_PERIOD_MS;

    while (1)
    {
        myStrip.setPixelColor(head, color); // 'On' pixel at head
        myStrip.setBrightness(brightness);  // adjust brightness between 0 and 255
        myStrip.setPixelColor(tail, 0);     // 'Off' pixel at tail
        myStrip.show();                     // Refresh strip
        vTaskDelay(delay);

        if (++head >= NUMPIXELS)
        {                                          // Increment head index.  Off end of strip?
            head = 0;                              //  Yes, reset head index to start
            if (isColored && ((color >>= 8) == 0)) //  Next color (R->G->B) ... past blue now?
            {
                color = 0xFF0000; // Yes, reset to red
            }
        }
        if (++tail >= NUMPIXELS)
        {
            tail = 0; // Increment, reset tail index
        }
        if ((0 == head) && ((brightness = brightness + 10) > MAX_BRIGHTNESS))
        {
            brightness = 1;
        }
    }
}
