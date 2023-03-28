/**
 * @file port_tx.h
 * @brief Header for port_tx.c file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

#ifndef PORT_TX_H_
#define PORT_TX_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include "port_system.h"

/* HW dependent includes */

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define IR_TX_0_ID = 0 
#define IR_TX_0_GPIO
#define IR_TX_0_PIN
/* Function prototypes and explanation -------------------------------------------------*/

void port_tx_init (uint8_t tx_id, bool status);

void port_tx_pwm_timer_set (uint8_t tx_id, bool status);

void port_tx_symbol_tmr_start ();

void port_tx_symbol_tmr_stop ();

uint32_t port_tx_tmr_get_tick ();
 

#endif
