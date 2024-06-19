
#include "eecs461.h"
#include "S32K144.h"
#include "adc.h"
#include "gpio.h"
#include "LPUART.h"
#include "s32_core_cm4.h"
#include "interrupt_manager.h"


int main(void) {
  uint16_t iAnalog=0;

  initEECS461();
  //init_ADC0_single();

  init_ADC0_single();
 // initGPDO(LED_BASE[1], 1);


  while (1) {
    //writeGPIO(3, LED[1], 0b1);
    iAnalog= read_ADC0_single(0);
   //if(iAnalog>=4095/2)
  // writeGPIO(3, LED[1], 0b1);
  // else
   //  writeGPIO(3, LED[1], 0b0);

  }

  return 0;
}


