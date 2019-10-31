/* generated thread header file - do not edit */
#ifndef DSE_PWM_THREAD_H_
#define DSE_PWM_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus 
extern "C" void DSE_PWM_Thread_entry(void);
#else 
extern void DSE_PWM_Thread_entry(void);
#endif
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#ifdef __cplusplus
extern "C" {
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t dse_sensorHall_Interrup;
#ifndef dse_sensorHall_CallBack
void dse_sensorHall_CallBack(external_irq_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t dsw_timerControl;
#ifndef dsw_timerControl_CallBack
void dsw_timerControl_CallBack(timer_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t dse_timerPWM;
#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
extern TX_QUEUE datadisplay;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* DSE_PWM_THREAD_H_ */
