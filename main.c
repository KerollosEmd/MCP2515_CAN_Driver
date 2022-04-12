/*
 * main.c
 *
 *  Created on: Apr 7, 2022
 *      Author: KeroEmad
 */


#include "STD_Types.h"
#include "BIT_MATH.h"
#define F_CPU		1000000UL
#include <avr/delay.h>

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "GIE_interface.h"

#include "LCD_interface.h"

#include "MCP2515_interface.h"
#include "MCP2515_private.h"
#include "MCP2515_config.h"
#define  RED_LED		129
#define  GRE_LED		36
#define  YEL_LED_R 		2
#define  YEL_LED_L 		64



typedef union{
	struct{
		u8 RX0IF :1;
		u8 RX1IF :1;
		u8 TX0IF :1;
		u8 TX1IF :1;
		u8 TX2IF :1;
		u8 ERRIF :1;
		u8 WAKIF :1;
		u8 MERRF :1;
	}Bits;
	u8 Byte;
}MCP_CANINTF_untypedef;
MCP_CANINTF_untypedef APP_CANINTF_REG;

MCP_StDF_strtypedef APP_Forward_msg;
MCP_StDF_strtypedef APP_STOP_msg;

MCP_StDF_strtypedef APP_stdf_ReceivedMessage;

u8 APP_u8Incrementer=0;


void APP_voidREQtoSend0(void){
	DIO_u8SetPortValue(DIO_u8_PORTC,0x01<<4);		//debug
	MCP_u8TxB0Config_Standard(APP_STOP_msg,3);
	_delay_ms(50);
	MCP_macF_CS_PIN_LOW;
	MCP_macF_SendMessage(0x81);//Request to send TX1Buffer with forward MSG
	MCP_macF_CS_PIN_HIGH;
}

void APP_voidREQtoSend1(void){

	DIO_u8SetPortValue(DIO_u8_PORTC,0x01<<6);		//debug
	MCP_u8TxB0Config_Standard(APP_Forward_msg,3);
	_delay_ms(50);
	MCP_macF_CS_PIN_LOW;
	MCP_macF_SendMessage(MCP_INST_BIT_MODIFY);//Bit modify instruction
	MCP_macF_SendMessage(MCP_u8_TXB0CTRL_REG);//Rigester Address
	MCP_macF_SendMessage(0x01<<4);//Mask Byte
	MCP_macF_SendMessage(0x01<<4);//Set TXREQ Bit for TXB0
	MCP_macF_CS_PIN_HIGH;
	MCP_TXBnCTRL_untypedef Local_TXB0CTRL;
	LCD_voidWriteCommand(LCD_Clear);
	PRIVATE_MCP_voidReadByte(0x66,&Local_TXB0CTRL.Byte);
	LCD_voidWriteChar(Local_TXB0CTRL.Byte);
	PRIVATE_MCP_voidReadByte(0x76,&Local_TXB0CTRL.Byte);
		LCD_voidWriteChar(Local_TXB0CTRL.Byte);
//	while(1);

}

void APP_voidReadIntFlags(void){
	u8 Local_u8Indecator=0xFF;
	PRIVATE_MCP_voidReadByte(0x2C,&APP_CANINTF_REG.Byte);
	if(1==APP_CANINTF_REG.Bits.RX0IF){
		DIO_u8SetPortValue(DIO_u8_PORTC,0x01<<5);//debug section start
		MCP_stdfReadRXnBufferID(&APP_stdf_ReceivedMessage,0);
		MCP_stdfReadRXnBufferData(&APP_stdf_ReceivedMessage,2);
		PRIVATE_MCP_voidWriteByte(0x2C,0);
		LCD_voidWriteCommand(LCD_Clear);
		LCD_voidWriteString(APP_stdf_ReceivedMessage.DATA);
		LCD_voidGoToXY(0,LCD_u8_LINE_2);
		LCD_voidWritNumber(APP_stdf_ReceivedMessage.SID);
		LCD_voidWriteChar(' ');
		LCD_voidWritNumber(APP_stdf_ReceivedMessage.DLC);
		PRIVATE_MCP_voidReadByte(0x2C,&APP_CANINTF_REG.Byte);
		LCD_voidWriteChar(' ');
		LCD_voidWritNumber(APP_CANINTF_REG.Byte+1);
		MCP_macF_CS_PIN_LOW;
		MCP_macF_SendMessage(0xA0);
		Local_u8Indecator=MCP_macF_ReceiveMessage;
		Local_u8Indecator=MCP_macF_ReceiveMessage;
		MCP_macF_CS_PIN_HIGH;
		LCD_voidWritNumber(Local_u8Indecator+1);
		_delay_ms(500);
//		while(1);//Debug section end
	}else if(1==APP_CANINTF_REG.Bits.RX1IF){
		DIO_u8SetPortValue(DIO_u8_PORTC,0x01<<3);
		MCP_stdfReadRXnBufferID(&APP_stdf_ReceivedMessage,4);
		MCP_stdfReadRXnBufferData(&APP_stdf_ReceivedMessage,6);
		LCD_voidWriteString(APP_stdf_ReceivedMessage.DATA);

	}
	APP_u8Incrementer++;
//	PRIVATE_MCP_voidWriteByte(0x2C,0x00);//CLEAR FLAGS
}

int main(void){
	DIO_voidInit();
	SPI_voidMasterInit();
	LCD_voidInit();
	GIE_voidEnable();

	EXTI_u8INIT(EXTI_u8_EXTI_1,EXTI_u8_FALLING_EDGE);
	EXTI_u8INIT(EXTI_u8_EXTI_2,EXTI_u8_FALLING_EDGE);

	APP_stdf_ReceivedMessage.SID=0;
	APP_stdf_ReceivedMessage.DLC=0;
	APP_stdf_ReceivedMessage.RTR=0;
	APP_CANINTF_REG.Byte=0;

/*
	MCP_StDF_strtypedef APP_Forward_msg;
	MCP_StDF_strtypedef APP_STOP_msg;
	MCP_StDF_strtypedef Local_RIGHT_msg;
	MCP_StDF_strtypedef Local_LEFT_msg;
*/

	u8 Local_u8Index;
	u8 Local_u8Forwardstring[]="FORWARD";
	u8 Local_u8Stopstring[]=   "STOP   ";

	APP_Forward_msg.SID=0x0A;
	APP_Forward_msg.DLC=8;
	APP_Forward_msg.RTR=0;
	for(Local_u8Index=0;Local_u8Forwardstring[Local_u8Index]!='\0';Local_u8Index++)
		APP_Forward_msg.DATA[Local_u8Index]=Local_u8Forwardstring[Local_u8Index];

	APP_STOP_msg.SID=0x09;
	APP_STOP_msg.DLC=8;
	APP_STOP_msg.RTR=0;
	for(Local_u8Index=0;Local_u8Stopstring[Local_u8Index]!='\0';Local_u8Index++)
		APP_STOP_msg.DATA[Local_u8Index]=Local_u8Stopstring[Local_u8Index];


	MCP_voidInit();
	PRIVATE_MCP_voidWriteByte(0x2B,0x03);//Enable some Interrupt sources
	MCP_macF_INT_INIT;
	MCP_macF_INT_ENABLE;
	MCP_macF_INT_CALLBACK(APP_voidReadIntFlags);

	u8 Local_u8CNF1=0, Local_u8CNF2=0, Local_u8CNF3=0;
	MCP_CANSTAT_untypedef Local_u8CANSTAT;
	PRIVATE_MCP_voidReadByte(MCP_u8_CANSTAT,&Local_u8CANSTAT.Byte);
	LCD_voidWriteString("CANSTAT=");
	LCD_voidWritNumber(Local_u8CANSTAT.Byte);

	/*Configure RXnBuffures to Receive any MSG*/
	PRIVATE_MCP_voidWriteByte(0x60,0b01100100);//turn off filters/mask of RXB0
	PRIVATE_MCP_voidWriteByte(0x70,0b01100000);//turn off filters/mask of RXB1

	PRIVATE_MCP_voidReadByte(MCP_u8_CNF1_REG,&Local_u8CNF1);
	PRIVATE_MCP_voidReadByte(MCP_u8_CNF2_REG,&Local_u8CNF2);
	PRIVATE_MCP_voidReadByte(MCP_u8_CNF3_REG,&Local_u8CNF3);

	LCD_voidGoToXY(0,LCD_u8_LINE_2);
	LCD_voidWriteString("CNF=");
	LCD_voidWritNumber(Local_u8CNF1);
	LCD_voidWriteChar(' ');
	LCD_voidWritNumber(Local_u8CNF2);
	LCD_voidWriteChar(' ');
	LCD_voidWritNumber(Local_u8CNF3);

	/*REQ Loop back operation mode*/
	PRIVATE_MCP_voidWriteByte(MCP_u8_CANCTRL,0x40);
	PRIVATE_MCP_voidReadByte(MCP_u8_CANSTAT,&Local_u8CANSTAT.Byte);
	LCD_voidWriteCommand(LCD_Clear);
	LCD_voidWriteString("OPMOD=");
	LCD_voidWritNumber(Local_u8CANSTAT.Bits.OPMOD);

	/*Configure TX0/TX1 Buffers */



	/*Request to send TX0Buffer with Stop MSG*/
	EXTI_u8SetCallBack(EXTI_u8_EXTI_1,APP_voidREQtoSend0);

	/*Request to send TX0Buffer with Forward MSG*/
	EXTI_u8SetCallBack(EXTI_u8_EXTI_2,APP_voidREQtoSend1);

	while(1){
//		while(!(APP_CANINTF_REG.Bits.RX0IF||APP_CANINTF_REG.Bits.RX1IF));
		if('S'==APP_stdf_ReceivedMessage.DATA[0]){
			LCD_voidWriteCommand(LCD_Clear);
			LCD_voidWriteString(APP_stdf_ReceivedMessage.DATA);
			LCD_voidGoToXY(0,LCD_u8_LINE_2);
			LCD_voidWritNumber(APP_stdf_ReceivedMessage.SID);
			DIO_u8SetPortValue(DIO_u8_PORTC,RED_LED);
			_delay_ms(1500);
			DIO_u8SetPortValue(DIO_u8_PORTC,0);
			_delay_ms(1500);
			MCP_macF_CS_PIN_LOW;
			MCP_macF_SendMessage(0x81);//Request to send TX1Buffer with forward MSG
			MCP_macF_CS_PIN_HIGH;
		}
		else if ('F'==APP_stdf_ReceivedMessage.DATA[0]){
			LCD_voidWriteCommand(LCD_Clear);
			LCD_voidWriteString(APP_stdf_ReceivedMessage.DATA);
			LCD_voidGoToXY(0,LCD_u8_LINE_2);
			LCD_voidWritNumber(APP_stdf_ReceivedMessage.SID);
			DIO_u8SetPortValue(DIO_u8_PORTC,GRE_LED);
			_delay_ms(500);
			DIO_u8SetPortValue(DIO_u8_PORTC,0);
			_delay_ms(500);
			MCP_macF_CS_PIN_LOW;
			MCP_macF_SendMessage(0x81);//Request to send TX1Buffer with forward MSG
			MCP_macF_CS_PIN_HIGH;

		}

	}

	return 0;
}

