#include "ring_buffer.h"

RingBuffer_TypeDef rb_rx, rb_tx;
unsigned char command, sensors;
unsigned char rcvpayload[4];
unsigned char txmpayload[4];
unsigned char myaddress = 99;
