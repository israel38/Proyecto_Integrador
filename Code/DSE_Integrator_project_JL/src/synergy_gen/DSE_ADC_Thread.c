/* generated thread source file - do not edit */
#include "DSE_ADC_Thread.h"

TX_THREAD DSE_ADC_Thread;
void DSE_ADC_Thread_create(void);
static void DSE_ADC_Thread_func(ULONG thread_input);
static uint8_t DSE_ADC_Thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.DSE_ADC_Thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_DSE_portreadADC) && !defined(SSP_SUPPRESS_ISR_ADC0)
SSP_VECTOR_DEFINE_CHAN(adc_scan_end_isr, ADC, SCAN_END, 0);
#endif
#endif
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_DSE_portreadADC) && !defined(SSP_SUPPRESS_ISR_ADC0)
SSP_VECTOR_DEFINE_CHAN(adc_scan_end_b_isr, ADC, SCAN_END_B, 0);
#endif
#endif
adc_instance_ctrl_t DSE_portreadADC_ctrl;
const adc_cfg_t DSE_portreadADC_cfg = { .unit = 0, .mode =
		ADC_MODE_CONTINUOUS_SCAN, .resolution = ADC_RESOLUTION_8_BIT,
		.alignment = ADC_ALIGNMENT_RIGHT, .add_average_count = ADC_ADD_OFF,
		.clearing = ADC_CLEAR_AFTER_READ_ON, .trigger = ADC_TRIGGER_SOFTWARE,
		.trigger_group_b = ADC_TRIGGER_SYNC_ELC, .p_callback = NULL,
		.p_context = &DSE_portreadADC, .scan_end_ipl = (BSP_IRQ_DISABLED),
		.scan_end_b_ipl = (BSP_IRQ_DISABLED), .calib_adc_skip = false, };
const adc_channel_cfg_t DSE_portreadADC_channel_cfg = { .scan_mask = (uint32_t)(
		((uint64_t) ADC_MASK_CHANNEL_0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | (0)),
/** Group B channel mask is right shifted by 32 at the end to form the proper mask */
.scan_mask_group_b = (uint32_t)(
		(((uint64_t) ADC_MASK_CHANNEL_0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
				| ((uint64_t) 0) | ((uint64_t) 0) | (0)) >> 32),
		.priority_group_a = ADC_GROUP_A_PRIORITY_OFF, .add_mask = (uint32_t)(
				(0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)
						| (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)
						| (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)
						| (0)), .sample_hold_mask = (uint32_t)((0) | (0) | (0)),
		.sample_hold_states = 24, };
/* Instance structure to use this module. */
const adc_instance_t DSE_portreadADC = { .p_ctrl = &DSE_portreadADC_ctrl,
		.p_cfg = &DSE_portreadADC_cfg, .p_channel_cfg =
				&DSE_portreadADC_channel_cfg, .p_api = &g_adc_on_adc };
#if (6) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_DSE_timer_readADC) && !defined(SSP_SUPPRESS_ISR_GPT0)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 0);
#endif
#endif
static gpt_instance_ctrl_t DSE_timer_readADC_ctrl;
static const timer_on_gpt_cfg_t DSE_timer_readADC_extend = { .gtioca = {
		.output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW }, .gtiocb = {
		.output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW } };
static const timer_cfg_t DSE_timer_readADC_cfg = { .mode = TIMER_MODE_PERIODIC,
		.period = 300, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50,
		.duty_cycle_unit = TIMER_PWM_UNIT_RAW_COUNTS, .channel = 0, .autostart =
				true, .p_callback = DSE_callback_timerADC, .p_context =
				&DSE_timer_readADC, .p_extend = &DSE_timer_readADC_extend,
		.irq_ipl = (6), };
/* Instance structure to use this module. */
const timer_instance_t DSE_timer_readADC = { .p_ctrl = &DSE_timer_readADC_ctrl,
		.p_cfg = &DSE_timer_readADC_cfg, .p_api = &g_timer_on_gpt };
TX_QUEUE DSE_QueueADC;
static uint8_t queue_memory_DSE_QueueADC[20];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void DSE_ADC_Thread_create(void) {
	/* Increment count so we will know the number of ISDE created threads. */
	g_ssp_common_thread_count++;

	/* Initialize each kernel object. */
	UINT err_DSE_QueueADC;
	err_DSE_QueueADC = tx_queue_create(&DSE_QueueADC, (CHAR *) "DSE_QueueADC",
			1, &queue_memory_DSE_QueueADC, sizeof(queue_memory_DSE_QueueADC));
	if (TX_SUCCESS != err_DSE_QueueADC) {
		tx_startup_err_callback(&DSE_QueueADC, 0);
	}

	UINT err;
	err = tx_thread_create(&DSE_ADC_Thread, (CHAR *) "DSE_ADC_Thread",
			DSE_ADC_Thread_func, (ULONG) NULL, &DSE_ADC_Thread_stack, 1024, 1,
			1, 1, TX_AUTO_START);
	if (TX_SUCCESS != err) {
		tx_startup_err_callback(&DSE_ADC_Thread, 0);
	}
}

static void DSE_ADC_Thread_func(ULONG thread_input) {
	/* Not currently using thread_input. */
	SSP_PARAMETER_NOT_USED(thread_input);

	/* Initialize common components */
	tx_startup_common_init();

	/* Initialize each module instance. */

	/* Enter user code for this thread. */
	DSE_ADC_Thread_entry();
}
