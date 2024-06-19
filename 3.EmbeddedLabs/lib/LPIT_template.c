/*
  LPIT.h
  University of Michigan
  EECS 461, Embedded Control Systems
  Low Power Interrupt Timer (LPIT)
  Read Chapter 30 in S32K144 User's Manual

  Revision History:
    2017-11-16  schmo
    2017-03-13  Paul Domanico
 */

#include "LPIT.h"

/* Array of 4 interrupt service routines.  One for each channel */
static int LPIT_IRQn[4] = LPIT_IRQS;    // { LPIT0_Ch0_IRQn, LPIT0_Ch1_IRQn, LPIT0_Ch2_IRQn, LPIT0_Ch3_IRQn }

void enableLPIT(){
  /* 29.6.5 PCC LPIT Register  */
  PCC->PCCn[PCC_LPIT_INDEX] =0x00000000;  /* Disable PCC LPIT clock to change PCS */
  PCC->PCCn[PCC_LPIT_INDEX] |= 0x06000000;     /* Clock source:  SPLL2_DIV2_CLK */
  PCC->PCCn[PCC_LPIT_INDEX] |=0x40000000;
                           /* fill in */   /* Enable clk to LPIT0 regs */

  /* 46.4.1.4.2 Module Control Register  */
  LPIT0->MCR  =0x00000001;     /* enable module clk (allows writing other LPIT0 regs)*/
}


void initLPIT(const uint8_t channel, const uint32_t frequency, const isr_t handler, const uint32_t priority) {
  /* 46.4.1.9.3 Timer Value Register   */
  LPIT0->TMR[channel].TVAL = (40000000/frequency) - 1 ;    /* channel timer start value */  
  
  /* 46.4.1.6.2 Module Interrupt Enable Register */
  LPIT0->MIER = 1<<channel; //0x0000000F;    /* Timer Interrupt Enabled for Channel */
  
  /* 46.4.1.9.3 Timer Control Register */  
  LPIT0->TMR[channel].TCTRL = LPIT_TMR_TCTRL_T_EN(0b0); /* T_EN : Timer channel is disabled to set registers*/
 LPIT0->TMR[channel].TCTRL = LPIT_TMR_TCTRL_MODE(0b00);  /* MODE :  32 periodic counter mode */
  LPIT0->TMR[channel].TCTRL = LPIT_TMR_TCTRL_TSOT(0b0);  /* TSOT : Timer decrements immediately based on restart */
  LPIT0->TMR[channel].TCTRL = LPIT_TMR_TCTRL_TSOI(0b0);  /* TSOI :  Timer does not stop after timeout */
 LPIT0->TMR[channel].TCTRL = LPIT_TMR_TCTRL_TROT(0b0);  /* TROT : ignore external trigger */            
 
  /* 46.4.1.7.3 Set Timer Enable Register   */                                                 
  LPIT0->SETTEN =1<<channel;    /*SET_T_EN_n :  enable timer for channel */

  /* defined in interrupt_manager.c */
  INT_SYS_InstallHandler(LPIT_IRQn[channel], handler, (isr_t*) 0);
  INT_SYS_SetPriority(LPIT_IRQn[channel], priority);
  INT_SYS_EnableIRQ(LPIT_IRQn[channel]);
}


void clearFlagLPIT(const uint8_t channel){
  /* 46.4.1.5.3 Module Status Register  */
  LPIT0->MSR |=1<<channel;   /* clear TIFn */
}

