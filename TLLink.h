/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLLink.h
 * @author  LL.T
 * @version 1.0.0
 * @date    2018/05/28
 * @brief   
 */
 
/* Define to prevent recursive inclusion */
#ifndef __TLLINK_H_
#define __TLLINK_H_ 

/**
 * @brief TLLink version, format is x.y.z
 */
#define TLLNK_VERSION 100

#ifdef __cplusplus
  extern "C" {
#endif
	
/* Includes */
#include <stdint.h>
		
/**
 * @brief Macros of packet protocol
 */		
#define TLLNK_MARK 0x7E  // Packet head mark
#define TLLNK_VERIFY_OFFSET 1  // Byte calc Checksum from
#define TLLNK_HEADS_VERIFY  6  // Calc + Seq + Sys + Dev + Tag + Len  
#define TLLNK_MIN_SIZE      9  // Size no payload included

/**
 * @brief Based on FSM, decompose parse of packet into several stable status.
 */		
typedef enum {
	TLLNK_FSM_MARK = 0,
	TLLNK_FSM_CALC,
	TLLNK_FSM_SEQ,
	TLLNK_FSM_SYS,
	TLLNK_FSM_DEV,
	TLLNK_FSM_TAG,
	TLLNK_FSM_LEN,
	TLLNK_FSM_VAL,
	TLLNK_FSM_CKL,
	TLLNK_FSM_CKH
}TLLNKFSMStatus;

/**
 * @brief Packet protocol
 */	
typedef struct 
{
	uint8_t Mark;    // Packet head mark
	uint8_t Calc;    // Calc Checksum if non-zero, else fill Checksum with Tag and Len.
	uint8_t Seq;     // Packet sequence
	uint8_t Sys;     // Sender system
	uint8_t Dev;     // Sender device
	uint8_t Tag;     // Tag
	uint8_t Len;     // Length
	uint8_t *ValPtr; // Value, remember to initialize the pointer.
	uint16_t Checksum;
}TLLNKPacket_t;

/**
 * @brief Data structure of TLLink.
 *        It doesn't contain instance of TLLNKPacket_t, whose use is up to implementer.
 *        Implementer can use one for sent and received, or two respectively.
 */	
typedef struct 
{
	uint8_t Sys;        // Local system
	uint8_t Dev;        // Local device
	uint8_t SeqRcv;     // Sequence of last packet received
	uint8_t SeqSend;    // Sequence of last packet sent
	uint32_t NbrErr;    // Number of error packets
	uint32_t NbrValid;  // Number of valid packets
	uint8_t Cnt;        // Counter of length has got
	TLLNKFSMStatus FSM;
}TLLink_t;

#ifdef __cplusplus
  }
#endif

#endif /* __TLLINK_H_ */
