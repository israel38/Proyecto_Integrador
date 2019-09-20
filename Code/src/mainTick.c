/**********************************************************************

  FILE        : mainTick.c
  DATE        : 26/04/2019
  DESCRIPTION : Set and reset main tick
  PROJECT     : DSE: 2.2.6 Maquina de estados

**********************************************************************/

#include "hal_data.h"
#include "mainTick.h"

bool bfMainTickElapsed = false;
int u16TickCnt = C_MAIN_TICK_MS;
timer_size_t counts = 0;


/************************************************************************
 Name:        FN_bfPerformTick
 Description: Set main tick
************************************************************************/
bool FN_bfPerformTick(void)
{
  g_timer0.p_api->counterGet(g_timer0.p_ctrl, &counts);

  if(counts > (COUNTS_PER_MILLISECOND))
    {
      // Reset the timer to 0
      g_timer0.p_api->reset(g_timer0.p_ctrl);

      u16TickCnt++;
      if(u16TickCnt >= C_MAIN_TICK_MS)
        {
          u16TickCnt = 0;
          bfMainTickElapsed = true;
        }
    }

  return bfMainTickElapsed;
}

/************************************************************************
 Name:        SR_ClearMainTick  
 Description: Clear main tick flag
************************************************************************/
void SR_ClearMainTick(void)
{
  bfMainTickElapsed = false;
}
