/**
 * @file port_button.h
 * @brief Header for port_button.c file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

#ifndef PORT_BUTTON_H_
#define PORT_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>
#include <stdbool.h>
#include "port_tx.h"

/* HW dependent includes */


/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define BUTTON_0_ID =0 
#define BUTTON_0_GPIO
#define BUTTON_0_PIN
#define BUTTON_DEBOUNCE_TIME_MS


/* Function prototypes and explanation -------------------------------------------------*/
/*Esta funcion inicializa un boton */
void port_button_init (uint32_t button_id);

/*Esta funcion te devuelve true si el botton esta siendo pulsado*/
bool port_button_is_pressed(uint32_t button_id);

uint32_t port_button_get_tick();

#endif