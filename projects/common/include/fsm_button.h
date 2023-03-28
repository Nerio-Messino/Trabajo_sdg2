/**
 * @file fsm_button.h
 * @brief Header for fsm_button.c file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

#ifndef FSM_BUTTON_H_
#define FSM_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>

/* Other includes */
#include "fsm.h"

/* Function prototypes and explanation -------------------------------------------------*/

uint32_t fsm_button_get_duration (fsm_t *p_this);

void fsm_button_reset_duration (fsm_t *p_this);

bool fsm_button_check_activity (fsm_t *p_this);

fsm_t *fsm_button_new(uint32_t debounce_time, uint32_t button_id);

void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id);

#endif