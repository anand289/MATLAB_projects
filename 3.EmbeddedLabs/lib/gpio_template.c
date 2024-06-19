/*
   gpio.c
   University of Michigan
   EECS 461, Embedded Control Systems
   General-Purpose Input/Output module
   Read Chapter 11&12 in S32K144 User's Manual

   Revision History
     2014-02-08  Yitian Chen
     2014-07-04  GPCz
     2017-03-14  RMC
     2018-03-30  Paul Domanico
 */

#include "gpio.h"

const uint8_t LED[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
const uint8_t LED_BASE[16] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
const uint8_t DIP[16] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0, 1, 2, 3, 17};
const uint8_t DIP_BASE[16] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3};

/* base: 0-4 corresponding to gpio/port groups A-E */
static GPIO_Type * gpio_base_ptrs[5] = GPIO_BASE_PTRS;
static PORT_Type * port_base_ptrs[5] = PORT_BASE_PTRS;


/******************************************************************************
 * Function:    initGPDI
 * Description: Initialize a general purpose input based on port base and pin
 ******************************************************************************/
void initGPDI(const uint8_t base, const uint8_t pin){
  /* Set the pin direction to input */
  port_base_ptrs[base]->PCR[pin]= 0b001 << 8;


  /* Set the pin configuration register */
  gpio_base_ptrs[base]->PDDR &= ~(1 << pin);                                            /* Pin Mux Alt1 for GPIO */
  /* All other bitfields to 0 */
  /* Internal pulldown or input filter are optional */
}


/******************************************************************************
 * Function:    initGPDO
 * Description: Initialize a general purpose output based on port base and pin
 ******************************************************************************/
void initGPDO(const uint8_t base, const uint8_t pin){
  /* Set the pin direction to output */
  port_base_ptrs[base]->PCR[pin]=0b001 << 8;

  /* Pin Mux Alt1 for GPIO */
  gpio_base_ptrs[base]->PDDR |= 0b1 << pin;                                               /* Pin Mux Alt1 for GPIO */
  /* All other bitfields to 0 */
}


/******************************************************************************
 * Function:    readGPIO
 * Description: Read the digital 1/0 from GPIO input register
 ******************************************************************************/
uint8_t readGPIO(const uint8_t base, const uint8_t pin){

  return((gpio_base_ptrs[base]->PDIR>>pin)&0x1);


}


/******************************************************************************
 * Function:    writeGPIO
 * Description: Write a digital 1/0 to a GPIO output
 ******************************************************************************/
void writeGPIO(const uint8_t base, const uint8_t pin, const uint8_t val){
  if(val==0)
    return(gpio_base_ptrs[base]->PDOR&=~(1 << pin));
  else
    return(gpio_base_ptrs[base]->PDOR |=(1 << pin));
  //return;
}
