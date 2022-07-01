/*
 * main.c
 *
 *  Created on: Jul 1, 2022
 *      Author: pc
 */


#include "BIT_MATH.h"
#include "STD_Types.h"

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"

#include "LCD_interface.h"
#include "MCP2515_interface.h"


void main(){

	DIO_voidInit();
	SPI_voidMasterInit();
	LCD_voidInit();
	MCP_voidInit();



}
