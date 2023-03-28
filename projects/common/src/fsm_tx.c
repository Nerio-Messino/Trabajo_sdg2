/**
 * @file fsm_tx.c
 * @brief Infrared transmitter FSM main file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "fsm_tx.h"
#include "port_system.h"

/* Typedefs --------------------------------------------------------------------*/
typedef struct 
{
    /* data */
    fsm_t f;
    uint32_t code;
    uint8_t tx_id;
}fsm_tx_t;




/* Defines and enums ----------------------------------------------------------*/
/* Enums */
enum FSM_TX{
    WAIT_TX
};



static void _wait_for_tx_ticks (uint32_t ticks){

  uint32_t tick=port_tx_tmr_get_tick();

  while (tick-ticks < ticks)
  {
    
  }
  
}
static void _send_NEC_burst (uint8_t tx_id, uint32_t ticks_ON, uint32_t ticks_OFF){
 port_tx_pwm_timer_set(tx_id, true);
 _wait_for_tx_ticks(ticks_ON);
 port_tx_pwm_timer_set(tx_id,false);
 _wait_for_tx_ticks(ticks_OFF);
}
static bool check_tx_start (fsm_t *p_this){
fsm_tx_t *p_fsm = (fsm_tx_t *)(p_this);
if (p_fsm -> code = 0x00){
    return true;
}else{
    return false;
}
}

static void do_tx_start (fsm_t *p_this){
fsm_tx_t *p_fsm = (fsm_tx_t *)(p_this);

fsm_send_NEC_code(p_this->current_state,0x00);

}
 static fsm_trans_t fsm_trans_tx[]={
    /*aqui tengo dudas porque en principio solo hay un estado , pero hay que poner {NULL,..,NULL,..}??*/
    /*{WAIT_TX},
         {NULL},
    */

};
/* Other auxiliary functions */
void fsm_tx_set_code(fsm_t *p_this, uint32_t code)
{
fsm_tx_t *p_fsm = (fsm_tx_t *)(p_this);
if (code=0x00){}
else{
    p_fsm->code;
}
}

void fsm_send_NEC_code(uint8_t tx_id, uint32_t code)
{
    /* TO-DO alumnos */
    uint32_t mascara= 0x80000000;
    port_tx_symbol_tmr_start();
    _send_NEC_burst(tx_id,NEC_TX_PROLOGUE_TICKS_ON,NEC_TX_PROLOGUE_TICKS_OFF);
    while (0<mascara)
    {
        if (code&&mascara){
            _send_NEC_burst(tx_id,NEC_TX_SYM_1_TICKS_ON,NEC_TX_SYM_1_TICKS_OFF);
        }else{
            _send_NEC_burst(tx_id,NEC_TX_SYM_0_TICKS_ON,NEC_TX_SYM_0_TICKS_OFF);
        }
    mascara>>=1;
    }
    _send_NEC_burst(tx_id,NEC_TX_EPILOGUE_TICKS_ON,NEC_TX_EPILOGUE_TICKS_OFF);
    port_tx_symbol_tmr_stop();


}

bool fsm_tx_check_activity (fsm_t *p_this){

}

fsm_t *fsm_tx_new(uint8_t tx_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_tx_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_tx_init(p_fsm, tx_id);
    return p_fsm;
}

void fsm_tx_init(fsm_t *p_this, uint8_t tx_id)
{
    fsm_tx_t *p_fsm = (fsm_tx_t *)(p_this);
    fsm_init(p_this, fsm_trans_tx);

    p_fsm ->tx_id;
    p_fsm ->code;
    port_tx_init(tx_id,false);
}

