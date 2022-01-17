
#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "../components/Adafruit_DotStar/include/Adafruit_DotStar.h"
#include "../components/LEDfunctions/include/LEDfunctions.h"



extern "C" void app_main(void)
{
	bool isColored = true;
	int delayTimeInMs = 20;
	ledRunning(isColored, delayTimeInMs);
}
