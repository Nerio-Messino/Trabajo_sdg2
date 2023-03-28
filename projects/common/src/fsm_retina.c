/**
 * @file fsm_retina.c
 * @brief Retina FSM main file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

/* Includes ------------------------------------------------------------------*/
#include "fsm_retina.h"

/* Defines and enums ----------------------------------------------------------*/
/* Defines */
#define COMMANDS_MEMORY_SIZE 3 /*!< Number of NEC commands stored in the memory of the system Retina */

/* Enums */
enum
{
    WAIT_TX = 0, /*!< **Single state in Version 2**. State to wait in transmission mode */
};

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure to define the Retina FSM.
 */
typedef struct
{
    fsm_t f; /*!< Retina FSM  */
    
    /* TO-DO alumnos */

} fsm_retina_t;

/* State machine input or transition functions */

/* State machine output or action functions */

/* Other auxiliary functions */
fsm_t *fsm_retina_new(fsm_t *p_fsm_button, uint32_t button_press_time, fsm_t *p_fsm_tx)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_retina_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_retina_init(p_fsm, p_fsm_button, button_press_time, p_fsm_tx);
    return p_fsm;
}

void fsm_retina_init(fsm_t *p_this, fsm_t *p_fsm_button, uint32_t button_press_time, fsm_t *p_fsm_tx)
{
    /* TO-DO alumnos */
}