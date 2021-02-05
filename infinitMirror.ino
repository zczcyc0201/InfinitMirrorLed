#include <Adafruit_NeoPixel.h>
#include "stdlib.h"
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN D5
#define NUMPIXELS 45

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 200

void setup()
{
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
    pixels.setBrightness(250);
    pixels.begin();
}

//三种颜色显示切换效果
char targetNumA = 0;
char targetNumB = 1;
char targetNumC = 2;
void modelRGB(int repeatTimes)
{
    for (int t = 0; t < repeatTimes; t++)
    {
        pixels.clear();
        for (int i = 0; i < NUMPIXELS; i++)
        {
            if (i % 3 == targetNumA)
            {
                pixels.setPixelColor(i, getRandomColor());
            }
            else if (i % 3 == targetNumB)
            {
                pixels.setPixelColor(i, getRandomColor());
            }
            else if (i % 3 == targetNumC)
            {
                pixels.setPixelColor(i, getRandomColor());
            }
        }

        if (targetNumA == 0)
        {
            targetNumA = 1;
            targetNumB = 2;
            targetNumC = 0;
        }
        else if (targetNumA == 1)
        {
            targetNumA = 2;
            targetNumB = 0;
            targetNumC = 1;
        }
        else if (targetNumA == 2)
        {
            targetNumA = 0;
            targetNumB = 1;
            targetNumC = 2;
        }
        pixels.show();
        delay(300);
    }
}
uint32_t getRandomColor()
{
    return pixels.Color((rand() % 255 + 1), (rand() % 255 + 1), (rand() % 255 + 1));
}
//随机颜色转圈圈效果
void modelCircle(bool isSeq, int repeatTimes)
{

    for (int t = 0; t < repeatTimes; t++)
    {
        pixels.clear();
        for (int i = 0; i < NUMPIXELS; i++)
        {
            if (isSeq == false && i % 5 == 0)
            {
                pixels.clear();
            }
            pixels.setPixelColor(i, getRandomColor());
            pixels.show();
            delay(50);
        }
    }
}
//随机显示20颗随机颜色效果
void modelRandom(int repeatTimes)
{

    for (int t = 0; t < repeatTimes; t++)
    {
        pixels.clear();
        //随即闪烁20个单体led 然后全体闪烁3次
        for (int i = 0; i < 20; i++)
        {
            int randLed = rand() % NUMPIXELS + 1;
            pixels.setPixelColor(randLed, getRandomColor());
            pixels.show();
            delay(50);
        }
        pixels.clear();
        //全体闪烁
        for (int a = 0; a < 3; a++)
        {
            for (int i = 0; i < NUMPIXELS; i++)
            {
                pixels.setPixelColor(i, getRandomColor());
            }
            pixels.show();
            delay(300);
            pixels.clear();
        }
    }
}

//随机显示20颗随机颜色效果
void showPureColor(uint32_t color, int delayTime)
{
    pixels.clear();
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, color);
    }
    pixels.show();
    delay(delayTime);
}

void loop()
{
    //颜色切换显示效果
    modelRGB(12);
    modelRandom(3);
    modelCircle(true, 3);
    showPureColor(getRandomColor(),3000);
}