/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLLFifo.h
 * @author  D.T
 * @version 1.0.0
 * @date    2018/05/27
 * @brief   
 */
 
/* Define to prevent recursive inclusion */
#ifndef __TLLFIFO_H_
#define __TLLFIFO_H_ 

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include <stdint.h>

/**
 * @brief Data structure of fifo
 */			
typedef struct{
	uint32_t Size;  // Must be a 2-power
	volatile uint32_t Head;
	volatile uint32_t Tail;
  uint8_t *BufPtr;	
}TLLFifo_t;

/**
 * @brief  Constructor for TLLFifo.
 *         Memory allocated by malloc(), note configuration of Heap Size. 
 * @size   Size of fifo, it must be a 2-power.
 * @return Reference to a new TLLFifo
 */
TLLFifo_t *  
newTLLFifo(uint32_t size);

/**
 * @brief Destructor for TLLFifo.
 *        Use free() to free memory allocated in newTLLFifo().
 * @fifo  Pointer to a reference to TLLFifo
 */
void  
deleteTLLFifo(TLLFifo_t **fifo);

/**
 * @brief Flush fifo
 */
void 
TLLFifoFlush(TLLFifo_t *fifo);

/**
 * @brief Return the number of elements in fifo
 */
uint32_t 
TLLFifoUsed(TLLFifo_t *fifo);

/**
 * @brief Return the remaining free spaces of fifo 
 */
uint32_t 
TLLFifoFree(TLLFifo_t *fifo);

/**
 * @brief  Return whether fifo is empty
 * @return Non-zero if empty
 */
uint8_t 
TLLFifoIsEmpty(TLLFifo_t *fifo);

/**
 * @brief Return whether fifo is full
 * @return Non-zero if full
 */
uint8_t 
TLLFifoIsFull(TLLFifo_t *fifo);
/**
 * @brief  Put a element into fifo
 * @return The item put, or -1 when fifo was full.
 */
int16_t
TLLFifoPutc(TLLFifo_t *fifo, uint8_t c);

/**
 * @brief Get a element from fifo
 * @return The item got, or -1 when fifo was empty.
 */
int16_t
TLLFifoGetc(TLLFifo_t *fifo);

/**
 * @brief Get a element from fifo but don't remove it from fifo
 * @return The item got, or -1 when fifo was empty.
 */
int16_t
TLLFifoPeek(TLLFifo_t *fifo);

/**
 * @brief  Put elements into fifo
 * @return Number of elements put actually
 */
uint32_t 
TLLFifoPuts(TLLFifo_t *fifo, const uint8_t *s, uint32_t len);

/**
 * @brief  Get elements from fifo
 * @return Number of elements got actually
 */
uint32_t 
TLLFifoGets(TLLFifo_t *fifo, uint8_t *s, uint32_t len);

#ifdef __cplusplus
  }
#endif

#endif /* __TLLFIFO_H_ */
