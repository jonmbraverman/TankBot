//#include "io430.h"
#include "ring_buffer.h"
#include "global.h"



unsigned char getMessage(unsigned char* rcvpayload)
{
static unsigned char rxmessage[10] = {0,0,0,0,0,0,0,0,0,0};
static unsigned char rxptr = 0;
unsigned char mybyte;
unsigned char bytesum = 0;

  if(ringbuffer_isempty(&rb_rx) == 0)
  {
    mybyte = ringbuffer_dequeue(&rb_rx);  
    rxmessage[rxptr++] = mybyte;
    if(rxptr >= 10) // if a complete message has been received
    {
      rxptr = 0;     // prepare for next receipt

      if((rxmessage[0] == 0xE3) && (rxmessage[2] == myaddress) && (rxmessage[9] == 0x3E))
      {
        for(mybyte = 1;mybyte < 8;mybyte++)
          bytesum += rxmessage[mybyte];
        
        if(bytesum == rxmessage[8])
        {
          rcvpayload[0] = rxmessage[4];
          rcvpayload[1] = rxmessage[5];
          rcvpayload[2] = rxmessage[6];
          rcvpayload[3] = rxmessage[7];
          return(rxmessage[1]);
        }
        
      }
    }
  }

  return(0);
  
}

void buildMessage(unsigned char destination, unsigned char* txmtpayload)
{
unsigned char txbyte;
unsigned char mybyte;
unsigned char bytesum = 0;  
static unsigned char transmissions = 0;

  for(mybyte = 0;mybyte < 10;mybyte++)
  {
    switch(mybyte)
    {
    case 0:
      txbyte = 0xE3;
      break;
    case 1:
      txbyte = transmissions;
      bytesum += txbyte;
      break;
     case 2:
      txbyte = destination;
      bytesum += txbyte;
      break;
    case 3:
      txbyte = myaddress;
      bytesum += txbyte;
      break;      
    case 4:
    case 5:
    case 6:
    case 7:
      txbyte = txmtpayload[mybyte - 4];
      bytesum += txbyte;
      break;      
    case 8:
      txbyte = bytesum;
      break;
    case 9:
      txbyte = 0x3E;
      break;
    }
    
    ringbuffer_enqueue(&rb_rx,txbyte);
    
    
  }
  
  
}
