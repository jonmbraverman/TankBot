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
#include <msp430g2553.h>
//#include "io430.h"
#include "hal.h"
#include "ring_buffer.h"
#include "motor control.h"
#include "global.h"

extern unsigned int countdown1;

void main( void )
{
  unsigned  char mode = 0;
  unsigned int speed = MAX_SPEED_F;
  unsigned int pwm = 0;
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_8MHZ;                       // Set DCO to 8MHz
  DCOCTL =  CALDCO_8MHZ; 

  configGPIO();
  configTIMERA0();
  configTIMERA1();
  configUARTA0();
  
  _BIS_SR(GIE);                 // Enable interrupt

  //if(PB)
    mode = 0;
 
  
    
  while(1)
  {
    if(mode == 0)
    {
      
      if(countdown1 == 0)
      {
        countdown1 = 5;
        speed -= 1;
      }
      
      setMotor1Speed(speed);
      turnOnLED1();
    }
    else if(mode == 1)
    {
      if(countdown1 == 0)
      {
        countdown1 = 5;
        pwm += 1;
      }
      
      setMOTOR1DutyCycle(pwm & 511);
      turnOffLED1();
    }
    else if(mode == 2)
    {

    }
  }
  
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  ringbuffer_enqueue(&rb_rx, UCA0RXBUF);
}



#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
  if(ringbuffer_isempty(&rb_tx))
  {
      IE2 &= UCA0TXIE;                          // Disable USCI_A0 TX interrupt
  }
  else
  {
      UCA0TXBUF = ringbuffer_dequeue(&rb_tx);                    // TX -> RXed character
  }

}
