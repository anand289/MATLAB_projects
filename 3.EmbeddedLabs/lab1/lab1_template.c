/*
  EECS461
  Lab 1
  Read Chapter 11&12 in S32K144 User's Manual
  Updated: March 17th, 2014 by Scott Kenyon
           14 Jun 2014 by GPCz
           19 Jun 2014 by GPCz
           2017-03 RMC
           2018-03 Paul Domanico
           15 Nov 2018 jfr
*/

#include "eecs461.h"
#include <stdint.h>

/* Change section number to match the section (1-3) being tested */
#define SECTION 3

#if SECTION == 1
#include "mylab1header.h"



/******************************************************************************
 * Function:    section1
 * Description: read and write to the GPIO registers using your header file
 ******************************************************************************/
void section1(){
  /* code for section 1 */

  volatile uint32_t * const portD_PCR = (uint32_t *)(BASE_PORTD);
  volatile uint32_t * const portE_PCR = (uint32_t *)(BASE_PORTE);
  GPIO_mem * const gpioD = (GPIO_mem *)(BASE_GPIO + GPIOD_OFFSET);
  GPIO_mem * const gpioE = (GPIO_mem *)(BASE_GPIO + GPIOE_OFFSET);
  uint16_t sum, value1, value2;
  uint32_t regReadVal;
  int i;
  /* Configure the LED pins */
  for(i = 0; i < 16; i++)
  {   /* Configure pin mux to gpio */
    portD_PCR[i] = 0b001 << 8;
    /* Set the direction to output */
    gpioD->PDDR |= 0b1 << i; }
  /* Configure the DIP pins */
  for(i = 6; i < 14; i++)
  {   /* Configure pin mux to gpio */
    portE_PCR[i] = 0b001 << 8;
    /* Set the direction to input */
    gpioE->PDDR &= ~(1 << i);
  }

  while(1)
  {   value1 = 0;
  value2 = 0;
  sum = 0;
  /* Read the GPIOE input register, extract the two 4 bit numbers       set on dipswitches 1-4 and 5-8  */
  value1=(gpioE->PDIR>>6)&0x0000000F;
  value2=(gpioE->PDIR>>10)&0x0000000F;

  /* Calculate the sum and write to the GPIOD output register         to display the results on LEDs1-5.  */
  sum=value1+value2;
   gpioD->PDOR=sum;
  }

}


#elif SECTION == 2
#include "S32K144.h"
#include "gpio.h"
/******************************************************************************
 * Function:    section2
 * Description: Use the provided S32K144.h header file
 ******************************************************************************/
void section2(){
  /* code for section 2 */
  uint16_t sum, value1, value2;
  int index;
  for(index = 0; index < 16; index++)
  {
    initGPDI(DIP_BASE[index], DIP[index]);
    initGPDO(LED_BASE[index], LED[index]);
  }
  while(1)
  {
    value1=0;
    value2=0;
    for(index = 3; index >= 0; index--)
              {
          value1 |= (readGPIO(4, DIP[index])<<index);
              }
    for(index = 7; index >= 4; index--)
          {
      value2|=(readGPIO(4, DIP[index])<<(index-4));
          }
  //value2=(readGPIO(4, 8)>>4)&0x0000000F;
  sum=value1+value2;
  for(index = 4; index >= 0; index--)
   {

    writeGPIO(3, LED[index], ((sum>>(index))&0b1));
   }

  //writeGPIO(3, 16, sum);
  /*
  for(index = 0; index <= 5; index++)
  {
    writeGPIO(3, LED[index], sum);
   }
   */

  }

}


#elif SECTION == 3
#include "LPUART.h"
#include "gpio.h"
/******************************************************************************
 * Function:    section3
 * Description: Communicate with the computer using the keyboard interface
 ******************************************************************************/
void section3(){
  /* code for section 3 */
  char byte_in, old_byte_in;
  uint16_t sum=0;
  int index;
    for(index = 0; index < 16; index++)
    {

      initGPDO(LED_BASE[index], LED[index]);
    }

  /* LPUART functions for sending and receiving serial data */
  LPUART1_init();
  LPUART1_transmit_string("\n\rSerial Output Enable...........");
  while(1) {
    old_byte_in = byte_in;
    byte_in = LPUART1_receive_char(); // returns ASCII representation
    if((byte_in)>='0' && (byte_in)<='9'&& (old_byte_in)>='0' && (old_byte_in)<='9')
    {
      sum=(byte_in & 0xF) + ((old_byte_in & 0xF) & 0b1111);
    }
    for(index = 4; index >= 0; index--)
       {

        writeGPIO(3, LED[index], ((sum>>(index))&0b1));
       }



  }
}
#endif

int main(){
  /* Always call  before doing anything else */
  initEECS461();
  #if(SECTION == 1)
  section1();
  #elif(SECTION == 2)
  section2();
  #elif(SECTION == 3)
  section3();
  #endif

  /* Should never reach this point */
  return 0;
}
