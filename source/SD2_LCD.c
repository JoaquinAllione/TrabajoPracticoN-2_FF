/*
 * Joaquin Allione - 2020 - Año horrible -
 */
/*==================[inclusions]=============================================*/

// Standard C Included Files

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


// Project Included Files

#include "SD2_board.h"
#include "clock_config.h"
#include "fsl_smc.h"
#include "mma8451.h"
#include "Seg_LCD.h"
#include "fsl_lpsci.h"
#include "board.h"
#include "temp.h"
#include "key.h"
#include "clock.h"

#define T 500 //tiempo de parpadeo en mSeg.
#define T_MAX 10000 //lapso de tiempo para reiniciar el programa (en mSeg.)

int16_t X_acc; // VARIABLES PARA EL CALCULO Y ALMACENAMIENTO REFERENTES A LA ACELERACION
int16_t Y_acc;
int16_t Z_acc;
int16_t acc2_max;
int16_t acc2;
int16_t mod_acc; // FIN VARIABLES ACC

bool leer_SW1 = false; //indica si se debe o no "ver" el estado de los pulsadores

void mefPrincipal(void);

void LCD_Clear(void){ // PARA LIMPIAR EL LCD
	int8_t i;
	for(i=1;i<=4;i++){
		SegLCD_Set_ASCII(NOTHING,i);
	}
}

void main(void)
{
    /* Init board hardware. */
    BOARD_InitBootClocks();

    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);

    // Se inicializan funciones de la placa
    board_init();
    SegLCD_Init();
    /* inicializa interrupción de systick cada 1 ms */
    SysTick_Config(SystemCoreClock / 1000U);

    SegLCD_DP2_Off();
    mma8451_setDataRate(DR_50hz);
    Temp_disable();
    Temp2_disable();
    LCD_Clear(); //limpia el LCD

    APP_SetClockVlpr();

    while(true)
    {
    	if(get_FreeFall_Motion_detection() == 1){ //la deteccion de caida libre se consulta mediante la funcion que condiciona la sentencia "if"
    		mefPrincipal();
    	}
    }
}

typedef enum{
   EST_MEF_PRINCIPAL_INICIO = 1,
   EST_MEF_PRINCIPAL_LED_BLINK,
   EST_MEF_PRINCIPAL_LCD,
}estMefPrincipal_enum;

void mefPrincipal(void){

   static estMefPrincipal_enum estMefPrincipal = EST_MEF_PRINCIPAL_INICIO;

   switch(estMefPrincipal){

   case EST_MEF_PRINCIPAL_INICIO:

    	 NVIC_DisableIRQ(PORTC_PORTD_IRQn);
         Temp_enable(); //permite que se incremente el contador
         Temp_reset(); //reestablece el valor del contador (lo pone a cero)
         mma8451_init(); //inicializa las funciones del acelerometro para determinar las magnitudes en los tres ejes
         acc2_max = 900; //establezco un umbral a partir del cual comenzará a realizar las comparaciones para hallar el valor maximo
         board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_ON); //enciende el led rojo de la placa
         estMefPrincipal = EST_MEF_PRINCIPAL_LED_BLINK;

      break;

   case EST_MEF_PRINCIPAL_LED_BLINK:
	  // ---- Para el efecto de parpadeo del led integrado en la placa  ---- //
      if(Temp_get()>=T){
         Temp_reset();
         board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_TOGGLE);
      }
      // ------------------------------------------------------------------- //

      X_acc = mma8451_getAcX(); // toma los valores de las aceleraciones en cada eje
      Y_acc = mma8451_getAcY();
      Z_acc = mma8451_getAcZ();

      acc2 = pow(X_acc, 2) + pow(Y_acc, 2) + pow(Z_acc, 2); //calcula el modulo al cuadrado de la aceleracion

      if(acc2 > acc2_max){ // analiza el valor obtenido para determinar el maximo
    	  acc2_max = acc2;
    	  mod_acc = (int16_t)sqrt(acc2_max);
    	  SegLCD_DisplayDecimal(mod_acc); //muestra el valor maximo (cada vez que se cumple la condicion del "if")
    	  clear_cont(); //limpia el contador que indica cuantas mediciones de aceleracion NO superaron el maximo valor guardado anteriormente
      }

      if(get_cont() >= 10){ // si se tuvieron 10 o mas medidas de aceleracion que no superaron el valor maximo guardado anteriormente, se supone que el impacto terminó
    	  NVIC_DisableIRQ(PORTC_PORTD_IRQn); //deshabilita las interrupciones de los puertos especificados
    	  Temp_enable();
    	  Temp2_enable();
    	  leer_SW1 = true; //indica que se debe leer el pulsador en la interrupcion de Systick
    	  estMefPrincipal = EST_MEF_PRINCIPAL_LCD;
      }
      break;

   case EST_MEF_PRINCIPAL_LCD:
	   // ---- Para el efecto de parpadeo del led integrado en la placa  ---- //
	   if(Temp_get()>=T){
	      Temp_reset();
	      board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_TOGGLE);
	   }
	   // ------------------------------------------------------------------- //

	   if((key_getPressEv(BOARD_SW_ID_1))||(Temp2_get() >= T_MAX)){ // verifica si se cumplió el lapso de tiempo dado por T_MAX en mSeg.
	      Clear_FreeFall_Motion_state(); //limpia la bandera que indica que se produjo la interrupcion por caida libre
	      LCD_Clear(); //borra el LCD
	      leer_SW1 = false; //indica que no se debe leer el pulsador SW1
	      board_setLed(BOARD_LED_ID_ROJO, BOARD_LED_MSG_OFF); //apaga el led
	      NVIC_DisableIRQ(PORTC_PORTD_IRQn); //deshactiva interrupciones para reconfigurar el modo y el acelerometro.
	      APP_SetClockVlpr(); //pasa a modo VLPR al micro
	      Temp2_reset();
	      Temp2_disable();
	      mma8451_init_freefall(); //configura el acelerometro en modo FF
	      mma8451_setDataRate(DR_50hz);
	      estMefPrincipal = EST_MEF_PRINCIPAL_INICIO;
	   }
	   break;
   default:
      estMefPrincipal = EST_MEF_PRINCIPAL_INICIO;
      break;

   }

}

void SysTick_Handler(void)
{
   if(leer_SW1 == 1){
	   key_periodicTask1ms(); //lee el estado de los pulsadores en caso de ser necesario (al cumplirse la condicion del "if")
   }
   Temp_increase();
   Temp2_increase();
}
