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
#define TLSLNK_MARK 0x7E  // Packet head mark
#define TLSLNK_VERIFY_OFFSET 1  // Byte calc Checksum from
#define TLSLNK_HEADS_VERIFY  6  // Calc + Seq + Sys + Dev + Tag + Len  
#define TLSLNK_MIN_SIZE      9  // Size no value included

/**
 * @brief Based on FSM, decompose parse of packet into several stable status.
 */		
typedef enum {
	TLSLNK_FSM_MARK = 0,
	TLSLNK_FSM_CALC,
	TLSLNK_FSM_SEQ,
	TLSLNK_FSM_SYS,
	TLSLNK_FSM_DEV,
	TLSLNK_FSM_TAG,
	TLSLNK_FSM_LEN,
	TLSLNK_FSM_VAL,
	TLSLNK_FSM_CKL,
	TLSLNK_FSM_CKH
}TLSLNKFSMStatus;

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
}TLSLNKPacket_t;

/**
 * @brief Data structure of TLSLink.
 *        It doesn't contain instance of TLSLNKPacket_t, whose use is up to implementer.
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
	TLSLNKFSMStatus FSM;
}TLSLink_t;

/**
 * @brief  Constructor for TLSLink.
 *         Memory allocated by malloc(), note configuration of Heap Size. 
 * @sys    Local system   
 * @dev    Local device
 * @return Reference to a new TLSLink
 */
TLSLink_t *  
newTLSLink(uint8_t sys, uint8_t dev);

/**
 * @brief Destructor for TLSLink.
 *        Use free() to free memory allocated in newTLSLink().
 * @lnk   Pointer to a reference to TLSLink
 */
void  
deleteTLSLink(TLSLink_t **lnk);

/**
 * @brief  Constructor for TLSLNKPacket.
 *         Memory allocated by malloc(), note configuration of Heap Size. 
 * @size   Max size of value
 * @return Reference to a new TLSLNKPacket
 */
TLSLNKPacket_t *  
newTLSLNKPacket(uint8_t size);

/**
 * @brief Destructor for TLSLNKPacket.
 *        Use free() to free memory allocated in newTLSLNKPacket().
 * @pkt   Pointer to a reference to TLSLNKPacket
 */
void  
deleteTLSLNKPacket(TLSLNKPacket_t **pkt);

/**
 * @brief  Pack sent packet.
 *         Assume message (Tag, Len, Val) already set.
 * @pkt    Sent packet to pack
 * @lnk    TLSLink 
 * @calc   Calc Checksum if non-zero, else fill Checksum with Tag and Len.
 * @return Packet size, limit to 0xFF.
 */
uint8_t 
TLSLNKPack(TLSLNKPacket_t *pkt, TLSLink_t *lnk, uint8_t calc);

/**
 * @brief  Parse one byte with state machine according to packet protocol.
 *         Only satisfy completeness, not correctness.
 *         User should then call TLSLNKVerify() to verify Checksum.
 * @c      Byte caller supplied for parsing
 * @pkt    Packet parsed into
 * @lnk    TLSLink
 * @return 0 if complete packet parsed, else 1.
 */
uint8_t 
TLSLNKParse(uint8_t c, TLSLNKPacket_t *pkt, TLSLink_t *lnk);

/**
 * @brief  Verify Checksum and update TLSLink after complete packet parsed
 * @pkt    Packet has been parsed to verify
 * @lnk    TLSLink
 * @return 1 if correct, else 0.
 */
uint8_t
TLSLNKVerify(TLSLNKPacket_t *pkt, TLSLink_t *lnk);

#ifdef __cplusplus
  }
#endif

#endif /* __TLSLINK_H_ */
