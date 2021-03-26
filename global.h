#include "ring_buffer.h"

extern RingBuffer_TypeDef rb_rx, rb_tx;
extern unsigned char command, sensors;
extern unsigned char rcvpayload[4];
extern unsigned char myaddress;
extern unsigned char txmpayload[4];
