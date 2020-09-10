/*
 * brink.c
 *
 *  Created on: 8 abr. 2020
 *      Author: Joaquin
 */

#include <temp.h>
#include "SD2_board.h"

bool temp_enable = false;

//============ TEMPORIZADOR =============//

int32_t temp;

int32_t Temp_get(void){return temp;}

void Temp_increase(void){
   if(temp_enable==true){
      temp++;
   }
}

void Temp_enable(void){
	temp_enable = true;
}

void Temp_disable(void){
	temp_enable = false;
}

void Temp_set(int32_t tiempo){temp = tiempo;}

void Temp_reset(void){
	temp = 0;
}

//========================================//

bool temp2_enable = false;

//============ TEMPORIZADOR =============//

int32_t temp2;

int32_t Temp2_get(void){return temp2;}

void Temp2_increase(void){
   if(temp2_enable==true){
      temp2++;
   }
}

void Temp2_enable(void){
	temp2_enable = true;
}

void Temp2_disable(void){
	temp2_enable = false;
}

void Temp2_set(int32_t tiempo){temp2 = tiempo;}

void Temp2_reset(void){
	temp2 = 0;
}


