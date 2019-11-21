/**
 * Copyright (c) 2018, LL Tang
 * All rights reserved
 *
 * @file    TLSTimer.h
 * @author  LL.T
 * @version 1.0.0
 * @date    2018/06/01
 * @brief   To optimize, use linked list instead.
 */

/* Define to prevent recursive inclusion */
#ifndef __TLSTIMER_H_
#define __TLSTIMER_H_

#ifdef __cplusplus
  extern "C" {
#endif	
		
/* Includes */
#include <stdint.h>
		
typedef uint64_t TLSTimType;
	
/**
* @brief Macros of hard timer TLSTimer based on
*/		
#define TLSTIM_BITS 16       // Bits of timer
#define TLSTIM_FCLK 9000000  // Clock freq of timer	

/**
 * @brief  Constructor for TLSTimer.
 *         Memory allocated by malloc(), note configuration of Heap Size. 
 * @cnt    Cnt of hard timer, must countdown.
 * @return Reference to a new TLSTimer
 */
void *  
newTLSTimer(uint32_t (*cnt)());		

/**
 * @brief Microsecond delay, blocking.
 * @cnt   Cnt of hard timer, must countdown.
 * @udly  Number of microsecond
 */
void 
TLSTimDly(uint32_t (*cnt)(), TLSTimType udly);

/**
 * @brief  Microsecond delay, non-blocking.
 * @timer  Instance of TLSTimer
 * @udly   Number of microsecond
 * @return Non-zero if delay time is up
 */
uint8_t
TLSTimIsDlyUp(void *timer, TLSTimType udly);

/**
 * @brief Interrupt Service Routine.
 */
void 
TLSTimISR(void);
		
#ifdef __cplusplus
  }
#endif		

#endif /* __TLSTIMER_H_ */
