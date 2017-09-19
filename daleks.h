#pragma once
#include "gamma.h"

#define DALEK_R GAMMA(0x20)
#define DALEK_G GAMMA(0x60)
#define DALEK_B GAMMA(0x40)

#define PHAZOR_R GAMMA(0x60)
#define PHAZOR_G GAMMA(0x00)
#define PHAZOR_B GAMMA(0x00)

#define EXPLODE_R GAMMA(0xFF)
#define EXPLODE_G GAMMA(0x8C)
#define EXPLODE_B GAMMA(0x00)

#define PHASER_LEN 10

#define DALEKS_9W_WIDTH 9
#define DALEKS_9W_DALEK 0
#define DALEKS_9W_EXPLODE 1

#define ENIMIES_WIDTH 12

const uint8_t enimies[] PROGMEM =
{
  0x70,0xf4,0xfe,0xda,0xd8,0xf4,0xf4,0xd8,0xda,0xfe,0xf4,0x70, // Enimie 1 - open
  0x72,0xf2,0xf4,0xdc,0xd8,0xf4,0xf4,0xd8,0xdc,0xf4,0xf2,0x72, // Enimie 1 - close
  0x1c,0x30,0x7c,0xda,0x7a,0x78,0x7a,0xda,0x7c,0x30,0x1c,0x00, // Enimie 2 - open
  0xf0,0x3a,0x7c,0xd8,0x78,0x78,0x78,0xd8,0x7c,0x3a,0xf0,0x00, // Enimie 2 - closed
  0x92,0x54,0x10,0x82,0x44,0x00,0x00,0x44,0x82,0x10,0x54,0x92, // Explosion
};

const uint8_t daleks_9w[] PROGMEM =
{
  // dalek facing right
  0b00000110,
  0b00001110,
  0b01111110,
  0b11111010,
  0b11111010,
  0b01111110,
  0b00101110,
  0b00100110,
  0b01010000,

  // explode
  0b00000000,
  0b00000000,
  0b00100000,
  0b10101000,
  0b01110000,
  0b10101000,
  0b00100000,
  0b00000000,
  0b00000000,
};

#if 0

const uint8_t daleks_old[] PROGMEM =
{
  // dalek v1
  0b01110000,
  0b00100000,
  0b00100110,
  0b01111110,
  0b11111010,
  0b01111110,
  0b00000110,
  0b00000000,

  // dalek v2
  0b00000000,
  0b01110000,
  0b00100110,
  0b01111110,
  0b11111010,
  0b01111110,
  0b00000110,
  0b00000000,

  // dalek v3 facing left
  0b01010000,
  0b00100110,
  0b00100110,
  0b01111110,
  0b11111010,
  0b01111110,
  0b00000110,
  0b00000110,

  // dalek v3 facing right
  0b00000110,
  0b00001110,
  0b01111110,
  0b11111010,
  0b01111110,
  0b00101110,
  0b00100110,
  0b01010000,

  // phazor
  0b00100000,
  0b00000000,
  0b00100000,
  0b00000000,
  0b00100000,
  0b00000000,
  0b00100000,
  0b00000000,

  // explode v1
  0b00000000,
  0b00100000,
  0b01110000,
  0b11111000,
  0b01110000,
  0b00100000,
  0b00000000,
  0b00000000,

  // explode v2
  0b00100000,
  0b10101000,
  0b01110000,
  0b10101000,
  0b00100000,
  0b00000000,
  0b00000000,
  0b00000000,
};

#endif

#define PHASER_WIDTH      3
#define DALEK_MOVE        10
#define SCENE_LEN_PHASER  15
#define SCENE_LEN_HIT     5
#define SCENE_LEN_EXPLODE 10
#define SCENE_LEN_TOTAL (SCENE_LEN_PHASER + SCENE_LEN_HIT + SCENE_LEN_EXPLODE)

void showDarkness()
{
  const char* prefix = "ENTER THE DARKNESS: ";

  unsigned int count = 700;
  while (count-- > 0)
  {    
    uint8_t brightness = GAMMA( ((count % 100) * 0xFF)  / 100 );

    uint8_t explode_r = GAMMA( 0xFF - ((count % 100) * 0xFF)  / 100 );
    uint8_t explode_g = GAMMA( 0x8C - ((count % 100) * 0x8C)  / 100 );
    uint8_t explode_b = GAMMA( 0x00 - ((count % 100) * 0x00)  / 100 );

    uint8_t phaser_i = SCENE_LEN_PHASER - ((count % 100) * SCENE_LEN_PHASER / 100);
    uint8_t scene_i = SCENE_LEN_TOTAL - ((count % 100) * SCENE_LEN_TOTAL / 100);

    cli();

    sendString("    ", 0, 0xFF, 0, 0);

    sendIcon(daleks_9w, DALEKS_9W_DALEK, 0, DALEKS_9W_WIDTH, DALEK_R, DALEK_G, DALEK_B);

    if (scene_i < SCENE_LEN_PHASER)
    {
      for (uint8_t skip = 0; skip < scene_i; skip++)
      {
        sendRowRGB(0, 0, 0, 0);
      }

      for (uint8_t phaser = 0; phaser < PHASER_WIDTH; phaser++)
      {
        sendRowRGB(0b00100000, PHAZOR_R, PHAZOR_G, PHAZOR_B);
      }

      for (uint8_t skip = 0; skip < SCENE_LEN_PHASER - scene_i; skip++)
      {
        sendRowRGB(0, 0, 0, 0);
      }

      for (uint8_t moveLeft = 0; moveLeft < SCENE_LEN_PHASER - scene_i; moveLeft++)
      {
        sendRowRGB(0, 0, 0, 0);
      }

      sendIcon(enimies, 2, 0, ENIMIES_WIDTH, GAMMA(0x99), GAMMA(0x99), GAMMA(0x00));
      sendRowRGB(0, 0, 0, 0);

      for (uint8_t moveRight = 0; moveRight < scene_i; moveRight++)
      {
        sendRowRGB(0, 0, 0, 0);
      }
    }
    else
    {
      for (uint8_t skip = 0; skip < SCENE_LEN_PHASER; skip++)
      {
        sendRowRGB(0, 0, 0, 0);
      }
      for (uint8_t phaser = 0; phaser < PHASER_WIDTH; phaser++)
      {
        sendRowRGB(0, 0, 0, 0);
      }

      if (scene_i < SCENE_LEN_PHASER + SCENE_LEN_HIT)
      {
        int8_t shift = scene_i % 2;

        if (shift == 0)
        {
          sendRowRGB(0, 0, 0, 0);
        }

        sendIcon(enimies, 3, 0, ENIMIES_WIDTH, explode_r, explode_g, explode_b);

        if (shift == 1)
        {
          sendRowRGB(0, 0, 0, 0);
        }

        for (uint8_t skip = 0; skip < SCENE_LEN_PHASER; skip++)
        {
          sendRowRGB(0, 0, 0, 0);
        }
      }
      else
      {
        sendIcon(enimies, 4, 0, ENIMIES_WIDTH, explode_r, explode_g, explode_b);
        sendRowRGB(0, 0, 0, 0);

        for (uint8_t skip = 0; skip < SCENE_LEN_PHASER; skip++)
        {
          sendRowRGB(0, 0, 0, 0);
        }
      }
    }

    sendString(prefix, 0, DODGER_R, 0, DODGER_B);

    // the extra spaces to the right are required to delay each message equally

    if (count > 600)
    {
      const char* text = "The Knight vs. Tesla                                              ";
      sendString(text, 0, brightness, brightness, brightness);
    }
    else if (count > 500)
    {
      const char* text = "Music                                                             ";
      sendString(text, 0, brightness, brightness, brightness);
    }
    else if (count > 400)
    {
      const char* text = "Digital Technology                                                 ";
      sendString(text, 0, brightness, brightness, brightness);
    }
    else if (count > 300)
    {
      const char* text = "Games                                                              ";
      sendString(text, 0, brightness, brightness, brightness);
    }
    else if (count > 200)
    {
      const char* text = "High Voltage Devices                                               ";
      sendString(text, 0, brightness, brightness, brightness);
    }
    else if (count > 100)
    {
      const char* text = "Lasers and Optics                                                  ";
      sendString(text, 0, brightness, brightness, brightness);
    }
    else if (count > 0)
    {
      const char* text = "Black Light Exhibits                                               ";
      sendString(text, 0, brightness, brightness, brightness);
    }

    sei();
    show();
  }
}

