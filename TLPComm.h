/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLPComm.h
 * @author  LL.T
 * @version 1.0.0
 * @date    2018/05/29
 * @brief   
 */

/* Define to prevent recursive inclusion */
#ifndef __TLPCOMM_H_
#define __TLPCOMM_H_

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "TLSLink.h"
#include "TLLFifo.h"

/**
 * @brief Communication pattern based on TLSLink and TLLFifo
 */		
typedef struct
{
	TLLFifo_t *Fifo;         // Cache received data
	TLSLNKPacket_t *Packet;  // Buffer for packet received and sent, not simultaneously 
	TLSLink_t *Link;
}TLPComm_t;

/**
 * @brief  Constructor for TLPComm.
 *         Memory allocated by malloc(), note configuration of Heap Size.
 * @sys    Local system in TLSLink
 * @dev    Local device in TLSLink
 * @vlsize Max size needed for value in TLSLNKPacket
 * @bfsize Size of TLLFifo buffer
 * @return Reference to a new TLPComm
 */
TLPComm_t *
newTLPComm(uint8_t sys, uint8_t dev, uint8_t vlsize, uint32_t bfsize);

/**
 * @brief Destructor for TLPComm.
 *        Use free() to free memory allocated in newTLPComm().
 * @comm  Pointer to a reference to TLPComm
 */
void  
deleteTLPComm(TLPComm_t **comm);

/**
 * @brief  Call TLSLNKParse() and TLSLNKVerify() to decode data in TLLFifo.
 *         Packet decoded is cached in TLSLNKPacket.
 *         Obviously, TLSLink is updated in TLSLNKVerify().   
 * @return 0 None
 *         1 Incomplete
 *         2 Error
 *         3 Valid
 */
uint8_t
TLPCOMMDecode(TLPComm_t *comm);

#ifdef __cplusplus
  }
#endif

#endif /* __TLPCOMM_H_ */
