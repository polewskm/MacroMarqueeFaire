#pragma once
#define STARFIELD_COUNT 600

void showStarField()
{

  const uint8_t field = 40;       // Good size for a field, must be less than 256 so counters fit in a byte
 
  uint8_t sectors = (PIXELS / field);      // Repeating sectors makes for more stars and faster update

  for (unsigned int i = 0; i < STARFIELD_COUNT; i++)
  {
    unsigned int r = random(PIXELS * 8);   // Random slow, so grab one big number and we will break it down.

    unsigned int x = r / 8;
    uint8_t y = r & 0x07;                // We use 7 rows
    uint8_t bitmask = (2 << y);           // Start at bit #1 since we enver use the bottom bit

    cli();

    unsigned int l = x;

    while (l--)
    {
      sendRowRGB(0, 0x00, 0x00, 0x00);
    }

    sendRowRGB(bitmask, 0x40, 0x40, 0xff);  // Starlight blue

    l = PIXELS - x;

    while (l--)
    {
      sendRowRGB(0, 0x00, 0x00, 0x00);
    }

    sei();   
  }

}

