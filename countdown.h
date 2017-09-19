#pragma once
#include "gamma.h"

inline void showCountDown()
{
  clear();

  const char* text = "                 THE MAKING BEGINS IN ";

  unsigned int count = 600; 
  while (count-- > 0)
  {
    uint8_t digit1 = count / 100;
    uint8_t digit2 = (count - (digit1 * 100)) / 10;
    uint8_t digit3 = (count - (digit1 * 100) - (digit2 * 10));

    uint8_t char1 = digit1 + '0';
    uint8_t char2 = digit2 + '0';
    uint8_t char3 = digit3 + '0';
    
    uint8_t brightness = GAMMA( ((count % 100) * 256)  / 100 );

    cli();
    sendString( text , 1 , brightness , brightness , brightness );      
 
    sendRowRGB( 0x00 , 0 , 0 , 0xff );
    sendChar( char1 , 0 , 0x80, 0 , 0 );
    sendChar( '.'   , 0 , 0x80, 0 , 0  );
    sendChar( char2 , 0 , 0x80, 0 , 0  );
    sendChar( char3 , 0 , 0x80, 0 , 0 );
    
    sei();
    show();
  }

  // one last blink
  count = 100;
  while (count-- > 0)
  {
    uint8_t brightness = GAMMA( ((count % 100) * 256)  / 100 );

    cli();
    sendString( text , 1 , brightness , brightness , brightness );      

    sendRowRGB( 0x00 , 0 , 0 , 0xFF );   // We need to quickly send a blank byte just to keep from missing our deadlne.
    sendChar( '0' , 0 , brightness, 0 , 0 );
    sendChar( '.' , 0 , brightness, 0 , 0 );
    sendChar( '0' , 0 , brightness, 0 , 0 );
    sendChar( '0' , 0 , brightness, 0 , 0 );
 
    sei();
    show();
  }  
}

