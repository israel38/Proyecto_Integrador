/*
 * data_types.h
 *
 *  Created on: 25/10/2019
 *      Author: Jhon-pc
 */

#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

#define DSE_FILTER_ORDER 16

void dse_function_motor_control(void);
uint16_t dse_function_pid_control(int16_t error);
uint16_t dse_function_filter(uint16_t input);


#endif /* DATA_TYPES_H_ */
