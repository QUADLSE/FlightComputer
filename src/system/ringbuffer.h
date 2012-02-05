/*
 * ringbuffer.h
 *
 *  Created on: Feb 5, 2012
 *      Author: Alan
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

/* buffer size definition */
#define RING_BUFSIZE 256

/* Buf mask */
#define __BUF_MASK (RING_BUFSIZE-1)
/* Check buf is full or not */
#define __BUF_IS_FULL(head, tail) ((tail&__BUF_MASK)==((head+1)&__BUF_MASK))
/* Check buf will be full in next receiving or not */
#define __BUF_WILL_FULL(head, tail) ((tail&__BUF_MASK)==((head+2)&__BUF_MASK))
/* Check buf is empty */
#define __BUF_IS_EMPTY(head, tail) ((head&__BUF_MASK)==(tail&__BUF_MASK))
/* Reset buf */
#define __BUF_RESET(bufidx)	(bufidx=0)
#define __BUF_INCR(bufidx)	(bufidx=(bufidx+1)&__BUF_MASK)


/** @brief UART Ring buffer structure */
typedef struct
{
    volatile uint32_t tx_head;                /*!< UART Tx ring buffer head index */
    volatile uint32_t tx_tail;                /*!< UART Tx ring buffer tail index */
    volatile uint32_t rx_head;                /*!< UART Rx ring buffer head index */
    volatile uint32_t rx_tail;                /*!< UART Rx ring buffer tail index */
    volatile uint8_t  tx[RING_BUFSIZE];  /*!< UART Tx data ring buffer */
    volatile uint8_t  rx[RING_BUFSIZE];  /*!< UART Rx data ring buffer */
} RING_BUFFER_t;


#endif /* RINGBUFFER_H_ */
