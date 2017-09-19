#include "driver.h"
#include "text.h"
#include "countdown.h"
#include "starfield.h"
#include "daleks.h"

void setup()
{    
  ledsetup();
  clear();
}

void showDick(unsigned int msdelay = 200)
{
  clear();
  showStaticText("                8====D~~~~~", msdelay);
  clear();
}

void scrollWelcome()
{
  const char* welcome = "The Betty Brinn Children's Museum and Milwaukee Makerspace Welcome You To Maker Faire Milwaukee";
  scrollText(welcome);
}

void showSponsors()
{
  // 57 characters with space in front and end
  //     " 123456789012345678901234567890123456789012345678901234567 "
  //     "                                                           "

  const char* sponsors = "Maker Faires are happening in 41 countries around the globe and all over the United States!  Thanks to our sponsors, supporters and volunteers, Maker Faire Milwaukee is one of the biggest Faires in the world.";
  scrollText(sponsors);

  const char* sponsor1 =  "         Silversmith Sponsor * Rockwell Automation         ";
  showStaticText(sponsor1);

  const char* sponsor2 =  "               Nerdy Derby Sponsor * Kohl's                ";
  showStaticText(sponsor2);

  const char* sponsor3 =  " Field Trip Friday Sponsor * Harley-Davidson Motor Company ";
  showStaticText(sponsor3);

  const char* sponsor4 =  " Thanks to Harvest Fair for sharing their grounds with us! ";
  showStaticText(sponsor4);
}

void showAbout()
{
  const char* text = "This NeoPixel sign was designed and built by Marcin Polewski from Milwaukee Makerspace with an Arduino Uno connected to 2,492 LEDs using the bit banging technique. See the Milwaukee Makerspace booth in the light room for more info.";
  scrollText(text, true);
}

void scrollDarkness()
{
  const char* darkness =  "ENTER THE DARKNESS: The Knight vs. Tesla * Music * Digital Technology * Games * High Voltage Devices * Lasers and Optics * Black Light Exhibits";
  scrollText(darkness, true);
}

void loop()
{
  scrollWelcome();
  showStarField();
  showSponsors();

  showDarkness();
  showDarkness();

  showCountDown();
  showAltText(" BUILD - LEARN - CRAFT - MEET - MAKE !!");

  showAbout();
  showAbout();
}

