/*
   worlds.c
   University of Michigan
   EECS 461, Embedded Control Systems
   Virtual Worlds

   Revision History
     2011-12-01  Jay Patel
     2014-02-24  Scott Kenyon
     2017-03-14  RMC
 */

#include "worlds.h"
#include "gpio.h"
 

//====================LAB 4================================
/***************************************************************************
 * Virtual Wall
 ***************************************************************************/
float virtualWall(float angle)
{ if(angle<0)
	return(-200*angle);
else
  return 0.0;

}
/***************************************************************************
 * Virtual Spring 
 ***************************************************************************/
float virtualSpring(float angle)
{ 
	return(-10*angle);
}

//====================LAB 6================================
/***************************************************************************
 * Virtual Spring Damper
***************************************************************************/
float virtualSpringDamper(float angle, float velocity)
{
  return(-10*angle - 0.65*velocity);
  //0.645
}

/***************************************************************************
 * Virtual Wall Damper
***************************************************************************/
float virtualWallDamper(float angle, float velocity)
{
 if(angle<0)
  return((-500*angle) - (0.9*velocity));
 else
   return 0.0;
}

/***************************************************************************
 * Virtual Spring Mass
***************************************************************************/

float virtualSpringMass(float angle)
{
  static float x1k=0,x2k=0;
  float k = 17.78;
  float J = 0.45;
  float T = 0.001;
  float x1k1, x2k1;

  x1k1 = x1k + T*x2k;
  x2k1 = (-k*T/J)*x1k + x2k + (k*T/J)*angle;

  x1k = x1k1;
  x2k = x2k1;

  return(-k*(angle - x1k));

}

/***************************************************************************
 * Virtual Spring Mass Damper
***************************************************************************/

float virtualSpringMassDamper(float angle, float velocity) 
{
  static float x1k=0,x2k=0;
  float K = 17.78;
  float J = 0.4508;
  float T = 0.001;
  float b = 0.01778;
  float x1k1, x2k1;

  x1k1 = x1k + T*x2k;
  x2k1 = (-K*T/J)*x1k + (1-(b*T/J))*x2k + (K*T/J)*angle + (b*T/J)*velocity;

  x1k = x1k1;
  x2k = x2k1;

  return(-K*(angle - x1k) - b*(velocity - x2k));
}

/***************************************************************************
 * Virtual Spring Mass Damper
***************************************************************************/

float virtualSpringMassDamperdynamic(float angle, float velocity,float J,float K)
{
  static float x1k=0,x2k=0;
  float T = 0.001;
  float b = 0.01778;
  float x1k1, x2k1;

  x1k1 = x1k + T*x2k;
  x2k1 = (-K*T/J)*x1k + (1-(b*T/J))*x2k + (K*T/J)*angle + (b*T/J)*velocity;

  x1k = x1k1;
  x2k = x2k1;

  return(-K*(angle - x1k) - b*(velocity - x2k));
}
/***************************************************************************
 * Virtual Knob
***************************************************************************/ 

float virtualKnob(float angle, float velocity) 
{     
  //There are many ways this can be implemented    
  float k = 15;
  float J = 0.45;
  float T = 0.001;
  float b = 0.1;//0.01778;
  //int ang = angle+50000;
  float ang=angle+36;
  float x=fmod((ang),72);
  ang=x-36;


  //if(abs(angle)>0)
  //{
/*    if (x < 1)
    {
      return(0);
    }
    else
    {*/
        return(-k * (ang) - (b * velocity));
 //   }
 // }
  /*else
  {
    if (x < 1)
    {
      return(0);
    }
    else
    {
    return(-k * (x) - (b * velocity));
    }

  }*/
}


