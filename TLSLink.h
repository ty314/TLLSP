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
#define TLLNK_MIN_SIZE      9  // Size no value included

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
	uint8_t *ValPtr; // Value
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

/**
 * @brief  Constructor for TLLink.
 *         Memory allocated by malloc(), note configuration of Heap Size. 
 * @sys    Local system   
 * @dev    Local device
 * @return Reference to a new TLLink
 */
TLLink_t *  
newTLLink(uint8_t sys, uint8_t dev);

/**
 * @brief Destructor for TLLink.
 *        Use free() to free memory allocated in newTLLink().
 * @lnk   Pointer to a reference to TLLink
 */
void  
deleteTLLink(TLLink_t **lnk);

/**
 * @brief  Constructor for TLLNKPacket.
 *         Memory allocated by malloc(), note configuration of Heap Size. 
 * @size   Max size of value
 * @return Reference to a new TLLNKPacket
 */
TLLNKPacket_t *  
newTLLNKPacket(uint8_t size);

/**
 * @brief Destructor for TLLNKPacket.
 *        Use free() to free memory allocated in newTLLNKPacket().
 * @pkt   Pointer to a reference to TLLNKPacket
 */
void  
deleteTLLNKPacket(TLLNKPacket_t **pkt);

/**
 * @brief  Pack sent packet.
 *         Assume message (Tag, Len, Val) already set.
 * @pkt    Sent packet to pack
 * @lnk    TLLink 
 * @calc   Calc Checksum if non-zero, else fill Checksum with Tag and Len.
 * @return Packet size, limit to 0xFF.
 */
uint8_t 
TLLNKPack(TLLNKPacket_t *pkt, TLLink_t *lnk, uint8_t calc);

/**
 * @brief  Parse one byte with state machine according to packet protocol.
 *         Only satisfy completeness, not correctness.
 *         User should then call TLLNKVerify() to verify Checksum.
 * @c      Byte caller supplied for parsing
 * @pkt    Packet parsed into
 * @lnk    TLLink
 * @return 0 if complete packet parsed, else 1.
 */
uint8_t 
TLLNKParse(uint8_t c, TLLNKPacket_t *pkt, TLLink_t *lnk);

/**
 * @brief  Verify Checksum and update IOTLink after complete packet parsed
 * @pkt    Packet has been parsed to verify
 * @lnk    TLLink
 * @return 1 if correct, else 0.
 */
uint8_t
TLLNKVerify(TLLNKPacket_t *pkt, TLLink_t *lnk);

#ifdef __cplusplus
  }
#endif

#endif /* __TLLINK_H_ */
