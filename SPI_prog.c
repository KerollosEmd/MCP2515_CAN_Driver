/*
 * SPI_prog.c
 *
 *  Created on: Apr 6, 2022
 *      Author: KeroEmad
 */
#include "STD_Types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"

static void(*SPI_PtrToFun)(void)=NULL;

/*
 * SPI Master Initialization Function.
 * It takes no arguments.
 * Data order is set to zero (default) to send MSB first.
 * Configures the MOSI and SCK as output pins.
 * Clock rate (default) F_CPU/16.
 */
void SPI_voidMasterInit(void){
	/*Set MOSI and SCK as output pins, all others as input*/
	DIO_u8SetPinDirection(SPI_u8_PORT,SPI_PIN_MOSI,DIO_u8_OUTPUT);
	DIO_u8SetPinDirection(SPI_u8_PORT,SPI_PIN_SCK,DIO_u8_OUTPUT);
	DIO_u8SetPinDirection(SPI_u8_PORT,SPI_PIN_MISO,DIO_u8_INPUT_UP);
	DIO_u8SetPinDirection(SPI_u8_PORT,SPI_PIN_SS,DIO_u8_OUTPUT);
	/*Enable SPI peripheral*/
	SET_BIT(SPI_u8_CONTROL_REG,6);
	/*Enable Master Mode*/
	SET_BIT(SPI_u8_CONTROL_REG,4);
	/*Set Clock rate to F_CPU/16*/
	SET_BIT(SPI_u8_CONTROL_REG,0);
}

/*
 * SPI Slave Initialization Function.
 * It takes no arguments.
 * Data order is set to zero (default) to receive MSB first.
 * Configure MISO as Output.
 */
void SPI_voidSlaveInit(void){
	/*Set MISO as output, all others as input*/
	DIO_u8SetPinDirection(SPI_u8_PORT,SPI_PIN_MOSI,DIO_u8_INPUT_UP);
	DIO_u8SetPinDirection(SPI_u8_PORT,SPI_PIN_SCK,DIO_u8_INPUT_FLOATING);
	DIO_u8SetPinDirection(SPI_u8_PORT,SPI_PIN_MISO,DIO_u8_OUTPUT);
	DIO_u8SetPinDirection(SPI_u8_PORT,SPI_PIN_SS,DIO_u8_INPUT_UP);
	/*Enable SPI*/
	SET_BIT(SPI_u8_CONTROL_REG,6);
}

void SPI_voidMasterTransmission(u8 Copy_u8Data){
	/*Start Transmission*/
	SPI_u8_DATA_REG=Copy_u8Data;
	/*wait for Transmission complete*/
	while(!GET_BIT(SPI_u8_STATE_REG,7));
}

u8 SPI_u8MasterReceive(void){
	/*Start Transmission*/
	SPI_u8_DATA_REG=0xCE;
	/*wait for Transmission complete*/
	while(!GET_BIT(SPI_u8_STATE_REG,7));
	/*Return Data*/
	return SPI_u8_DATA_REG;
}

u8 	 SPI_u8SlaveReceive(void){
	/*Wait for reception complete*/
	while(!GET_BIT(SPI_u8_STATE_REG,7));
	/*Return data register*/
	return SPI_u8_DATA_REG;
}

u8 SPI_u8CallBack(void(*Copy_PtrToFun)(void)){
	u8 Local_u8ErrorState=STD_TYPES_OK;
	if(Copy_PtrToFun!=NULL){
		SPI_PtrToFun=Copy_PtrToFun;
	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}
	return Local_u8ErrorState;
}

void __vector_12(void) __attribute__((signal));
void __vector_12(void){

}
