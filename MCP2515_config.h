/*
 * MCP2515_config.h
 *
 *  Created on: Apr 6, 2022
 *      Author: KeroEmad
 */

#ifndef MCP2515_CONFIG_H_
#define MCP2515_CONFIG_H_

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "EXTI_interface.h"

#define MCP_CS_PIN			DIO_u8_PIN4
#define	MCP_CS_PORT			DIO_u8_PORTB
#define MCP_INT_PIN			EXTI_u8_EXTI_0
#define MCP_INT_TRIG		EXTI_u8_FALLING_EDGE

#define MCP_macF_INT_INIT						EXTI_u8INIT(MCP_INT_PIN,MCP_INT_TRIG)
#define MCP_macF_INT_ENABLE						EXTI_u8Enable(MCP_INT_PIN)
#define MCP_macF_INT_DESABLE					EXTI_u8Disable(MCP_INT_PIN)
#define MCP_macF_INT_CALLBACK(Copy_PtrToFun)	EXTI_u8SetCallBack(MCP_INT_PIN,Copy_PtrToFun)

#define MCP_macF_CS_PIN_HIGH					DIO_u8SetPinValue(MCP_CS_PORT,MCP_CS_PIN,DIO_u8_HIGH)
#define MCP_macF_CS_PIN_LOW						DIO_u8SetPinValue(MCP_CS_PORT,MCP_CS_PIN,DIO_u8_LOW)

#define MCP_macF_SendMessage(Copy_u8Message) 	SPI_voidMasterTransmission(Copy_u8Message)
#define MCP_macF_ReceiveMessage					SPI_u8MasterReceive()



#endif /* MCP2515_CONFIG_H_ */
