
class Adafruit_DotStar;

// DATAPIN and CLOCKPIN can usually be any two pins
enum
{
	NUMPIXELS = 60,
	DATAPIN = 4,
	CLOCKPIN = 5,
	MAX_BRIGHTNESS = 255
};

Adafruit_DotStar stripInit();
void ledRunning(bool isColored, int delayTimeInMs);
void ledBlinking(bool isColored);