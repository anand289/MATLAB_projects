/*
  EECS461
  Lab 4
*/
#include "eecs461.h"
#include "qd.h"
#include "pwm.h"
#include "worlds.h"
#include "S32K144.h"
#include "adc.h"
#include "gpio.h"



int main(void)
{
  int section = 6;


  initEECS461();

  float angle=0;
  uint16_t iAnalog=0;
  float t=0;
  float d=0;
  
  // Initialize QD and ADC
  /* fill in */
  initQD();
  init_ADC0_single();
  initGPDO(LED_BASE[1], 1);
  // Initialize PWMs
  initPWMPCRs();
  initPWM(3,0,FILTER_FREQUENCY,0.5);
  initPWM(0,0,MOTOR_FREQUENCY,0.5);


  while(1)
  {
    switch(section)
    {
	case 1: // 0 Torque
	  outputTorque(0);
	 /* iAnalog= read_ADC0_single(0);
	  d=(0.52/4095)*iAnalog+0.24;
	  setPWM(0,0,MOTOR_FREQUENCY,d);*/
	  break;
    case 2: //Analog Input Control of PWM
      iAnalog= read_ADC0_single(0);
      d=(0.52/4095)*iAnalog+0.24;
      setPWM(0,0,MOTOR_FREQUENCY,d);
      break;
    case 3: //Change PWM Frequency to 1 kHz torque = 0 N-mm
      outputTorque(0);
      break;
    case 4: //Set torque to 200 N-mm
      outputTorque(200);
      break;
    case 5: //Virtual Spring
      writeGPIO(3, LED[1], 0b1);
      angle=updateAngle();

      t=virtualSpring(angle);
      outputTorque(t);
      writeGPIO(3, LED[1], 0b0);
      break;
    case 6: // Virtual Wall
            angle=updateAngle();
           t=virtualWall(angle);
           outputTorque(t);
      break;
    }
  }
}
