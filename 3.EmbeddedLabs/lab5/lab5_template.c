/*
 * lab5.c
 *
 *  Created on: Jan 21, 2018
 *      Author: domanico
 *      1-6-19  jfr
 */

#include "S32K144.h"
#include "eecs461.h"

#include "pwm.h"
#include "LPIT.h"
#include "adc.h"
#include "gpio.h"
#include "math.h"
#include "mylab1header.h"


#define LPIT0_CHANNEL  0
#define PWM_CLOCK_FREQ  10000000
//static GPIO_Type * gpio_base_ptrs[5] = GPIO_BASE_PTRS;
FTM_Type * FTM_MODULE1[4] = FTM_BASE_PTRS;
GPIO_mem * const gpioD = (GPIO_mem *)(BASE_GPIO + GPIOD_OFFSET);


float sineTable[10]; // Ten samples/period
int sineIndex = 0;
const float PI = 3.14159;
float val=0;
static int i =0;

double dc;
uint16_t dp1=0;
uint16_t dp2=0;
int pwm_freq=0;
uint16_t cmax  = (PWM_CLOCK_FREQ/60000) - 1;
//cthres = dutyCycle*(cmax+1);

void IsrA(void){

 	/* Turn on LED */
	writeGPIO(3, 0, 1);

	/* Read sine value */
	val = read_ADC0_single(0);

	/* Calculate PWM duty cycle */

	dp1 = readGPIO(DIP_BASE[0], DIP[0]);
	dp2 = readGPIO(DIP_BASE[1], DIP[1]);
	if (dp2 == 1)
	{   dc = 0.1 + val * 0.8 / 5000.0;  }
	else  {   dc = 0.4 + val * 0.2 / 5000.0;  }
	
	/* Set PWM frequency based on dipswitch */  
	if (dp1 == 1)
	{   pwm_freq = 60000;  }
	else  
	{   pwm_freq = 20000;  }

	/* Set PWM duty cycle and frequency */
	setPWM(0, 0, pwm_freq, dc);

	/* Turn off LED */
	writeGPIO(3, 0, 0); 

	/* Clear interrupt flag */
	clearFlagLPIT(LPIT0_CHANNEL); 


}

void IsrB(void){
  static int i =0;
  float theta;
  pwm_freq = 60000;

	/* Turn on LED */
	writeGPIO(3, 0, 1);

	/* Calculate and set PWM duty cycle */
	
	theta = 2*PI *i/10; 
	i = (i+1)%10; 
	dc = 0.5 + 0.4*sinf (theta);
	setPWM(0, 0, pwm_freq, dc);
 

	/* Turn off LED */
	writeGPIO(3, 0, 0);

	/* Clear interrupt flag */
	clearFlagLPIT(LPIT0_CHANNEL); 

}

void IsrC(void){


  gpioD->PDOR=0b1;

	dc=sineTable[i];
	i = (i+1);

	FTM_MODULE1[0]->MOD = cmax ;
	FTM_MODULE1[0]->CONTROLS[0].CnV = (dc*(cmax+1)) ;

	gpioD->PDOR=0b0;

	clearFlagLPIT(LPIT0_CHANNEL); 

}

int main(){
  static int i =0;
  initEECS461();
  enableLPIT();
  init_ADC0_single();

  initPWMPCRs();  
  initPWM(3,0,FILTER_FREQUENCY,0.5);
   initPWM(0,0,MOTOR_FREQUENCY,0.5);
  /* Initialize GPIO */
  initGPDO(LED_BASE[0], LED[0]);
  initGPDI(DIP_BASE[0], DIP[0]);
  initGPDI(DIP_BASE[1], DIP[1]);
  for (i = 0; i < 10; i++)
 {
   sineTable[i] = 0.5 + 0.4*sin(2.0*PI*i / 10.0);
  } 

  initLPIT(LPIT0_CHANNEL, 20000, &IsrA, 0xC);
  initLPIT(LPIT0_CHANNEL, 1000, &IsrB, 0xC);
  initLPIT(LPIT0_CHANNEL, 1000, &IsrC, 0xC);
  IsrC();
  while(1){
    /*Loop forever */
  };
}

