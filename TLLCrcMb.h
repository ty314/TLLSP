/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLLCrcMb.h
 * @author  LL.T
 * @version 1.0.0
 * @date    2018/05/27
 * @brief   
 */
 
/* Define to prevent recursive inclusion */
#ifndef __TLLCRCMB_H_
#define __TLLCRCMB_H_

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include <stdint.h>

/**
 * @brief  Calculate Crc16/Modbus
 * @pdata  Pointer of data to hash
 * @len    Data length
 * @return Checksum
 **/
uint16_t
TLLCrcMbCalc(const uint8_t *pdata, uint16_t len);

/**
 * @brief Accumulate Crc16/Modbus
 * @ck    Already accumulated checksum input, as well as return
 * @pdata Pointer of followed data to hash
 * @len   Data length
 **/
void 
TLLCrcMbAccum(uint16_t *ck, const uint8_t *pdata, uint16_t len);

#ifdef __cplusplus
  }
#endif

#endif /* __TLLCRCMB_H_ */
