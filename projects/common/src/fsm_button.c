/**
 * @file fsm_button.c
 * @brief Button FSM main file.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

/* Includes ------------------------------------------------------------------*/
#include "fsm_button.h"
#include "port_button.h"
#include "port_system.h"

/* Typedefs --------------------------------------------------------------------*/
typedef struct 
{
   fsm_t f; /* Boton FSM */
   uint32_t debounce_time;
   uint32_t next_timeout;
   uint32_t tick_pressed;
   uint32_t duration;
   uint32_t button_id;
} fsm_button_t;

/* Defines and enums ----------------------------------------------------------*/
/* Enums */
enum FSM_STATES{
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED_WAIT,
    BUTTON_PRESSED,
    BUTTON_RELEASED_WAIT,

};



/* State machine input or transition functions */


/* State machine output or action functions */


/* Other auxiliary functions */
void port_button_gpio_setup(void){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOA-> MODER &= ~MODER13_MASK;
    GPIOA-> PUPDR &= ~PUDR13_MASK;
    GPIOA-> MODER |= MODER13_AS_INPUT;
    GPIOA-> PUPDR |= PUPDR13_AS_NOPUPD;
}
bool port_button_read(void){
    return ( bool )(GPIOA ->IDR & IDR13_MASK );
}

static bool check_button_pressed( fsm_t * p_fsm ){
 return  !check_button_released ( p_fsm );
}

static bool check_button_released( fsm_t * p_fsm ){
    return port_button_read();
}

static bool check_timeout ( fsm_t * p_fsm ){
    fsm_button_t * p_button = ( fsm_button_t *)p_fsm;
    uint32_t now = port_system_get_millis ();
    return now > p_button -> next_timeout ;
}

static void do_store_tick_pressed ( fsm_t * p_fsm )
{
    fsm_button_t * p_button = ( fsm_button_t *) p_fsm ;
    uint32_t now = port_system_get_millis ();
    p_button -> tick_pressed = now ;
    p_button -> next_timeout = now + p_button -> debounce_time ;
}

static void do_set_duration ( fsm_t * p_fsm ){

 fsm_button_t * p_button = ( fsm_button_t *) p_fsm ;
 uint32_t now = port_system_get_millis ();
 p_button -> duration = now - p_button -> tick_pressed ;
 p_button -> next_timeout = now + p_button -> debounce_time ;
}

static fsm_trans_t fsm_trans_button[] = {
  { BUTTON_RELEASED , check_button_pressed , BUTTON_PRESSED_WAIT ,do_store_tick_pressed },
  { BUTTON_PRESSED_WAIT , check_timeout , BUTTON_PRESSED , NULL },
  { BUTTON_PRESSED , check_button_released , BUTTON_RELEASED_WAIT , do_set_duration } ,
  { BUTTON_RELEASED_WAIT , check_timeout , BUTTON_RELEASED , NULL },
  { -1 , NULL , -1, NULL }

};

uint32_t fsm_button_get_duration ( fsm_t * p_fsm ){
    fsm_button_t * p_button = ( fsm_button_t *) p_fsm ;
    return p_button -> duration ;

}
void fsm_button_reset_duration ( fsm_t * p_fsm ){
    fsm_button_t * p_button = ( fsm_button_t *) p_fsm ;
    p_button -> duration = 0;
}



fsm_t *fsm_button_new(uint32_t debounce_time, uint32_t button_id)
{
    fsm_t *p_fsm = malloc(sizeof(fsm_button_t)); /* Do malloc to reserve memory of all other FSM elements, although it is interpreted as fsm_t (the first element of the structure) */
    fsm_button_init(p_fsm, debounce_time, button_id);
    return p_fsm;
}

void fsm_button_init(fsm_t *p_this, uint32_t debounce_time, uint32_t button_id){
     fsm_button_t *p_fsm = (fsm_button_t *)(p_this);
    fsm_init(p_this, fsm_trans_button);
    p_this -> debounce_time = debounce_time ;
    p_this -> tick_pressed = 0;
    p_this -> duration = 0;
    port_button_gpio_setup ();
    /*No entiendo porque no me reconoce los campos*/
}

