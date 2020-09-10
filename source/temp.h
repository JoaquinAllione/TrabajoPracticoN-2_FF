/*
 * brink.h
 *
 *  Created on: 8 abr. 2020
 *      Author: Joaquin
 */

#ifndef TEMP_H_
#define TEMP_H_
#include "SD2_board.h"

void Temp_increase(void);
void Temp_set(int32_t);
void Temp_enable(void);
void Temp_disable(void);
int32_t Temp_get(void);
void Temp_reset(void);

void Temp2_increase(void);
void Temp2_set(int32_t);
void Temp2_enable(void);
void Temp2_disable(void);
int32_t Temp2_get(void);
void Temp2_reset(void);

#endif /* TEMP_H_ */
