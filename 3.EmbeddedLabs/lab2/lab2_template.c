/*
  EECS461
  Lab 2
  Updated: March 17th, 2014 by Scott Kenyon
           July  4th, 2014 by GPCz
           2017-03-15 RMC
           2018-03    Paul Domanico
*/


 #include "eecs461.h"
 #include "S32K144.h"
 #include "gpio.h"
 #include "qd.h"

 int main(void){
   initEECS461();

   int32_t counter = 0;
   int i;
   float angle;
   int16_t angleInt=0;
   int section = 4; //Set to case you are testing
   int index;

   /* Initialize EECS461, QD, GPDO */
   initQD();
   for(index = 0; index < 16; index++)
           {
              initGPDO(LED_BASE[index], LED[index]);
           }


   while(1){
     switch(section){
     case 1://Read the counter
    	 counter = updateCounter();
       break;

     case 2://Overflow and Underflow
       counter = updateCounter();
       for(index = 15; index >=0; index--)
          {
           writeGPIO(3, LED[index], ((counter>>(index))&0b1));
          }



       break;

     case 3: //updateCounter and Faulty Casting
       counter = updateCounter();
      counter=counter&0xFFFFFF00;
      counter=counter>>8;
              for(index = 15; index >=0; index--)
                 {
                  writeGPIO(3, LED[index], ((counter>>(index))&0b1));
                 }
       break;

     case 4: //Angle Calculation
       counter = updateAngle();
       angleInt=counter;
              for(index = 15; index >=0; index--)
                 {
                  writeGPIO(3, LED[index], ((angleInt>>(index))&0b1));
                 }
       break;
     }
   }
 }
