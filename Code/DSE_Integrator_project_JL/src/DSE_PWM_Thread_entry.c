/* ======== Includes  ========*/

#include "DSE_PWM_Thread.h"
#include "DSE_ADC_Thread.h"
#include "data_types.h"

/* DSE_PWM_Thread entry function */
/* ======== Global Variables  ========*/
uint16_t dse_dutyCiclePWM[1]      ={0U};
uint16_t dse_status;
double dse_setPoint             = 0U;
uint16_t dse_counter              = 0U;
uint16_t rpm                      = 0U;
uint16_t dse_dutyCycle = 0;
uint16_t counter_freq              = 0U;
uint16_t SendData[4]={0};
uint16_t dse_counter_filtered_freq = 0U;
double dse_error  = 0;
double dse_error_anterior =0;
double dse_errorTotal = 0;
double kp = 4.0;//2
double ki = 1.0;//1
double kd = 2.0;//3
double rt = 0;
double yt = 0;
double iT = 1;
double kp_gain = 0;
double dse_dt = 0;
uint16_t dse_ut = 0;
uint16_t dse_salida = 0;
double iT0 = 0;
uint16_t max = 1000;
uint16_t min = 0;

//FILTER
uint16_t filter_counter = 0;


void DSE_PWM_Thread_entry(void)
{
        //Inicializamos el Timer 1 para la lectura del PWM
        dse_timerPWM.p_api->open(dse_timerPWM.p_ctrl, dse_timerPWM.p_cfg);
        dse_timerPWM.p_api->dutyCycleSet(dse_timerPWM.p_ctrl, 0, TIMER_PWM_UNIT_PERCENT_X_1000, 1);
        dse_timerPWM.p_api->start(dse_timerPWM.p_ctrl);

        //Inicializamos el Timer 2 para la lectura del Control
        dsw_timerControl.p_api->open(dsw_timerControl.p_ctrl, dsw_timerControl.p_cfg);
        dsw_timerControl.p_api->start(dsw_timerControl.p_ctrl);

        //Inicializamos la interrupción
        dse_sensorHall_Interrup.p_api->open(dse_sensorHall_Interrup.p_ctrl, dse_sensorHall_Interrup.p_cfg);

    while (1)
    {
        dse_status = (uint16_t)_txe_queue_receive(&DSE_QueueADC, dse_dutyCiclePWM, TX_WAIT_FOREVER);
        dse_setPoint = (uint32_t) dse_dutyCiclePWM[0] * 12;
        if(dse_setPoint >= 3000)
        {
            dse_setPoint = 3000;
        }
        dse_function_motor_control();
        tx_thread_sleep (10);


    }


}


void dse_sensorHall_CallBack (external_irq_callback_args_t *p_args)
{
    (void) p_args;
    dse_counter++;
//    uint16_t toogle = 0x0001;
//    toogle = toogle & dse_counter;
//    g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, toogle);
}

void dsw_timerControl_CallBack(timer_callback_args_t *p_args)
{
    (void)p_args;
	counter_freq = dse_counter;
	dse_counter = 0;
}
void dse_function_motor_control(void)
{
	rpm = counter_freq * (uint16_t)(75);
	dse_counter_filtered_freq = dse_function_filter(rpm);
	dse_errorTotal = (double)(dse_setPoint) - (double)(dse_counter_filtered_freq);
	dse_dutyCycle = dse_function_pid_control((int16_t)(dse_errorTotal));
//    SendData[0] = dse_ut/100;
//    SendData[0] = dse_dutyCiclePWM[0];
    dse_timerPWM.p_api->dutyCycleSet(dse_timerPWM.p_ctrl, (uint32_t)(dse_dutyCycle*100), TIMER_PWM_UNIT_PERCENT_X_1000, 1);
    //dse_status = (uint16_t)tx_queue_send(&datadisplay, SendData, TX_NO_WAIT);
    tx_thread_sleep (10);
}
uint16_t dse_function_pid_control(int16_t error)
{
	static uint16_t dse_function_dutyCycle = 0;
    iT = ki * (error + iT0);
    if(iT > max) iT = max;
    if(iT < -max) iT = -max;
    dse_dt = kd * (error - dse_error_anterior);
    if(dse_dt > max) dse_dt = max;
    if(dse_dt < -max) dse_dt = -max;
    kp_gain = kp * error;
    if(kp_gain > max) kp_gain = max;
    if(kp_gain < -max) kp_gain = -max;
    dse_ut = (uint16_t)(iT + kp * error + dse_dt);
    dse_salida = dse_ut;
    if ( dse_ut > max)
    {
        dse_ut = max;
    }
    if ( dse_ut < min )
    {
        dse_ut = min;
    }

    dse_function_dutyCycle = (uint16_t)(max - dse_ut);
    iT0 = iT;
    dse_error_anterior = error;
    return (uint16_t)(dse_function_dutyCycle);
}
uint16_t dse_function_filter(uint16_t input)
{
    static float dse_output_filtered_value = 0;

    if(DSE_FILTER_ORDER > 1)
    	dse_output_filtered_value = (float)((input + (float)((DSE_FILTER_ORDER - 1) * dse_output_filtered_value)) / DSE_FILTER_ORDER);
    else
    	dse_output_filtered_value = input;

    return (uint16_t)dse_output_filtered_value;
}


