/***********************************************************************************************************************
 * Copyright [2015-2017] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : hal_entry.c
* Description  : This is a very simple example application that blinks all LEDs on a board.
***********************************************************************************************************************/

#include "hal_data.h"
#include "mainTick.h"
#include "BtnDigitalFilter.h"

#define C_100_ms (int)(100 / C_MAIN_TICK_MS)
#define C_200_ms (int)(200 / C_MAIN_TICK_MS)
#define C_500_ms (int)(500 / C_MAIN_TICK_MS)

#define C_BTN_PRESSED IOPORT_LEVEL_LOW
#define C_BTN_RELEASED IOPORT_LEVEL_HIGH
#define C_LED_ON IOPORT_LEVEL_LOW
#define C_LED_OFF IOPORT_LEVEL_HIGH
#define PWM_FACTOR 100/255
#define SAMPLES 20
ioport_level_t P05_status;
ioport_level_t P06_status;
ioport_level_t P64_status;
ioport_level_t Led1;
ioport_level_t Led2;
ioport_level_t Led3;

ioport_level_t Sw4Filtered;
ioport_level_t Sw5Filtered;

int blinkCnt;
int adcData = 0;
int pwm_set = 0;
int counter = 0;

struct stFilterBtnParameters Sw4Filter;
struct stFilterBtnParameters Sw5Filter;

bool enableLed3Process;

int dutyCycle;

/************************************************************************
 Name:        hal_entry
 Description: Main thread
************************************************************************/
void hal_entry(void)
{

    bool bfmainTick;
    long int sum = 0;
    g_timer0.p_api->open (g_timer0.p_ctrl, g_timer0.p_cfg);
    g_timer0.p_api->start (g_timer0.p_ctrl);
    SR_InitBtnFilter(&Sw4Filter);
    SR_InitBtnFilter(&Sw5Filter);

    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);



    while(1)
    {
      
      bfmainTick = FN_bfPerformTick();
      if(bfmainTick == true)
        {
          SR_ClearMainTick();

          /******************************************************/
          /*       READ INPUTS                                  */
          /******************************************************/
          g_ioport.p_api->pinRead(IOPORT_PORT_00_PIN_05, &P05_status);
          g_ioport.p_api->pinRead(IOPORT_PORT_00_PIN_06, &P06_status);// S4
          g_ioport.p_api->pinRead(IOPORT_PORT_06_PIN_04, &P64_status);


          SR_DigitalBtnFilter(P06_status, &Sw4Filter);
          SR_DigitalBtnFilter(P05_status, &Sw5Filter);

          for(counter = 0; counter < SAMPLES; counter++)
          {
              g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &adcData);
              sum += adcData;
          }
          sum = sum / SAMPLES;
          pwm_set = sum;
          pwm_set = adcData*PWM_FACTOR;
          sum = 0;
          /******************************************************/
          /*       INSERT CODE HERE                             */
          /******************************************************/

          if(Sw4Filter.trigger == true)
            {
              Led1 = !Led1;
            }

          if(Led1)
            {
              g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
              g_timer1.p_api->start (g_timer1.p_ctrl);
            }
          else
          {
              g_timer1.p_api->close(g_timer1.p_ctrl);
          }
          if(Sw5Filter.trigger == true)
            {
              enableLed3Process = !enableLed3Process;
            }
          
          if(true)
            {
              blinkCnt++;
              if(blinkCnt == C_500_ms)
                {
                  Led3 = !Led3;
                }
              if(blinkCnt == C_500_ms*2)
              {
                  Led3 = !Led3;
                  blinkCnt = 0;
              }
            }
          else
            {
              Led3 = C_LED_OFF;
            }

          if(P64_status == IOPORT_LEVEL_HIGH)
              {
                  Led2 = C_LED_ON;
              }
          else
              {
                  Led2 = C_LED_OFF;
              }

          /******************************************************/
          /*       REFRESH OUTPUTS                              */
          /******************************************************/
          g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_00, Led1);
          g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_01, Led2);
          g_ioport.p_api->pinWrite(IOPORT_PORT_06_PIN_02, Led3);

	  g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, pwm_set, TIMER_PWM_UNIT_PERCENT, 1);
        }
    }   
}

