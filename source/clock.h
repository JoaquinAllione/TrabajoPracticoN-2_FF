/*
 * clock.h
 *
 *  Created on: 28 may. 2020
 *      Author: Joaquin
 */

#ifndef CLOCK_H_
#define CLOCK_H_
#include "fsl_smc.h"

void APP_SetClockVlpr(void);
void APP_SetClockRunFromVlpr(void);
void APP_ShowPowerMode(smc_power_state_t currentPowerState);

#endif /* CLOCK_H_ */
