

/* ======== Includes  ========*/

#include "DSE_ADC_Thread.h"


/* DSE_ADC_Thread entry function */

/* ======== Global Variables  ========*/
uint16_t DSE_ADCread_u16 = 0U;
uint32_t dse_average_adc = 0U;
uint32_t dse_average_adc_assign = 0U;
uint16_t filtro_adc      = 0U;
uint16_t keep_datafilter[10] = {0U};
uint16_t dse_promedioADC[1]  = {0U};
uint16_t dse_status_queue;

void DSE_ADC_Thread_entry(void)
{
    //Inicializamos el Timer 0 para la lectura del ADC
    DSE_timer_readADC.p_api->open(DSE_timer_readADC.p_ctrl, DSE_timer_readADC.p_cfg);
    DSE_timer_readADC.p_api->start(DSE_timer_readADC.p_ctrl);

    //inicializamos la lectura del ADC
    DSE_portreadADC.p_api->open(DSE_portreadADC.p_ctrl, DSE_portreadADC.p_cfg);
    DSE_portreadADC.p_api->scanCfg(DSE_portreadADC.p_ctrl, DSE_portreadADC.p_channel_cfg);
    DSE_portreadADC.p_api->scanStart(DSE_portreadADC.p_ctrl);

    while (1)
    {
    	   if (filtro_adc < 10 )
    	   {
    		   DSE_portreadADC.p_api->read(DSE_portreadADC.p_ctrl, ADC_REG_CHANNEL_0, & DSE_ADCread_u16 );
    		   dse_average_adc += DSE_ADCread_u16;
    	       filtro_adc++;
    	   }
    	   else
    	   {
    		   dse_average_adc_assign = dse_average_adc / 10;
    	       filtro_adc = 0;
    	       dse_average_adc = 0;
    	   }

        tx_thread_sleep (1);
    }
}


void DSE_callback_timerADC(timer_callback_args_t *p_args)
{
   (void)p_args;
   dse_promedioADC[0] = (uint16_t)(dse_average_adc_assign);
   dse_status_queue = (uint16_t)tx_queue_send(&DSE_QueueADC, dse_promedioADC, TX_NO_WAIT);

}
