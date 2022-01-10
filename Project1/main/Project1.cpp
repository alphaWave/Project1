/* for reference:
 * https://learn.adafruit.com/adafruit-dotstar-leds/arduino-library-us
 */

#include <stdio.h>


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "../components/Adafruit_DotStar/include/Adafruit_DotStar.h"
// #include "../components/LEDStrip/include/LEDStrip.h"

// DATAPIN and CLOCKPIN can usually be any two pins
enum
{
	NUMPIXELS = 60,
	DATAPIN = 4,
	CLOCKPIN = 5,
	MAX_BRIGHTNESS = 255
};

// This is how we declare a DotStar-object
Adafruit_DotStar myStrip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BRG);

extern "C" void app_main(void)
{
	// initArduino();

	// IF I UNCOMMENT THIS, THE PROBLEMS START HAPPENING
	// bool isColored = true;
    // ledRunning(isColored);

	myStrip.begin(); // Initialize pins for output
	myStrip.show();	 // Turn all LEDs off ASAP

	// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
	// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

	int head = 0;
	int tail = -10; // Index of first 'on' and 'off' pixels
	int brightness = 10;
	uint32_t color = 0xFF0000; // 'On' color (starts red)
	const TickType_t delay = 20 / portTICK_PERIOD_MS;

	while (1)
	{
		myStrip.setPixelColor(head, color); // 'On' pixel at head
		// myStrip.setPixelColor(head, 0xFFFFFF); // For white pixels only (makes nested if-statement superfluous)
		myStrip.setBrightness(brightness); // adjust brightness between 0 and 255
		myStrip.setPixelColor(tail, 0);	   // 'Off' pixel at tail
		myStrip.show();					   // Refresh strip
		vTaskDelay(delay);

		if (++head >= NUMPIXELS)
		{							// Increment head index.  Off end of strip?
			head = 0;				//  Yes, reset head index to start
			if ((color >>= 8) == 0) //  Next color (R->G->B) ... past blue now?
			{
				color = 0xFF0000; //   Yes, reset to red
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
