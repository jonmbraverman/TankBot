/*******************************************************************************
;   TankBot Motor Drive using Timer_A, PWM TA1.1, TA1.2, Up Mode, DCO SMCLK
;
;   Description: This program generates two PWM outputs on P2.1 (TA1.1) and 
;   P2.4 (TA1.2) using Timer_A configured for up mode. 
;   The value in TA1CCR0, 512-1, defines the PWM period
;   and the value in TA1CCR1, TA1CCR2 the PWM duty cycles.
;   ACLK = n/a, SMCLK = MCLK = TACLK = default DCO
;
;
;       P2      7 6 5 4 3 2 1 0
;                     | | | | |
;                     | | | | - ----------
;                     | | | --- Motor 1 PWM E
;                     | | ----- Motor 1 Direction M
;                     | ------- Motor 2 Direction M 
;                     --------- Motor 2 PWM E


****************************************************************************** */

//#include "io430.h"
#include <msp430g2553.h>
#include "hal.h"

void configGPIO( void )
{
  P1OUT = 0;                                    // Clear output buffer           
  P1DIR = _STATUSLED_BIT;                        // StatusLED (P1.3) output
  P1REN = _PUSHBUTTON_BIT;                      // Pushbutton pull up resistor enabled
  P2OUT = 0;                                    // Clear output buffer
  P2DIR = _M1EN_BIT+_M1PWM_BIT+_M2EN_BIT+_M2PWM_BIT;                 // Motor Drive 1 (P2.1, P2.2) outputs & Motor Drive 2 (P2.3, P2.4) outputs          
  P2SEL = _M1PWM_BIT+_M2PWM_BIT;                 // Motor Drive 1 & 2 PWM options P2.1,P2.4 -> TA1.1, TA1.2 
  P1OUT = _STATUSLED_BIT;
}

void configTIMERA0( void )
{
  TA0CCTL0 = CCIE;                    // Set TA1CCR1 reset/set            
  TA0CCR0 = 10000;                    // Set PWM Period        
  TA0CTL = TASSEL_2+MC_1+ID_3;             // SMCLK, upmode, divide by 8
}

void configTIMERA1( void )
{
   
  TA1CCR0 = MTRDRIVE_PERIOD;                    // Set PWM Period        
  TA1CCTL1 = OUTMOD_7;                          // Set TA1CCR1 reset/set            
  TA1CCR1 = MTRDRIVE_OFF;                           // Init TA1CCR1 PWM Duty Cycle	
  TA1CCTL2 = OUTMOD_7;                          // Set TA1CCR2 reset/set            
  TA1CCR2 = MTRDRIVE_OFF;                           // Init TA1CCR2 PWM Duty Cycle	            
  TA1CTL = TASSEL_2+MC_1;                       // SMCLK, upmode
}

void configUARTA0(void)
{
  P1SEL = BIT1 + BIT2;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2;                    // P1.1 = RXD, P1.2=TXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 104;                            // 1MHz 9600
  UCA0BR1 = 0;                              // 1MHz 9600
  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

void enableMOTOR1( void )
{
  P2OUT |= _M1EN_BIT;
}

void enableMOTOR2( void )
{
  P2OUT |= _M2EN_BIT;  
}

void disableMOTOR1( void )
{
  P2OUT &= ~_M1EN_BIT;
}

void disableMOTOR2( void )
{
  P2OUT &= ~_M2EN_BIT;  
}

void setMOTOR1DutyCycle ( signed int dutycycle )
{
  TA1CCR1 = (unsigned int)dutycycle;
}

void setMOTOR2DutyCycle ( signed int dutycycle )
{
  TA1CCR2 = (unsigned int)dutycycle;
}


void turnOnLED1 ( void )
{
    P1OUT |= _STATUSLED_BIT;
}


void turnOffLED1 ( void )
{
    P1OUT &= ~_STATUSLED_BIT;
}
