/*
   qd.h
   University of Michigan
   EECS 461, Embedded Control Systems
   FlexTimer Module (FTM): Quadrature Decode
   Read Chapter 45 in S32K144 User's Manual
    Section 45.5.27: Quadrature Decoder Mode

   Revision History:
     2017-03-14  RMC
     2017-03     Paul Domanico
 */
#include "qd.h"

#define ENCODER_COUNT 4000
#define QD_PHA_PORT PORTA
#define QD_PHB_PORT PORTA
#define QD_PHA_PIN 0xD
#define QD_PHB_PIN 0xC

/******************************************************************************
* Function: init_QD
* Description: Initializes eTimer for Quadrature Decoding
******************************************************************************/
void initQD()
{
  /* Initialize Phase A and B input PCR */
    QD_PHA_PORT->PCR[ (QD_PHA_PIN) ] |= PORT_PCR_MUX(0b110);
    QD_PHB_PORT->PCR[ (QD_PHB_PIN) ] |= PORT_PCR_MUX(0b110);
    /* Set up FTM2 for Quadrature Decode */
    FTM2->MODE |= FTM_MODE_WPDIS_MASK;
    /* Disable write protection (should already be disabled) */
    FTM2->MOD = 0xFFFF ;
    FTM2->CNTIN =0x0;
    FTM2->QDCTRL = 0b1 ;
    /* Enable QD mode */
    FTM2->CONF |= FTM_CONF_BDMMODE(0b11);
    /* Optional: enable in debug mode */
    return;
}

/******************************************************************************
 * Function:    updateCounter
 * Description: Returns an updated counter value that keeps track of absolute
 *              wheel position
 ******************************************************************************/
int32_t updateCounter()
{
  static int32_t total_count=0;
  uint16_t curr_count=0;
  static uint16_t prev_count =0;
  curr_count = FTM2->CNT;
  total_count += (int16_t) (curr_count - prev_count);
  prev_count = curr_count;
  return total_count;
}


/******************************************************************************
 * Function:    updateAngle
 * Description: Returns the angle of the wheel
 ******************************************************************************/
float updateAngle()
{
  float angle=0;
  angle=(updateCounter()*0.09); //resolution in 4x mode
  return angle;
}
