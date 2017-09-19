#pragma once
#include "driver.h"

#define SCROLL_DEBUG 0
#define SCROLL_DELAY 10
#define SCROLL_DEBUG_VALUE altGradient

#define SCROLL_MAX_BRIGHTNESS 0xFF
#define SCROLL_MIN_BRIGHTNESS 0x00
#define SCROLL_STEPS (SCROLL_MAX_BRIGHTNESS - SCROLL_MIN_BRIGHTNESS)


void showAltText(const char* text)
{
  clear();
  for (unsigned int slide = 10000; slide; slide -= 10)
  {
      altbright = (slide & 0xFF);
      cli();      
      sendStringAlt(text);
      sei();
      show();
  } 
}


void sendString(const char* text , uint8_t skip)
{
  sendString(text, skip, DODGER_R, DODGER_G, DODGER_B);
}


void showStaticText(const char* text, unsigned int delayms = 6000)
{
  cli();
  sendString(text, 0, DODGER_R, DODGER_G, DODGER_B);
  sei();
  show();
  delay(delayms);
}


void scrollText(const char* text, bool useGradient = false)
{
  unsigned long time_ms = millis();

  uint8_t sector = 0;
  uint8_t step = 0;

  int pad = PIXELS - FONT_WIDTH;
  while (pad-- > 0)
  {    
    cli();
  
    for (int i = 0; i < pad; ++i)
    {
      sendRowRGB(0, 0, 0, 0);
    }

    if (step == SCROLL_STEPS)
    {
      step = 0;
      sector++;
      if (sector == 3)
      {
        sector = 0;
      }
    }
    else
    {
      step++;
    }

    uint8_t rampup = SCROLL_MIN_BRIGHTNESS + step;
    uint8_t rampdown = SCROLL_MIN_BRIGHTNESS + (SCROLL_STEPS - step); 

    uint8_t r, g, b;

    switch (sector)
    {
      case 0: 
        r = rampup;
        g = rampdown;
        b = SCROLL_MIN_BRIGHTNESS;
        break;

      case 1:
        r = rampdown;
        g = SCROLL_MIN_BRIGHTNESS;
        b = rampup;
        break;

      case 2:
        r = SCROLL_MIN_BRIGHTNESS;
        g = rampup;
        b = rampdown;
        break;
    };

    if (useGradient)
      sendString(text, 0, r, g, b);
    else
      sendString(text, 0);
  
    sei();
  
    unsigned long diff = millis() - time_ms;
    if (diff < SCROLL_DELAY)
    {
      delay(SCROLL_DELAY - diff);
      time_ms = millis();
    }

#if SCROLL_DEBUG
    uint8_t digit1 = SCROLL_DEBUG_VALUE / 100;
    uint8_t digit2 = (SCROLL_DEBUG_VALUE - (digit1 * 100)) / 10;
    uint8_t digit3 = (SCROLL_DEBUG_VALUE - (digit1 * 100) - (digit2 * 10));

    uint8_t char1 = digit1 + '0';
    uint8_t char2 = digit2 + '0';
    uint8_t char3 = digit3 + '0';

    cli();
    sendChar(' ', 0, 0xFF, 0, 0);
    sendChar(char1, 0, 0xFF, 0, 0);
    sendChar(char2, 0, 0xFF, 0, 0);
    sendChar(char3, 0, 0xFF, 0, 0);
    sendChar(' ', 0, 0xFF, 0, 0);
    sei();

    show();
#endif
  }

  while (*text)
  {
    if (step == SCROLL_STEPS)
    {
      step = 0;
      sector++;
      if (sector == 3)
      {
        sector = 0;
      }
    }
    else
    {
      step++;
    }

    uint8_t rampup = SCROLL_MIN_BRIGHTNESS + step;
    uint8_t rampdown = SCROLL_MIN_BRIGHTNESS + (SCROLL_STEPS - step); 

    uint8_t r, g, b;

    switch (sector)
    {
      case 0: 
        r = rampup;
        g = rampdown;
        b = SCROLL_MIN_BRIGHTNESS;
        break;

      case 1:
        r = rampdown;
        g = SCROLL_MIN_BRIGHTNESS;
        b = rampup;
        break;

      case 2:
        r = SCROLL_MIN_BRIGHTNESS;
        g = rampup;
        b = rampdown;
        break;
    };

    // step though each column of the 1st char for smooth scrolling
    for (uint8_t skip = 0; skip < FONT_WIDTH + INTERCHAR_SPACE; skip++)
    {
      cli();
  
      if (useGradient)
        sendString(text, skip, r, g, b);
      else
        sendString(text, skip);
      
      sei();

      unsigned long diff = millis() - time_ms;
      if (diff < SCROLL_DELAY)
      {
        delay(SCROLL_DELAY - diff);
        time_ms = millis();
      }

#if SCROLL_DEBUG
      uint8_t digit1 = SCROLL_DEBUG_VALUE / 100;
      uint8_t digit2 = (SCROLL_DEBUG_VALUE - (digit1 * 100)) / 10;
      uint8_t digit3 = (SCROLL_DEBUG_VALUE - (digit1 * 100) - (digit2 * 10));
  
      uint8_t char1 = digit1 + '0';
      uint8_t char2 = digit2 + '0';
      uint8_t char3 = digit3 + '0';
  
      cli();
      sendChar(' ', 0, 0xFF, 0, 0);
      sendChar(char1, 0, 0xFF, 0, 0);
      sendChar(char2, 0, 0xFF, 0, 0);
      sendChar(char3, 0, 0xFF, 0, 0);
      sendChar(' ', 0, 0xFF, 0, 0);
      sei();

      show();
#endif

    }

    text++;
  }
}

