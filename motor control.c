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
#include "hal.h"

signed int motor1speed = 0;
signed int motor2speed = 0;

void setMotor1Speed ( signed int speed)
{
signed int pwm = (signed int)MTRDRIVE_OFF;
  
  if(speed < (MTRDRIVE_OFF * (-1)))
    return;
  
  if(speed == 0)
    disableMOTOR1();
  else
    enableMOTOR1();
  
  pwm += speed;
  
  setMOTOR1DutyCycle(pwm);
}

void setMotor2Speed ( signed int speed)
{
signed int pwm = (signed int)MTRDRIVE_OFF;
  
  if(speed < (MTRDRIVE_OFF * (-1)))
    return;

  
  if(speed == 0)
    disableMOTOR2();
  else
    enableMOTOR2();
  
  
  pwm += speed;
  
  setMOTOR2DutyCycle(pwm);
}
