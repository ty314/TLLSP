/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLSLink.h
 * @author  LL.T
 * @version 1.0.0
 * @date    2018/05/28
 * @brief   
 */
 
/* Define to prevent recursive inclusion */
#ifndef __TLSLINK_H_
#define __TLSLINK_H_ 

/**
 * @brief TLSLink version, format is x.y.z
 */
#define TLSLNK_VERSION 100

#ifdef __cplusplus
  extern "C" {
#endif
	
/* Includes */
#include <stdint.h>
		
/**
 * @brief Macros of packet protocol
 */		
#define TLSLNK_MARK 0x7E  // Head mark  

/**
 * @brief Based on FSM, decompose parse into several stable status.
 */		
typedef enum {
	TLSLNK_STA_MARK = 0,
	TLSLNK_STA_RESVA,
	TLSLNK_STA_RESVB,
	TLSLNK_STA_SEQ,
	TLSLNK_STA_SYS,
	TLSLNK_STA_DEV,
	TLSLNK_STA_TAG,
	TLSLNK_STA_LEN,
	TLSLNK_STA_VAL,
	
	/* Got complete packet, do nothing until processed 
	   and switch to TLSLNK_STA_MARK. */
	TLSLNK_STA_FINISH
}TLSLNKStatus;

/**
 * @brief Data structure of TLSLink, as well as packet protocol.
 */	
typedef struct 
{
	uint8_t Cnt;     // Length count when parsing, if Len non-zero.
	TLSLNKStatus Status;
	
	/* Packet protocol, must send in order as follow. */
	uint8_t Mark;    // Head mark
	uint8_t ResvA;   // Reserved, left to user to define,
	uint8_t ResvB;   // for example as checksum.
	uint8_t Seq;     // Sequence
	uint8_t Sys;     // Sender system
	uint8_t Dev;     // Sender device
	uint8_t Tag;     // Tag
	uint8_t Len;     // Length
	uint8_t *ValPtr; // Value
}TLSLink_t;

/**
 * @brief  Constructor for TLSLink.
 *         Memory allocated by malloc(), note configuration of Heap Size. 
 * @size   Max size of value
 * @return Reference to a new TLSLink
 */
TLSLink_t *  
newTLSLink(uint8_t size);

/**
 * @brief Destructor for TLSLink.
 *        Use free() to free memory allocated in newTLSLink().
 * @pkt   Pointer to a reference to TLSLink
 */
void  
deleteTLSLink(TLSLink_t **lnk);

/**
 * @brief Parse one byte with state machine according to packet protocol.
 *        Only satisfy completeness, not correctness, left to user implement.
 * @c     Byte caller supplied for parsing
 * @lnk   TLSLink, packet parsed into, also record the status.
 */
void 
TLSLNKParse(uint8_t c, TLSLink_t *lnk);

#ifdef __cplusplus
  }
#endif

#endif /* __TLSLINK_H_ */
