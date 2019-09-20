#include "mainTick.h"
#include "BtnDigitalFilter.h"

#define C_BTN_PRESSED IOPORT_LEVEL_LOW
#define C_BTN_RELEASED IOPORT_LEVEL_HIGH

#define C_100_ms (int)(100 / C_MAIN_TICK_MS)

#define C_BTN_LATCH C_100_ms

/************************************************************************
 Name:        SR_DigitalBtnFilter
 Description: Button filter
************************************************************************/
void SR_DigitalBtnFilter(ioport_level_t Input, struct stFilterBtnParameters *lpstFilterParam)
{
  switch(lpstFilterParam->state)
  {
      case 0:
          lpstFilterParam->trigger = false;
          if(Input == C_BTN_PRESSED)
            {
              lpstFilterParam->timeCnt = 0;
              lpstFilterParam->state = 1;
            }
          break;

      case 1:
          lpstFilterParam->trigger = false;
          (lpstFilterParam->timeCnt)++;
          if((lpstFilterParam->timeCnt) >= C_BTN_LATCH)
            {
              lpstFilterParam->state = 2;
            }
          else if(Input == C_BTN_RELEASED)
            {
              lpstFilterParam->state = 0;
            }
          break;

      case 2:
          lpstFilterParam->trigger = true;
          lpstFilterParam->state = 3;
          break;

      case 3:
          lpstFilterParam->trigger = false;
          if(Input == C_BTN_RELEASED)
            {
              lpstFilterParam->state = 0;
            }
          break;
      default:
          lpstFilterParam->state = 0;
          break;
  }
}

/************************************************************************
 Name:        SR_InitBtnFilter
 Description: Initialize Button Filter
************************************************************************/
void SR_InitBtnFilter(struct stFilterBtnParameters *lpstFilterParam)
{
  lpstFilterParam->state = 0;
  lpstFilterParam->timeCnt = 0;
  lpstFilterParam->trigger = false;
}
