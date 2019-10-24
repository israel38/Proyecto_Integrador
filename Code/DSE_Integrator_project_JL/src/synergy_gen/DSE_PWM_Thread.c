/* generated thread source file - do not edit */
#include "DSE_PWM_Thread.h"

TX_THREAD DSE_PWM_Thread;
void DSE_PWM_Thread_create(void);
static void DSE_PWM_Thread_func(ULONG thread_input);
static uint8_t DSE_PWM_Thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.DSE_PWM_Thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (4) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_dse_sensorHall_Interrup) && !defined(SSP_SUPPRESS_ISR_ICU0)
SSP_VECTOR_DEFINE( icu_irq_isr, ICU, IRQ0);
#endif
#endif
static icu_instance_ctrl_t dse_sensorHall_Interrup_ctrl;
static const external_irq_cfg_t dse_sensorHall_Interrup_cfg = { .channel = 0,
		.trigger = EXTERNAL_IRQ_TRIG_BOTH_EDGE, .filter_enable = true,
		.pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64, .autostart = true,
		.p_callback = dse_sensorHall_CallBack, .p_context =
				&dse_sensorHall_Interrup, .p_extend = NULL, .irq_ipl = (4), };
/* Instance structure to use this module. */
const external_irq_instance_t dse_sensorHall_Interrup = { .p_ctrl =
		&dse_sensorHall_Interrup_ctrl, .p_cfg = &dse_sensorHall_Interrup_cfg,
		.p_api = &g_external_irq_on_icu };
#if (5) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_dsw_timerControl) && !defined(SSP_SUPPRESS_ISR_GPT2)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 2);
#endif
#endif
static gpt_instance_ctrl_t dsw_timerControl_ctrl;
static const timer_on_gpt_cfg_t dsw_timerControl_extend = { .gtioca = {
		.output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW }, .gtiocb = {
		.output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW } };
static const timer_cfg_t dsw_timerControl_cfg = { .mode = TIMER_MODE_PERIODIC,
		.period = 25, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50,
		.duty_cycle_unit = TIMER_PWM_UNIT_RAW_COUNTS, .channel = 2, .autostart =
				true, .p_callback = dsw_timerControl_CallBack, .p_context =
				&dsw_timerControl, .p_extend = &dsw_timerControl_extend,
		.irq_ipl = (5), };
/* Instance structure to use this module. */
const timer_instance_t dsw_timerControl = { .p_ctrl = &dsw_timerControl_ctrl,
		.p_cfg = &dsw_timerControl_cfg, .p_api = &g_timer_on_gpt };
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_dse_timerPWM) && !defined(SSP_SUPPRESS_ISR_GPT1)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 1);
#endif
#endif
static gpt_instance_ctrl_t dse_timerPWM_ctrl;
static const timer_on_gpt_cfg_t dse_timerPWM_extend = { .gtioca = {
		.output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW }, .gtiocb = {
		.output_enabled = true, .stop_level = GPT_PIN_LEVEL_LOW } };
static const timer_cfg_t dse_timerPWM_cfg = { .mode = TIMER_MODE_PWM, .period =
		750, .unit = TIMER_UNIT_FREQUENCY_HZ, .duty_cycle = 50,
		.duty_cycle_unit = TIMER_PWM_UNIT_PERCENT_X_1000, .channel = 1,
		.autostart = true, .p_callback = NULL, .p_context = &dse_timerPWM,
		.p_extend = &dse_timerPWM_extend, .irq_ipl = (BSP_IRQ_DISABLED), };
/* Instance structure to use this module. */
const timer_instance_t dse_timerPWM = { .p_ctrl = &dse_timerPWM_ctrl, .p_cfg =
		&dse_timerPWM_cfg, .p_api = &g_timer_on_gpt };
TX_QUEUE datadisplay;
static uint8_t queue_memory_datadisplay[20];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void DSE_PWM_Thread_create(void) {
	/* Increment count so we will know the number of ISDE created threads. */
	g_ssp_common_thread_count++;

	/* Initialize each kernel object. */
	UINT err_datadisplay;
	err_datadisplay = tx_queue_create(&datadisplay, (CHAR *) "datadisplay", 1,
			&queue_memory_datadisplay, sizeof(queue_memory_datadisplay));
	if (TX_SUCCESS != err_datadisplay) {
		tx_startup_err_callback(&datadisplay, 0);
	}

	UINT err;
	err = tx_thread_create(&DSE_PWM_Thread, (CHAR *) "DSE_PWM_Thread",
			DSE_PWM_Thread_func, (ULONG) NULL, &DSE_PWM_Thread_stack, 1024, 1,
			1, 1, TX_AUTO_START);
	if (TX_SUCCESS != err) {
		tx_startup_err_callback(&DSE_PWM_Thread, 0);
	}
}

static void DSE_PWM_Thread_func(ULONG thread_input) {
	/* Not currently using thread_input. */
	SSP_PARAMETER_NOT_USED(thread_input);

	/* Initialize common components */
	tx_startup_common_init();

	/* Initialize each module instance. */

	/* Enter user code for this thread. */
	DSE_PWM_Thread_entry();
}
