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
;                     | | | | -
;                     | | | --- Motor 1 PWM
;                     | | ----- Motor 1 Enable
;                     | ------- Motor 2 Enable
;                     --------- Motor 2 PWM

****************************************************************************** */

//GPIO HARDWARE LOCATIONS

#define _M1PWM_BIT      0x02        //; BIT1
#define _M1EN_BIT       0x04        //; BIT2
#define _M2EN_BIT       0x08        //; BIT3
#define _M2PWM_BIT      0x10        //; BIT4
#define _STATUSLED_BIT  0x01
#define _PUSHBUTTON_BIT 0x08

// PWM VALUES
#define MTRDRIVE_PERIOD  511    // MOTOR DRIVE PERIOD - 1 
#define MTRDRIVE_OFF    ((MTRDRIVE_PERIOD + 1)/2)

#define PB (_PUSHBUTTON_BIT & P1IN)

void configGPIO( void );
void configTIMERA0( void );
void configTIMERA1( void );
void configUARTA0( void );
void enableMOTOR1( void );
void enableMOTOR2( void );
void disableMOTOR1( void );
void disableMOTOR2( void );
void setMOTOR1DutyCycle ( signed int dutycycle );
void setMOTOR2DutyCycle ( signed int dutycycle );
void turnOnLED1 ( void );
void turnOffLED1 ( void );
