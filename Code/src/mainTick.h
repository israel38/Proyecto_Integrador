/**********************************************************************

  FILE        : mainTick.h
  DATE        : 26/04/2019
  DESCRIPTION : Set and reset main tick
  PROJECT     : DSE: 2.2.6 Maquina de estados

**********************************************************************/

#ifndef __MAIN_TICK__
#define __MAIN_TICK__

#define bool    _Bool
#define true    1
#define false   0

#define COUNTS_PER_MILLISECOND  (120E6 / 1000)
#define C_MAIN_TICK_MS  10

extern bool FN_bfPerformTick(void);
extern void SR_ClearMainTick(void);
#endif
