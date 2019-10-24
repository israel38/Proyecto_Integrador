/* generated thread header file - do not edit */
#ifndef DSE_ADC_THREAD_H_
#define DSE_ADC_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus 
extern "C" void DSE_ADC_Thread_entry(void);
#else 
extern void DSE_ADC_Thread_entry(void);
#endif
#include "r_adc.h"
#include "r_adc_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#ifdef __cplusplus
extern "C" {
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t DSE_portreadADC;
#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t DSE_timer_readADC;
#ifndef DSE_callback_timerADC
void DSE_callback_timerADC(timer_callback_args_t *p_args);
#endif
extern TX_QUEUE DSE_QueueADC;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* DSE_ADC_THREAD_H_ */
