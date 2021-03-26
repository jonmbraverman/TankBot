
#include "hal.h"

#define MAX_SPEED_F (MTRDRIVE_PERIOD - MTRDRIVE_OFF)
#define MAX_SPEED_R (-1 * (MTRDRIVE_PERIOD - MTRDRIVE_OFF))


void setMotor1Speed ( signed int speed);
void setMotor2Speed ( signed int speed);
