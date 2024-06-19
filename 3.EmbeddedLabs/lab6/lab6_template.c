/*
  EECS461
  Lab 6
 */

#include "S32K144.h"
#include "eecs461.h"
#include "LPIT.h"
#include "LPUART.h"
#include "qd.h"
#include "pwm.h"
#include "worlds.h"
#define LPIT0_CHANNEL  0

float angle=0;
//uint16_t iAnalog=0;
float t=0;
float d=0;
float T=0.001;
float J_global=0.45,K_global=17.78;

void wallDamper(void)
{
  float velocity=0.0;
  static float prevang=0;
	/* ISR for the wall-damper system */
  angle=updateAngle();
  velocity = (angle - prevang)/T;
  prevang = angle;

  t= virtualWallDamper(angle,velocity);
  outputTorque(t);

  /* Make sure to clear interrupt flag */
  clearFlagLPIT(WORLDISR_LPIT_CHANNEL);


}

void springDamper(void)
{
	/* ISR for the spring-damper system */

  /*  Make sure to clear interrupt flag  */
  float velocity=0.0;
    static float prevang=0;
    /* ISR for the wall-damper system */
    angle=updateAngle();
    velocity = (angle - prevang)/T;
    prevang = angle;

    t= virtualSpringDamper(angle,velocity);
    outputTorque(t);

    /* Make sure to clear interrupt flag */
    clearFlagLPIT(WORLDISR_LPIT_CHANNEL);

}

void springMass(void)
{
	/* ISR for the spring-mass system */

  /* Make sure to clear interrupt flag */
  float velocity=0.0;
      static float prevang=0;
      /* ISR for the wall-damper system */
      angle=updateAngle();
      velocity = (angle - prevang)/T;
      prevang = angle;

      t= virtualSpringMass(angle);
      outputTorque(t);

      /* Make sure to clear interrupt flag */
      clearFlagLPIT(WORLDISR_LPIT_CHANNEL);

}

void springMassDamper(void)
{
	/* ISR for the spring-mass-damper system */

  /* Make sure to clear interrupt flag  */
  float velocity=0.0;
        static float prevang=0;
        /* ISR for the wall-damper system */
        angle=updateAngle();
        velocity = (angle - prevang)/T;
        prevang = angle;

        t= virtualSpringMassDamper(angle,velocity);
        outputTorque(t);

        /* Make sure to clear interrupt flag */
        clearFlagLPIT(WORLDISR_LPIT_CHANNEL);

}


void springMassDamperdynamic(void)
{
  /* ISR for the spring-mass-damper system */

  /* Make sure to clear interrupt flag  */
  float velocity=0.0;
        static float prevang=0;
        /* ISR for the wall-damper system */
        angle=updateAngle();
        velocity = (angle - prevang)/T;
        prevang = angle;

        t= virtualSpringMassDamperdynamic(angle,velocity,J_global,K_global);
        outputTorque(t);

        /* Make sure to clear interrupt flag */
       clearFlagLPIT(WORLDISR_LPIT_CHANNEL);

}

void knobIndents(void)
{
	/* ISR for the virtual knob system */

  /* Make sure to clear interrupt flag */
  float velocity=0.0;
         static float prevang=0;
         /* ISR for the wall-damper system */
         angle=updateAngle();
         velocity = (angle - prevang)/T;
         prevang = angle;

         t= virtualKnob(angle,velocity);
         outputTorque(t);

         /* Make sure to clear interrupt flag */
         clearFlagLPIT(WORLDISR_LPIT_CHANNEL);

}

int main(void) {
   char byte_in = 0;
  void (*interrupt)(void);
  int section = 6;

  initEECS461();
  initQD();
  enableLPIT();

  // Initialize PWMs
  initPWMPCRs();

  initPWM(MOTOR_SUBMODULE, MOTOR_CHANNEL, MOTOR_FREQUENCY, 0.5f);
  initPWM(FILTER_SUBMODULE, FILTER_CHANNEL, FILTER_FREQUENCY, 0.5f);

  if(section == 5)
  {
    LPUART1_init();
    LPUART1_transmit_string("\n\n\n\n\n\n\n\rSerial Output Enabled.");
  }
  switch(section)
  {
    case 1:
      interrupt = &wallDamper;
      break;

    case 2:
      interrupt = &springDamper;
      break;

    case 3:
      interrupt = &springMass;
      break;

    case 4:
      interrupt = &springMassDamper;
      break;

    case 5:
      interrupt = &springMassDamperdynamic;
      break;

    case 6:
      interrupt = &knobIndents;
      break;
  }

  //Fill in the arguments to initialize the appropriate interrupt routine for
  //each part of the lab. Be sure to use the correct channel specified in worlds.h
  initLPIT(WORLDISR_LPIT_CHANNEL, WORLDISR_FREQUENCY, interrupt, 0xC);

  while(1){
    if(section == 5){

      /* adjust K and M from the keyboard. Must be a critical section. */

      byte_in = LPUART1_receive_char();
      DISABLE_INTERRUPTS();

      if(byte_in=='w')
        J_global*=1.1;
      else if(byte_in == 'x')
        J_global*=0.9;
      else if(byte_in == 'a')
        K_global*=0.9;
      else if(byte_in == 'd')
        K_global*=1.1;
      ENABLE_INTERRUPTS();
    }
  }

}
