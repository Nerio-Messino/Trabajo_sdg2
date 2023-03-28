/**
 * @file fsm_retina.c
 * @brief Retina FSM main file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

/* Includes ------------------------------------------------------------------*/
#include "fsm_retina.h"
#include "commands.h"
#include "fsm_button.h"
#include"fsm_tx.h"


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
    fsm_t *p_fsm_button;
    uint32_t long_button_press_ms;
    fsm_t *p_fsm_tx;
    uint32_t tx_codes_arr[COMMANDS_MEMORY_SIZE];
    uint8_t tx_codes_index;



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
    fsm_t *p_fsm = (fsm_t *)(p_this);
    fsm_init(p_this, fsm_trans_retina);
    long_button_press_ms();
    tx_codes_index();
    tx_codes_arr();
}

static void do_send_next_msg (fsm_t *p_this){
 fsm_tx_set_code(p_this, 0x00);
 fsm_button_reset_duration(p_this);
 tx_codes_index ++;

}

static bool check_short_pressed (fsm_t *p_this){
 fsm_t *p_fsm = (fsm_t *)(p_this); 
 int duration = fsm_button_get_duration(p_fsm);
 if (duration != 0 && duration <long_button_press_ms()){
    return true;
 }else{
    return false;
 }
}

fsm_trans_t fsm_trans_retina[]={

};
}
