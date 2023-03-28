/**
 * @file port_tx.c
 * @brief Portable functions to interact with the infrared transmitter FSM library.
 * @author alumno1
 * @author alumno2
 * @date fecha
 */

/* Includes ------------------------------------------------------------------*/
#include "port_tx.h"
#include "fsm_tx.h"

/* Defines --------------------------------------------------------------------*/
#define ALT_FUNC1_TIM2 /*!< TIM2 Alternate Function mapping */

/* IMPORTANT
The timer symbol is the same for all the TX, so it is not in the structure of TX. It has been decided to be the TIM1. It is like a systick but faster.
*/

/* Typedefs --------------------------------------------------------------------*/
typedef struct 
{
  /* data */
  GPIO_TypeDef p_port;
  uint8_t      pin;
  uint8_t      alt_func;
}port_tx_hw_t;


/* Global variables ------------------------------------------------------------*/
static symbol_tick;

static port_tx_hw_t transmitters_arr[]={
  /*Aqui no entiendo que es lo que esta mal, he inicializado los valores literalmente como me pone*/
  [IR_TX_0_ID]= {.p_port = IR_TX_0_GPIO, .pin =IR_TX_0_PIN, .alt_func =ALT_FUNC1_TIM2},
};

/* Infrared transmitter private functions */
static void _timer_symbol_setup()
{
  /* TO-Do alumnos */
  RCC  ->  APB1ENR |= RCC_APB1ENR_TIM2EN ;
  TIM2 -> CR1 = 0x0000 ;
  TIM2 -> CR1 &= ~ TIM_CR1_CEN ;
  TIM2 -> CNT = 0;
  TIM2 -> ARR = 5625; /*Pendientes de revisar*/
  TIM2 -> PSC = 399;
  TIM2 -> EGR = TIM_EGR_UG ;
  TIM2 -> SR = ~ TIM_SR_UIF ;
  TIM2 -> DIER |= TIM_DIER_UIE ;

  /* Finally, set the priority and enable interruptions globally. */
  NVIC_SetPriority(TIM1_UP_TIM10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0)); /* Priority 1, sub-priority 0 */
  NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);                                                          /* Enable interrupt */
}

static void _timer_pwm_setup(uint32_t tx_id)
{
 RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN ;
 TIM2 -> CNT = 0;
 TIM2 -> ARR = 63999;
 TIM2 -> PSC = 4;/*Pendientes de revisar*/
 TIM2 -> EGR = TIM_EGR_UG ;
 TIM2 -> CCER &= ~ TIM_CCER_CC1E ;
 /*TIM2 -> CCMR1 |= TIM_AS_PWM1_MASK ;
 TIM2 -> CCMR1 |= TIM_CCMR1_OC1PE ;*/
 TIM2 -> CCR1 = 32000;
 TIM2 -> CCER |= TIM_CCER_CC1E ;
 TIM2 -> CR1 |= TIM_CR1_CEN;

}

/* Public functions */
void port_tx_init(uint8_t tx_id, bool status)
{
port_system_gpio_config(GPIO_MODE_ALTERNATE,pin, ALT_FUNC1_TIM2, tx_id);/*No se exactamente a que pin se refiere*/
port_system_gpio_config_alternate(GPIO_MODE_ALTERNATE,ALT_FUNC1_TIM2,tx_id);
_timer_symbol_setup();
_timer_pwm_setup(tx_id);
port_tx_pwm_timer_set(tx_id,status);

}


/* In order to make the academic effort of configuring the PWM, the values: timer, channel and masks are hardcoded and this function is not generic for any timer/channel. It is not the best way, but it is as it. */
void port_tx_pwm_timer_set(uint8_t tx_id, bool status)
{
  if (status=true){
    TIM2 -> CCER |= TIM_CCER_CC1E ;
    TIM2 -> CR1 |= TIM_CR1_CEN ;
  }else{
    TIM2 -> CCER &= ~TIM_CCER_CC1E;
    TIM2 -> CR1 &= ~TIM_CR1_CEN ;
  }
  
}

void port_tx_symbol_tmr_start()
{
  TIM2 -> CNT = 0;
  TIM2 -> CR1 |= TIM_CR1_CEN;
  symbol_tick = 0;
}

void port_tx_symbol_tmr_stop()
{
  TIM2 -> CR1 &= ~TIM_CR1_CEN;
}

uint32_t port_tx_tmr_get_tick()
{
  return symbol_tick;
}

//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------

void TIM1_UP_TIM10_IRQHandler(void)
{
 TIM2 ->SR = ~ TIM_SR_UIF ;
 symbol_tick++;
}