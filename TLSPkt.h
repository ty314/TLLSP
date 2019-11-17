/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLSPkt.h
 * @author  LL.T
 * @version 1.0.0
 * @date    2018/05/28
 * @brief   
 */
 
/* Define to prevent recursive inclusion */
#ifndef __TLSPKT_H_
#define __TLSPKT_H_ 

/**
 * @brief TLSPkt version, format is x.y.z
 */
#define TLSPKT_VERSION 100

#ifdef __cplusplus
  extern "C" {
#endif
	
/* Includes */
#include <stdint.h>
	
#define TLSPKT_MARK 0x7E // TLSPkt head mark	  		

/**
 * @brief Data structure of TLSPkt, as well as protocol.
 */	
typedef struct 
{
	/* Protocol, must send in order as follow. */
	uint8_t Mark;  // Head mark
	uint8_t ResvX;
	uint8_t ResvY;	
	uint8_t ResvZ;
	uint8_t Seq;   // Sequence
	uint8_t Sys;   // System
	uint8_t Dev;   // Device
	uint8_t Tag;   // Tag
	uint8_t Len;   // Length
	uint8_t *Val;  // Value
}TLSPkt_t;

/**
 * @brief  Constructor for TLSPkt.
 *         Memory allocated by malloc(), note configuration of Heap Size. 
 * @size   Max size of value(uint8_t *Val)
 * @return Reference to a new TLSPkt
 */
TLSPkt_t *  
newTLSPkt(uint8_t size);

/**
 * @brief Destructor for TLSPkt.
 *        Use free() to free memory allocated in newTLSPkt().
 * @pkt   Pointer to a reference to TLSPkt
 */
void  
deleteTLSPkt(TLSPkt_t **pkt);

#ifdef __cplusplus
  }
#endif

#endif /* __TLSPKT_H_ */
