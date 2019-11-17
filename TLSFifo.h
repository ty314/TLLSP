/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLSFifo.h
 * @author  LL.T
 * @version 1.0.0
 * @date    2018/05/27
 * @brief   
 */
 
/* Define to prevent recursive inclusion */
#ifndef __TLSFIFO_H_
#define __TLSFIFO_H_ 

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include <stdint.h>

/**
 * @brief Data structure of TLSFifo
 */			
typedef struct{
	uint32_t Size;  // Must be a 2-power!
	uint32_t Mask;  // Don't touch it! Used internally for wrapping. 
	volatile uint32_t Head;
	volatile uint32_t Tail;
	uint8_t *BufPtr;	
}TLSFifo_t;

/**
 * @brief  Constructor for TLSFifo.
 *         Memory allocated by malloc(), note configuration of Heap Size. 
 * @size   Size of TLSFifo buffer, it must be a 2-power.
 * @return Reference to a new TLSFifo
 */
TLSFifo_t *  
newTLSFifo(uint32_t size);

/**
 * @brief Destructor for TLSFifo.
 *        Use free() to free memory allocated in newTLSFifo().
 * @fifo  Pointer to a reference to TLSFifo
 */
void  
deleteTLSFifo(TLSFifo_t **fifo);

/**
 * @brief Flush TLSFifo
 */
void 
TLSFifoFlush(TLSFifo_t *fifo);

/**
 * @brief Return the number of elements in TLSFifo
 */
uint32_t 
TLSFifoUsed(TLSFifo_t *fifo);

/**
 * @brief Return the remaining free spaces of TLSFifo 
 */
uint32_t 
TLSFifoFree(TLSFifo_t *fifo);

/**
 * @brief  Return whether TLSFifo is empty
 * @return Non-zero if empty
 */
uint8_t 
TLSFifoIsEmpty(TLSFifo_t *fifo);

/**
 * @brief Return whether TLSFifo is full
 * @return Non-zero if full
 */
uint8_t 
TLSFifoIsFull(TLSFifo_t *fifo);

/**
 * @brief  Put a element into TLSFifo
 * @return The item put, or -1 when TLSFifo was full.
 */
int16_t
TLSFifoPutc(TLSFifo_t *fifo, uint8_t c);

/**
 * @brief Get a element from TLSFifo
 * @return The item got, or -1 when TLSFifo was empty.
 */
int16_t
TLSFifoGetc(TLSFifo_t *fifo);

/**
 * @brief Get a element from TLSFifo but don't remove it
 * @return The item got, or -1 when TLSFifo was empty.
 */
int16_t
TLSFifoPeek(TLSFifo_t *fifo);

/**
 * @brief  Put elements into TLSFifo
 * @return Number of elements put actually
 */
uint32_t 
TLSFifoPuts(TLSFifo_t *fifo, const uint8_t *s, uint32_t len);

/**
 * @brief  Get elements from TLSFifo
 * @return Number of elements got actually
 */
uint32_t 
TLSFifoGets(TLSFifo_t *fifo, uint8_t *s, uint32_t len);

#ifdef __cplusplus
  }
#endif

#endif /* __TLSFIFO_H_ */
