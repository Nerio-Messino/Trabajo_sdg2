/**
 * @file fsm_tx.h
 * @brief Header for fsm_tx.c file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

#ifndef FSM_TX_H_
#define FSM_TX_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* Other includes */
#include "fsm.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
/* NEC transmission macros */
#define NEC_TX_TIMER_TICK_BASE_US 56.25 /*!< Time base in microseconds to create the ticks for the timer of symbols */
#define NEC_TX_PROLOGUE_TICKS_ON  16     /*!< Number of time base ticks for prologue ON in transmission  */
#define NEC_TX_PROLOGUE_TICKS_OFF 8   /*!< Number of time base ticks for prologue OFF in transmission  */
#define NEC_TX_SYM_0_TICKS_ON     1       /*!< Number of time base ticks for symbol 0 ON in transmission  */
#define NEC_TX_SYM_0_TICKS_OFF    1      /*!< Number of time base ticks for symbol 0 OFF in transmission  */
#define NEC_TX_SYM_1_TICKS_ON     1      /*!< Number of time base ticks for symbol 1 ON in transmission  */
#define NEC_TX_SYM_1_TICKS_OFF    3    /*!< Number of time base ticks for symbol 1 OFF in transmission  */
#define NEC_TX_EPILOGUE_TICKS_ON  1      /*!< Number of time base ticks for epilogue ON in transmission  */
#define NEC_TX_EPILOGUE_TICKS_OFF 3560  /*!< Number of time base ticks for epilogue OFF in transmission ~200 miliseconds */
#define NEC_PWM_FREQ_HZ                 /*!< PWM timer frequency in Hz */
#define NEC_PWM_DC                      /*!< PWM duty cycle 0-1  */

/* Function prototypes and explanation ----------------------------------------*/
uint32_t fsm_button_get_duration (fsm_t *p_this);

void fsm_button_reset_duration (fsm_t *p_this);

bool fsm_button_check_activity (fsm_t *p_this);

fsm_t *fsm_button_new(uint32_t debounce_time, uint32_t button_id);

void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id);
#endif