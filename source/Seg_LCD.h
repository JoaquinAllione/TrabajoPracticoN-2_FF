/******************************************************************/
//Seg_LCD.h	Rev 1.0	8/20/2014 EPH Initial version									//
//Author: Ethan Hettwer																						//
//Purpose:  Allow for easy control of Seg_LCD											//
/******************************************************************/

#ifndef __SEG_LCD_H_
#define __SEG_LCD_H_

#include "MKL46Z4.h"

//LETRAS MAYUSCULAS
#define LETRA_A 65
#define LETRA_B 66
#define LETRA_C 67
#define LETRA_D 68
#define LETRA_E 69
#define LETRA_F 70
#define LETRA_G 71
#define LETRA_H 72
#define LETRA_I 73
#define LETRA_J 74
#define LETRA_L 76
#define LETRA_O 79
#define LETRA_P 80
#define LETRA_S 83
#define LETRA_U 85
#define SIMB_right_1 200
#define SIMB_left_1 201
#define SIMB_top 202
#define SIMB_bottom 203
#define SIMB_middle 204
#define SIMB_right_2 205
#define SIMB_left_2 206
#define NOTHING 207

//LETRAS MINUSCULAS
#define LETRA_a 97
#define LETRA_b 98
#define LETRA_c 99
#define LETRA_d 100
#define LETRA_e 101
#define LETRA_g 103
#define LETRA_h 104
#define LETRA_i 105
#define LETRA_l 108
#define LETRA_n 110
#define LETRA_o 111
#define LETRA_r 114
#define LETRA_t 116
#define LETRA_u 117
#define LETRA_y 121

//Function Declarations
void SegLCD_Init(void);
void SegLCD_Set(uint8_t Value,uint8_t Digit);
void SegLCD_DisplayDecimal(uint16_t Value);
void SegLCD_DisplayHex(uint16_t Value);
void SegLCD_DisplayTime(uint8_t Value1, uint8_t Value2);
void SegLCD_DisplayError(uint8_t ErrorNum);
void SegLCD_Set_ASCII(uint8_t Value,uint8_t Digit);
//Define Number of Front and Back plane pins
#define LCD_NUM_FRONTPLANE_PINS 8
#define LCD_NUM_BACKPLANE_PINS 4

//Create macros for segments
#define LCD_SEG_D 0x11
#define LCD_SEG_E 0x22
#define LCD_SEG_G 0x44
#define LCD_SEG_F 0x88
#define LCD_SEG_DECIMAL 0x11
#define LCD_SEG_C 0x22
#define LCD_SEG_B 0x44
#define LCD_SEG_A 0x88
#define LCD_CLEAR 0x00

//Create Macros for each pin
#define LCD_FRONTPLANE0 37u
#define LCD_FRONTPLANE1 17u
#define LCD_FRONTPLANE2 7u
#define LCD_FRONTPLANE3 8u
#define LCD_FRONTPLANE4 53u
#define LCD_FRONTPLANE5 38u
#define LCD_FRONTPLANE6 10u
#define LCD_FRONTPLANE7 11u
#define LCD_BACKPLANE0 40u
#define LCD_BACKPLANE1 52u
#define LCD_BACKPLANE2 19u
#define LCD_BACKPLANE3 18u

//Macros for turning decimal points and colon on and off
#define SegLCD_DP1_On() LCD->WF8B[LCD_FRONTPLANE1]	 |= LCD_SEG_DECIMAL;
#define SegLCD_DP1_Off() LCD->WF8B[LCD_FRONTPLANE1] &= ~LCD_SEG_DECIMAL;
#define SegLCD_DP2_On() LCD->WF8B[LCD_FRONTPLANE3]	 |= LCD_SEG_DECIMAL;
#define SegLCD_DP2_Off() LCD->WF8B[LCD_FRONTPLANE3] &= ~LCD_SEG_DECIMAL;
#define SegLCD_DP3_On() LCD->WF8B[LCD_FRONTPLANE5]	 |= LCD_SEG_DECIMAL;
#define SegLCD_DP3_Off() LCD->WF8B[LCD_FRONTPLANE5] &= ~LCD_SEG_DECIMAL;
#define SegLCD_Col_On() LCD->WF8B[LCD_FRONTPLANE7]	 |= LCD_SEG_DECIMAL;
#define SegLCD_Col_Off() LCD->WF8B[LCD_FRONTPLANE7] &= ~LCD_SEG_DECIMAL;

#endif
