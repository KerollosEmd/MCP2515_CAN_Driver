/****************************************/
/*				Name: kerollos Emad 	*/
/* 				Date: 18-9-2021			*/
/*				SWC	: LCD				*/
/*				Version: 1.0			*/
/****************************************/

/*LIB Layer*/
#include "STD_Types.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include <avr/delay.h>

/*MCAL*/
#include "DIO_interface.h"

/*HAL*/
#include "LCD_private.h"
#include "LCD_config.h"
#include "LCD_interface.h"

void LCD_voidInit(void) //initialize the LCD for 8-bit mode
{

	_delay_ms(35);
#if (LCD_u8_8BIT_MODE==LCD_u8_MODE)
	/* Send Function Set Command */
	LCD_voidWriteCommand(LCD_FunctionSet8bit);

#elif (LCD_u8_4BIT_MODE==LCD_u8_MODE)
	/*send first step of function set command*/
	//1-Rs =0  	select Data Register
	DIO_u8SetPinValue(LCD_u8_RS_PORT, LCD_u8_RS_PIN, DIO_u8_LOW);

	//Rw =0 	Write Operation
	DIO_u8SetPinValue(LCD_u8_RW_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);
	//3-Send 4_MSB Data byte to LCD
//	DIO_u8SetPortValue(LCD_u8_DATA_PORT, 0b00100000);
	PRIVATE_voidSetHalfPort(0b00100000);
	//4-enable
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_LOW);
#else
#error "wrong choice"
#endif
	_delay_us(40);
	/* Display on off Control */
	LCD_voidWriteCommand(LCD_Disp_Curser_Bl);
	_delay_us(40);
	/* Display Clear */
	LCD_voidWriteCommand(LCD_Clear);
	_delay_ms(2);
	/* Entry Mode Set */
	LCD_voidWriteCommand(LCD_EntryMode);
}

void LCD_voidWriteChar(u8 Copy_u8Char) {
	/*
	 *	function instruction
	 1-Rs =1  	select Data Register
	 2-Rw =0 	Write Operation
	 3-Send Data byte to LCD
	 4-Send Enable Pulse
	 */
#if(LCD_u8_8BIT_MODE==LCD_u8_MODE)
	//1-Rs =1  	select Data Register
	DIO_u8SetPinValue(LCD_u8_RS_PORT, LCD_u8_RS_PIN, DIO_u8_HIGH);

	//Rw =0 	Write Operation
	DIO_u8SetPinValue(LCD_u8_RW_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);

	//3-Send Data byte to LCD
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Char);

	//4-enable
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_HIGH);
	_delay_ms(2);

	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_LOW);

#elif (LCD_u8_4BIT_MODE==LCD_u8_MODE)
	//1-Rs =1  	select Data Register
	DIO_u8SetPinValue(LCD_u8_RS_PORT, LCD_u8_RS_PIN, DIO_u8_HIGH);

	//Rw =0 	Write Operation
	DIO_u8SetPinValue(LCD_u8_RW_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);
	//3-Send 4_MSB Data byte to LCD
	//DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Char);
	PRIVATE_voidSetHalfPort(Copy_u8Char);
	//4-Enable
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_LOW);

	//3-Send 4_LSB Data byte to LCD
	//DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Char << 4);
	PRIVATE_voidSetHalfPort(Copy_u8Char<<4);
	//4-Enable
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_LOW);

#else
#error "Wrong choice"
#endif

}

void LCD_voidWriteCommand(u8 Copy_u8Cmnd) {
	/*
	 *	function instruction
	 1-Rs =1  	select Data Register
	 2-Rw =0 	Write Operation
	 3-Send Data byte to LCD
	 4-Send Enable Pulse
	 */
#if(LCD_u8_8BIT_MODE==LCD_u8_MODE)
	//1-Rs =1  	select Data Register
	DIO_u8SetPinValue(LCD_u8_RS_PORT, LCD_u8_RS_PIN, DIO_u8_LOW);

	//Rw =0 	Write Operation
	DIO_u8SetPinValue(LCD_u8_RW_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);

	//3-Send Data byte to LCD
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd);

	//4-
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_LOW);

#elif (LCD_u8_4BIT_MODE==LCD_u8_MODE)
	//1-Rs =0  	select Data Register
	DIO_u8SetPinValue(LCD_u8_RS_PORT, LCD_u8_RS_PIN, DIO_u8_LOW);

	//Rw =0 	Write Operation
	DIO_u8SetPinValue(LCD_u8_RW_PORT, LCD_u8_RW_PIN, DIO_u8_LOW);
	//3-Send 4_MSB Data byte to LCD
//	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd);
	PRIVATE_voidSetHalfPort(Copy_u8Cmnd);
	//4-Enable
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_LOW);

	//3-Send 4_LSB Data byte to LCD
//	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Cmnd << 4);
	PRIVATE_voidSetHalfPort(Copy_u8Cmnd<<4);
	//4-Enable
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_u8_EN_PORT, LCD_u8_EN_PIN, DIO_u8_LOW);

#else
#error "Wrong choice"
#endif
}

void LCD_voidWriteString(u8* Copy_Pu8String) {
	u32 Local_u32Index;

	for (Local_u32Index = 0; Copy_Pu8String[Local_u32Index] != 0;
			Local_u32Index++) {
		LCD_voidWriteChar(Copy_Pu8String[Local_u32Index]);
	}
}

void LCD_voidWritNumber(u32 Copy_u32Number) {
	//local variables
	u8 local_u8Array_Asmpeller[16];
	u8 local_u8Length = 0;

	u32 local_u32num = Copy_u32Number;
	u32 Local_u32Index;

	while (local_u32num != 0) {
		local_u8Length++;
		local_u32num /= 10;
	}

	//Split the whole number to units , tens , hundreds ,.... etc.
	for (Local_u32Index = 0; Copy_u32Number != 0; Local_u32Index++) {
		local_u8Array_Asmpeller[local_u8Length - (Local_u32Index + 1)] = '0'
				+ (u8) (Copy_u32Number % 10); //convert integer to ascii
		Copy_u32Number /= 10;
	}
	local_u8Array_Asmpeller[local_u8Length] = '\0';

	//sprintf(local_u8Array_Asmpeller,"%d",Copy_u32Number);//second method

	LCD_voidWriteString(local_u8Array_Asmpeller);

}

void LCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos) {
	u8 Local_u8Address;
	if (Copy_u8YPos == LCD_u8_LINE_1) {
		Local_u8Address = Copy_u8XPos;
	} else if (Copy_u8YPos == LCD_u8_LINE_2) {
		Local_u8Address = Copy_u8XPos + 0x40;
	}

	LCD_voidWriteCommand(SET_BIT(Local_u8Address, 7));

}

static void PRIVATE_voidSetHalfPort(u8 Copy_u8Data) {
	if (GET_BIT(Copy_u8Data, 7)) {
		DIO_u8SetPinValue(LCD_u8_PD7_PORT, LCD_u8_PD7_PIN, DIO_u8_HIGH);
	} else {
		DIO_u8SetPinValue(LCD_u8_PD7_PORT, LCD_u8_PD7_PIN, DIO_u8_LOW);
	}
	if (GET_BIT(Copy_u8Data, 6)) {
		DIO_u8SetPinValue(LCD_u8_PD6_PORT, LCD_u8_PD6_PIN, DIO_u8_HIGH);
	} else {
		DIO_u8SetPinValue(LCD_u8_PD6_PORT, LCD_u8_PD6_PIN, DIO_u8_LOW);
	}

	if (GET_BIT(Copy_u8Data, 5)) {
		DIO_u8SetPinValue(LCD_u8_PD5_PORT, LCD_u8_PD5_PIN, DIO_u8_HIGH);
	} else {
		DIO_u8SetPinValue(LCD_u8_PD5_PORT, LCD_u8_PD5_PIN, DIO_u8_LOW);
	}

	if (GET_BIT(Copy_u8Data, 4)) {
		DIO_u8SetPinValue(LCD_u8_PD4_PORT, LCD_u8_PD4_PIN, DIO_u8_HIGH);
	} else {
		DIO_u8SetPinValue(LCD_u8_PD4_PORT, LCD_u8_PD4_PIN, DIO_u8_LOW);
	}

}

