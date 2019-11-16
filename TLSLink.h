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
	
#define TLSLNK_MARK 0x7E // Head mark	
/* Number of bytes in heads need to verify: Calc, Seq, Sys, Dev, Tag, Len */		
#define TLSLNK_HEADS_VERIFY 6   		

/**
 * @brief Data structure of TLSLink, as well as protocol.
 */	
typedef struct 
{
	/* Protocol, must send in order as follow. */
	uint8_t Mark;     // Head mark
	uint8_t CKL;      // Divide checksum consider alignment of structure,
	uint8_t CKH;      // if Calc is non-zero, calc checksum by Crc16/Modbus,	
	uint8_t Calc;     // else just filled with Tag(CKL) and Len(CKH).
	uint8_t Seq;      // Sequence
	uint8_t Sys;      // Sender system
	uint8_t Dev;      // Sender device
	uint8_t Tag;      // Tag
	uint8_t Len;      // Length
	uint8_t *ValPtr;  // Value
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
 * @brief  Calc Checksum by Crc16/Modbus, or just fill with Tag and Len.
 * @return Checksum
 */
uint16_t 
TLSLNKCalc(TLSLink_t *lnk);

#ifdef __cplusplus
  }
#endif

#endif /* __TLSLINK_H_ */
