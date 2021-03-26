
#include <msp430.h>
#include "ring_buffer.h"



bool ringbuffer_isfull(RingBuffer_TypeDef *rb)
{
unsigned char rbhead, rbtail;

    rbhead = rb -> head;    // grab a "snap shot" of values so that changes made by irq won't affect below calc or eval
    rbtail = rb -> tail;    // the irq will only create more space, so using "old" data won't be a problem for reliabality, just performance.

    if(rbtail == (RINGBUFFERSIZE - 1))
    {
      if(rbhead == 0)
        return(TRUE);      
    }
    else if((rbtail + 1) == rbhead)
      return(TRUE);
      
    return(FALSE);
    
} 

bool ringbuffer_isempty(RingBuffer_TypeDef *rb)
{
  if(rb->head == rb->tail)
    return(TRUE);
  
  return(FALSE);
}
       
unsigned char ringbuffer_dequeue(RingBuffer_TypeDef *rb)
{
unsigned char retval;
 

  retval = rb->array[rb->head++];
  
  if(rb->head >= RINGBUFFERSIZE)
    rb->head = 0;
  
  return(retval);
} 

bool ringbuffer_enqueue(RingBuffer_TypeDef *rb, unsigned char bytedata)
{ 
    // if buffer is not full read the receive data register and increment tail pointer.
    if( ringbuffer_isfull(rb) == FALSE )
      rb->array[rb->tail++] = bytedata;
    else
      return(FALSE);
    
    // If new tail index is outside of ring buffer memory space, reset to beginning. (WRAP)
    if(rb->tail >= RINGBUFFERSIZE)
      rb->tail = 0;

    return(TRUE);
}

void ringbuffer_flush(RingBuffer_TypeDef *rb)
{
 rb->head = rb->tail = 0; 
}




