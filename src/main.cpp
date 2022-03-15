#include <Arduino.h>
#include <led.h>

#define LED_PIN 6
#define LED_COUNT 47 // total number of NeoPixel LEDs

// NeoPixel strip object
// All pixels are 800 KHz bitstream and RGB (not RGBW)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t white = strip.Color(255, 255, 255);

void arcReactor(uint32_t);
void fade(uint32_t);

void setup()
{
    Serial.begin(9600);

    strip.begin();            // initialize NeoPixel strip object
    strip.show();             // deactivate all pixels
    strip.setBrightness(100); // control brightness level
}

void loop()
{
    fade(white);

    // do nothing
    while (!Serial.available())
        ;
}

void arcReactor(uint32_t color)
{
    int i;
    for (i = LED_COUNT; i > 0; i--)
    {
        strip.setPixelColor(i - 1, color);
        strip.show();
    }
}

void fade(uint32_t color)
{
    int i;
    arcReactor(white);
    while (1)
    {
        for (i = 98; i > 0; i -= 2)
        {
            strip.setBrightness(i);
            strip.show();
            delay(10);
        }
        for (i = 2; i <= 100; i += 2)
        {
            strip.setBrightness(i);
            strip.show();
            delay(10);
        }
    }
}