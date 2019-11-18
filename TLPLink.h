/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLPLink.h
 * @author  LL.T
 * @version 1.0.0
 * @date    2018/05/29
 * @brief   
 */

/* Define to prevent recursive inclusion */
#ifndef __TLPLINK_H_
#define __TLPLINK_H_

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "TLSPkt.h"		
#include "TLSFifo.h"		

/**
 * @brief Communication pattern based on TLSPkt and TLSFifo.
 */		
typedef struct 
{
	TLSFifo_t *Fifo;
	TLSPkt_t *Pkt;
	
	TLSPktMode Mode;        // ASCII or Hex mode defined in TLSPkt
	void *(*Proc)(void *);  // Business implemented by user
}TLPLink_t;

/**
 * @brief  Constructor for TLPLink.
 *         Memory allocated by malloc(), note configuration of Heap Size.
 * @vlsize Max size needed for value(uint8_t *Val) in TLSPkt
 * @bfsize Size of TLSFifo buffer(uint8_t *Buf)
 * @mode   ASCII or Hex mode defined in TLSPkt
 * @proc   Business implemented by user
 * @return Reference to a new TLPLink
 */
TLPLink_t *
newTLPLink(uint8_t vlsize, uint32_t bfsize, TLSPktMode mode, void *(*proc)(void *));

/**
 * @brief Destructor for TLPLink.
 *        Use free() to free memory allocated in newTLPLink().
 * @comm  Pointer to a reference to TLPLink
 */
void  
deleteTLPLink(TLPLink_t **lnk);

/**
 * @brief Process frame for comm using pattern TLPLink.
 *        Decode done by frame;
 *        Business left to user called by fun ptr (*Proc)().
 */
void
TLPLnkProc(TLPLink_t *lnk);

/**
 * @brief  Interrupt Service Routine.
 *         Only put byte received into TLSFifo.
 * @c      Byte received through interrupt
 * @return The byte put, or -1 when TLSFifo was full.
 */
int16_t
TLPLnkISR(TLPLink_t *lnk, uint8_t c);

#ifdef __cplusplus
  }
#endif

#endif /* __TLPLINK_H_ */
