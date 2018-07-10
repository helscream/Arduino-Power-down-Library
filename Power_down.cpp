/* Author = helscream (Omer Ikram ul Haq)
Last edit date = 2015-04-05
Website: http://hobbylogs.me.pn/?p=339
Location: Pakistan
Ver: 0.1 beta --- Start
*/

#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "Power_down.h"
/*****************************************************************************
* Power Down rotuine
*****************************************************************************/
void Power_down(unsigned int T){
  
  /*         7      6      5      4       3          2      1     0
   MCUSR =   -      -      -      -   WD Reset Flag BORF  EXTRF  PORF  (Micro Controller Status Register)
   WDTCSR=  WDIF   WDIE  WDP3    WDCE    WDE       WDP2    WDP1  WDP0
   
   WDE   WDIE           Mode            Action on Time-out
    0      0            Stopped         None
    0      1            Interrupt Mode  Interrupt
    1      0            System Reset    Reset
    1      1            INT + Reset     Interrupt and then go to system reset mode
    
    
    WDP3 WDP2 WDP1 WDP0 Time
     0    0    0    0    16ms
     0    0    0    1    32ms
     0    0    1    0    64ms
     0    0    1    1    125ms
     0    1    0    0    250ms
     0    1    0    1    500ms
     0    1    1    0    1s
     0    1    1    1    2s
     1    0    0    0    4s
     1    0    0    1    8s
    
    
    for more information lookinto http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf
  */
  
  wdt_reset();
  
  boolean will_work = false;
  unsigned int factor = 1;
  
  bitClear(MCUSR,3);          // Clear Previous Watch dog reset flag in the MCU Status register
  
  
  switch (T){
    case 1:
      // Setting for 1s
      wdt_enable(WDTO_1S);
      will_work = true;
      break;
    case 2:
      // Setting for 2s
      wdt_enable(WDTO_2S);
      will_work = true;
      break;
    case 4:
      // Setting for 4s
      wdt_enable(WDTO_4S);
      will_work = true;
      break;  
    default:
      if (T>=8){
        // Setting for 8s
        wdt_enable(WDTO_8S);
        factor = T/8;
        will_work = true;
      }else{
        will_work = false;
      }
  }
  
  
  if (will_work == true){
    while(factor >= 1){
      bitSet(WDTCSR,6);           // Enabeling WD for an interrupt
      sleep_tight();
      factor--;  
    }

  }
  wdt_disable();
  return;
}




void sleep_tight(void){
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
    sleep_enable();
  
    /* Now enter sleep mode. */
    sleep_mode();
      /* The program will continue from here after the WDT timeout*/
    sleep_disable(); /* First thing to do is disable sleep. */
    
    /* Re-enable the peripherals. */
    power_all_enable();

}


ISR(WDT_vect){

}
