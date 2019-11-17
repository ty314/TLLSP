/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLLAsciiToHex.h
 * @author  LL.T
 * @version 1.0.0
 * @date    2018/05/28
 * @brief   
 */
 
/* Define to prevent recursive inclusion */
#ifndef __TLLASCIITOHEX_H_
#define __TLLASCIITOHEX_H_

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include <stdint.h>

/**
 * @brief  Convert Ascii '0' - '9', 'A' - 'F' to Hex 0 - 15, case-insensitive.
 * @return Result of conversion, -1 means error occurred.
 **/
int8_t
TLLAsciiToHex(uint8_t c);

#ifdef __cplusplus
  }
#endif

#endif /* __TLLASCIITOHEX_H_ */
