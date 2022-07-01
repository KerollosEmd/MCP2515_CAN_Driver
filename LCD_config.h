/****************************************/
/*				Name: kerollos Emad 	*/
/* 				Date: 18-9-2021			*/
/*				SWC	: LCD				*/
/*				Version: 1.0			*/
/****************************************/

#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H

/*Option :	1- LCD_u8_8BIT_MODE
 * 			2- LCD_u8_4BIT_MODE*/

#define LCD_u8_MODE 	LCD_u8_4BIT_MODE

//configuration for LCD PINs
//Rs PIN
#define LCD_u8_RS_PORT			DIO_u8_PORTA
#define LCD_u8_RS_PIN			DIO_u8_PIN6

//Rw PIN
#define LCD_u8_RW_PORT			DIO_u8_PORTA
#define LCD_u8_RW_PIN			DIO_u8_PIN5

//E PIN
#define LCD_u8_EN_PORT			DIO_u8_PORTA
#define LCD_u8_EN_PIN			DIO_u8_PIN4

//DATA PORT
#define LCD_u8_DATA_PORT		DIO_u8_PORTA

//macros for data pins for 4 bit mode

#define LCD_u8_PD7_PORT 		DIO_u8_PORTA
#define LCD_u8_PD7_PIN			DIO_u8_PIN0

#define LCD_u8_PD6_PORT 		DIO_u8_PORTA
#define LCD_u8_PD6_PIN			DIO_u8_PIN1

#define LCD_u8_PD5_PORT 		DIO_u8_PORTA
#define LCD_u8_PD5_PIN			DIO_u8_PIN2

#define LCD_u8_PD4_PORT 		DIO_u8_PORTA
#define LCD_u8_PD4_PIN			DIO_u8_PIN3

#endif
