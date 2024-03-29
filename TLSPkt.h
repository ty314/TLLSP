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
#define TLSPKT_MAX_SIZE 255  // Fixed! Don't touch it.
#define TLSPKT_MIN_SIZE 9  // Can insert or delete data between Mark and Len
#define TLSPKT_MAX_VAL_SIZE (TLSPKT_MAX_SIZE - TLSPKT_MIN_SIZE)

/**
 * @brief The only difference between Hex and ASCII is how the Len is parsed.
 *        ASCII '6'(0x36) converted to Hex 0x06, 'F' to 0x0F, and so on.
 *        Note! In ASCII mode, Len range is '0'-'9' and 'A'-'F', case-insensitive.
 */			
typedef enum {
	TLSPKT_MODE_HEX = 0,
	TLSPKT_MODE_ASCII
}TLSPktMode;			

/**
 * @brief Data structure of TLSPkt, as well as protocol.
 *        In fact, except Mark and Len, all can be customized.
 *        User can insert or delete data between Mark and Len by TLSPKT_MIN_SIZE.
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
	
	/* Don't touch it! Used internally for parsing */
	uint8_t Status;
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

/**
 * @brief  Parse data user supplied into TLSPkt, one byte at a time.
 *         Only satisfy completeness, not correctness.
 *				 Note! Shouldn't call TLSPktParse() if TLSPkt is complete,
 *         otherwise the byte supplied will be discarded.
 * @return 0 if go smoothly, 1 means error occurred.
 */
uint8_t 
TLSPktParse(uint8_t c, TLSPkt_t *pkt, TLSPktMode mode);

/**
 * @brief  Return whether TLSPkt is complete
 * @return Non-zero if complete
 */
uint8_t
TLSPktIsCplt(TLSPkt_t *pkt);

/**
 * @brief Clear complete flag of TLSPkt
 */
void
TLSPktClrCplt(TLSPkt_t *pkt);

#ifdef __cplusplus
  }
#endif

#endif /* __TLSPKT_H_ */
