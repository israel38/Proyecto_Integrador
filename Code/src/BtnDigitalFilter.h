/*
 * BtnDigitalFilter.h
 *
 *  Created on: 17/05/2019
 *      Author: cramexla
 */

#ifndef BTNDIGITALFILTER_H_
#define BTNDIGITALFILTER_H_

#include "hal_data.h"
#include "r_ioport_api.h"

struct stFilterBtnParameters
  {
    int state;
    int timeCnt;
    int trigger;
  };

extern void SR_InitBtnFilter(struct stFilterBtnParameters *lpstFilterParam);
extern void SR_DigitalBtnFilter(ioport_level_t Input, struct stFilterBtnParameters *lpstFilterParam);

#endif /* BTNDIGITALFILTER_H_ */
