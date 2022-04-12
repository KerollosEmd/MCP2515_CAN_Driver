/*
 * MCP2515_prog.c
 *
 *  Created on: Apr 6, 2022
 *      Author: KeroEmad
 */

#include "STD_Types.h"
#include "BIT_MATH.h"

#include "MCP2515_interface.h"
#include "MCP2515_private.h"
#include "MCP2515_config.h"

#include "LCD_interface.h" //debug

/*
 * Initialization of MCP2515
 * Configure Baud Rate to reach 500 Kbit/sec
 * SJW = 2.TQ , BRP =0,
 * CNF1=0x40, CNF2=0xC9, CNF3=0x42
 */
void MCP_voidInit(void) {
	/*Send Reset instruction to resets internal registers to default state,
	 * set Configuration mode*/
	MCP_macF_CS_PIN_LOW; //Pulling down CS pin to Start Communication
	MCP_macF_SendMessage(MCP_INST_RESET); //Send Reset instruction
	MCP_macF_CS_PIN_HIGH; //Pulling Up CS pin to End Communication

	/*Define • CNF1, CNF2, CNF3*/
	MCP_CNF1_untypedef Local_CNF1_untypedef;
	MCP_CNF2_untypedef Local_CNF2_untypedef;
	MCP_CNF3_untypedef Local_CNF3_untypedef;

	Local_CNF1_untypedef.Byte = 0;
	Local_CNF2_untypedef.Byte = 0;
	Local_CNF3_untypedef.Byte = 0;
	/*Configure CNF1 REG*/
	Local_CNF1_untypedef.Bits.SJW1_0 = 1; //SJW=2.TQ
	//as BRP=0, therefore TQ=1/4MHz=250nS
	//CNF1=64

	/*Configure CNF2 REG*/
	Local_CNF2_untypedef.Bits.PRSEG2_0 = 1;	//PRSEG=2.TQ
	Local_CNF2_untypedef.Bits.SAM = 1; //Bus line is sampled 3 times at the sample point
	Local_CNF2_untypedef.Bits.BTLMODE = 1; //Length of PS2 determined by PHSEG2 bits of CNF3 REG
	Local_CNF2_untypedef.Bits.PHSEG1_2_0 = 1; //PS1 = 2.TQ
	//CNF2=201

	/*Configure CNF3 REG*/
	Local_CNF3_untypedef.Bits.PHSEG2_2_0 = 2;	//PS2 = 3.TQ
	Local_CNF3_untypedef.Bits.WAKFIL = 1;	//Wake-up filter is enabled
	//CNF3=66
	/*Check Mode of operation (configuration OPMODE)*/
	MCP_CANSTAT_untypedef Local_CANSTAT_untypedef;
	PRIVATE_MCP_voidReadByte(MCP_u8_CANSTAT, &Local_CANSTAT_untypedef.Byte);
	if (Local_CANSTAT_untypedef.Bits.OPMOD == MCP_MODE_CONFIG) {
		// write CNF1 REG
		PRIVATE_MCP_voidWriteByte(MCP_u8_CNF1_REG, Local_CNF1_untypedef.Byte);
		PRIVATE_MCP_voidWriteByte(MCP_u8_CNF2_REG, Local_CNF2_untypedef.Byte);
		PRIVATE_MCP_voidWriteByte(MCP_u8_CNF3_REG, Local_CNF3_untypedef.Byte);
	}
}

/*Modes of Operation*/

/*
 * The MCP2515 must be initialized before activation.
 * This is only possible if the device is in the Configuration
 * mode. Configuration mode is automatically selected
 * after power-up, a reset or can be entered from any
 * other mode by setting the CANTRL.REQOP bits to
 * ‘100’. When Configuration mode is entered, all error
 * counters are cleared. Configuration mode is the only
 * mode where the following registers are modifiable:
 *  • CNF1, CNF2, CNF3
 *  • TXRTSCTRL
 *  • Filter registers
 *  • Mask registers
 */

/*
 MCP_CANSTAT_untypedef MCP_u8ConfigModeReq(void);
 MCP_CANSTAT_untypedef MCP_u8SleepModeReq(void);
 MCP_CANSTAT_untypedef MCP_u8ListenOnlyModeReq(void);
 MCP_CANSTAT_untypedef MCP_u8LoopbackModeReq(void);
 MCP_CANSTAT_untypedef MCP_u8NormalModeReq(void);
 */

/*
 * Transmission APIs to handle CAN Protocol in MCP2515
 */

/*Tx Buffer 0 Configuration*/
MCP_ERR_entypedef MCP_u8TxB0Config_Standard(
		MCP_StDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority) {
	MCP_ERR_entypedef Local_enumErrorState = No_ERR;

	MCP_TXBnCTRL_untypedef Local_unTXB0CTRL;
	MCP_TXBnSIDL_untypedef Local_unTXB0SIDL;
	MCP_TXBnDLC_untypedef Local_unTXB0DLC;

	Local_unTXB0CTRL.Byte = 0;
	Local_unTXB0DLC.Byte = 0;
	Local_unTXB0SIDL.Byte = 0;

	Local_unTXB0SIDL.Bits.ST_ID_2_0 = Copy_strtypedef_Message.SID;

	Local_unTXB0DLC.Bits.DLC_3_0 = Copy_strtypedef_Message.DLC;
	Local_unTXB0DLC.Bits.RTR = Copy_strtypedef_Message.RTR;

	/*Check there no pending transmission in TXB0 before writing to it*/
	do {
		PRIVATE_MCP_voidReadByte(MCP_u8_TXB0CTRL_REG, &Local_unTXB0CTRL.Byte);
	} while (Local_unTXB0CTRL.Bits.TX_REQ);

	Local_unTXB0CTRL.Bits.TX_Priority = Copy_u8BufferPriority;
	/*Configure Transmit Buffer Priority*/
	PRIVATE_MCP_voidWriteByte(MCP_u8_TXB0CTRL_REG, Local_unTXB0CTRL.Byte);

	MCP_macF_CS_PIN_LOW;	// Start Communication
	/*Send Load Tx Buffer Instruction*/
	MCP_macF_SendMessage(MCP_INST_LOAD_TXB|0); // 0 for make address point to TXB0SIDH
	/*Load TXB0SIDH register*/
	MCP_macF_SendMessage((Copy_strtypedef_Message.SID >> 3));
	/*Load TXB0SIDL register*/
	MCP_macF_SendMessage(Local_unTXB0SIDL.Byte);
	/*Load Extended ID High/Low Registers with 0s*/
	MCP_macF_SendMessage(0); //TXB0EID8 REG
	MCP_macF_SendMessage(0); //TXB0EID0 REG
	/*Load TXB0DLC register*/
	MCP_macF_SendMessage(Local_unTXB0DLC.Byte);
	MCP_macF_CS_PIN_HIGH; // End Communication

	/*Load TXB0Dm*/
	MCP_u8TxBnWrite_DATA(Copy_strtypedef_Message, TXB0D0);

	/*Debug Section*/
	u8 Local_u8Debug = 0;
	MCP_StDF_strtypedef Local_stdf_DATA;
	LCD_voidGoToXY(0, LCD_u8_LINE_2);
	PRIVATE_MCP_voidReadByte(MCP_u8_TXB0CTRL_REG, &Local_u8Debug);
	LCD_voidWritNumber(Local_u8Debug); //debug
	PRIVATE_MCP_voidReadByte(MCP_u8_TXB0SIDH_REG, &Local_u8Debug);
	LCD_voidWriteChar(' ');
	LCD_voidWritNumber(Local_u8Debug); //debug
	PRIVATE_MCP_voidReadByte(MCP_u8_TXB0SIDL_REG, &Local_u8Debug);
	LCD_voidWriteChar(' ');
	LCD_voidWritNumber(Local_u8Debug); //debug
	PRIVATE_MCP_voidReadByte(MCP_u8_TXB0DLC_REG, &Local_u8Debug);
	LCD_voidWriteChar(' ');
	LCD_voidWritNumber(Local_u8Debug); //debug
	MCP_stDF_TxBnRead_DATA(&Local_stdf_DATA,MCP_u8_TXB0D0_REG);
	LCD_voidWriteChar(' ');
	LCD_voidWriteString(Local_stdf_DATA.DATA);

//	while (1); //debug
	/*End Debug Section*/
	return Local_enumErrorState;
}

/*Tx Buffer 1*/
MCP_ERR_entypedef MCP_u8TxB1Config_Standard(
		MCP_StDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority) {
	MCP_ERR_entypedef Local_enumErrorState = No_ERR;

	MCP_TXBnCTRL_untypedef Local_unTXB1CTRL;
	MCP_TXBnSIDL_untypedef Local_unTXB1SIDL;
	MCP_TXBnDLC_untypedef Local_unTXB1DLC;

	Local_unTXB1CTRL.Bits.TX_Priority = Copy_u8BufferPriority;

	Local_unTXB1SIDL.Bits.ST_ID_2_0 = Copy_strtypedef_Message.SID << 8;
	Local_unTXB1SIDL.Bits.EX_ID_ENABLE = 0;

	Local_unTXB1DLC.Bits.DLC_3_0 = Copy_strtypedef_Message.DLC;
	Local_unTXB1DLC.Bits.RTR = Copy_strtypedef_Message.RTR;

	/*Check there no pending transmission in TXB1 before writing to it*/
	/*while(!(Local_unTXB1CTRL.Bits.TX_REQ)){
	 PRIVATE_MCP_voidReadByte(MCP_u8_TXB1CTRL_REG,&Local_unTXB1CTRL.Byte);
	 }*/

	/*Configure Transmit Buffer Priority*/
	PRIVATE_MCP_voidWriteByte(MCP_u8_TXB1CTRL_REG,
			Local_unTXB1CTRL.Bits.TX_Priority);

	MCP_macF_CS_PIN_LOW; // Start Communication
	/*Send Load Tx Buffer Instruction*/
	MCP_macF_SendMessage(MCP_INST_LOAD_TXB|0); // 0 for make address point to TXB0SIDH
	/*Load TXB1SIDH register*/
	MCP_macF_SendMessage((Copy_strtypedef_Message.SID >> 3));
	/*Load TXB1SIDL register*/
	MCP_macF_SendMessage(Local_unTXB1SIDL.Byte);
	/*Load Extended ID High/Low Registers with 0s*/
	MCP_macF_SendMessage(0); //TXB1EID8 REG
	MCP_macF_SendMessage(0); //TXB1EID0 REG
	/*Load TXB0DLC register*/
	MCP_macF_SendMessage(Local_unTXB1DLC.Byte);
	MCP_macF_CS_PIN_HIGH; // End Communication

	/*Load TXB0Dm*/

	MCP_u8TxBnWrite_DATA(Copy_strtypedef_Message, TXB1D0);

	u8 Local_u8Data = 0;										//debug
	PRIVATE_MCP_voidReadByte(MCP_u8_TXB1D0_REG, &Local_u8Data);			//debug
	LCD_voidWriteChar(Local_u8Data);						//debug
	PRIVATE_MCP_voidReadByte(MCP_u8_TXB1D1_REG, &Local_u8Data);			//debug
	LCD_voidWriteChar(Local_u8Data);						//debug
	DIO_u8SetPortValue(DIO_u8_PORTC, 0x01 << 7);				//debug

	return Local_enumErrorState;
}

/*Tx Buffer 2*/
MCP_ERR_entypedef MCP_u8TxB2Config_Standard(
		MCP_StDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority) {
	MCP_ERR_entypedef Local_enumErrorState = No_ERR;

	MCP_TXBnCTRL_untypedef Local_unTXB2CTRL;
	MCP_TXBnSIDL_untypedef Local_unTXB2SIDL;
	MCP_TXBnDLC_untypedef Local_unTXB2DLC;

	Local_unTXB2CTRL.Bits.TX_Priority = Copy_u8BufferPriority;

	Local_unTXB2SIDL.Bits.ST_ID_2_0 = Copy_strtypedef_Message.SID << 8;
	Local_unTXB2SIDL.Bits.EX_ID_ENABLE = 0;

	Local_unTXB2DLC.Bits.DLC_3_0 = Copy_strtypedef_Message.DLC;
	Local_unTXB2DLC.Bits.RTR = Copy_strtypedef_Message.RTR;

	/*Check there no pending transmission in TXB2 before writing to it*/
	while (!Local_unTXB2CTRL.Bits.TX_REQ) {
		PRIVATE_MCP_voidReadByte(MCP_u8_TXB2CTRL_REG, &Local_unTXB2CTRL.Byte);
	}

	/*Configure Transmit Buffer Priority*/
	PRIVATE_MCP_voidWriteByte(MCP_u8_TXB1CTRL_REG,
			Local_unTXB2CTRL.Bits.TX_Priority);

	MCP_macF_CS_PIN_LOW;				// Start Communication
	/*Send Load Tx Buffer Instruction*/
	MCP_macF_SendMessage(MCP_INST_LOAD_TXB|0); // 0 for make address point to TXB0SIDH
	/*Load TXB1SIDH register*/
	MCP_macF_SendMessage((Copy_strtypedef_Message.SID >> 3));
	/*Load TXB1SIDL register*/
	MCP_macF_SendMessage(Local_unTXB2SIDL.Byte);
	/*Load Extended ID High/Low Registers with 0s*/
	MCP_macF_SendMessage(0); //TXB1EID8 REG
	MCP_macF_SendMessage(0); //TXB1EID0 REG
	/*Load TXB0DLC register*/
	MCP_macF_SendMessage(Local_unTXB2DLC.Byte);
	MCP_macF_CS_PIN_HIGH; // End Communication

	/*Load TXB0Dm*/
	MCP_u8TxBnWrite_DATA(Copy_strtypedef_Message, TXB2D0);

	return Local_enumErrorState;

}
/*Tx Buffer 0*/
MCP_ERR_entypedef MCP_u8TxB0Config_Extended(
		MCP_ExDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority) {
	MCP_ERR_entypedef Local_enumErrorState = No_ERR;

	MCP_TXBnCTRL_untypedef Local_unTXB0CTRL;
	MCP_TXBnSIDL_untypedef Local_unTXB0SIDL;
	MCP_TXBnDLC_untypedef Local_unTXB0DLC;

	Local_unTXB0CTRL.Bits.TX_Priority = Copy_u8BufferPriority;

	Local_unTXB0SIDL.Bits.ST_ID_2_0 = Copy_strtypedef_Message.SID << 8;
	Local_unTXB0SIDL.Bits.EX_ID_ENABLE = 1;
	Local_unTXB0SIDL.Bits.EX_ID_17_16 = Copy_strtypedef_Message.EID >> 16;

	Local_unTXB0DLC.Bits.DLC_3_0 = Copy_strtypedef_Message.DLC;
	Local_unTXB0DLC.Bits.RTR = Copy_strtypedef_Message.RTR;

	/*Check there no pending transmission in TXB0 before writing to it*/
	while (!Local_unTXB0CTRL.Bits.TX_REQ) {
		PRIVATE_MCP_voidReadByte(MCP_u8_TXB0CTRL_REG, &Local_unTXB0CTRL.Byte);
	}

	/*Configure Transmit Buffer Priority*/
	PRIVATE_MCP_voidWriteByte(MCP_u8_TXB1CTRL_REG,
			Local_unTXB0CTRL.Bits.TX_Priority);

	MCP_macF_CS_PIN_LOW; // Start Communication
	/*Send Load Tx Buffer Instruction*/
	MCP_macF_SendMessage(MCP_INST_LOAD_TXB|0); // 0 for make address point to TXB0SIDH
	/*Load TXB1SIDH register*/
	MCP_macF_SendMessage((Copy_strtypedef_Message.SID >> 3));
	/*Load TXB1SIDL register*/
	MCP_macF_SendMessage(Local_unTXB0SIDL.Byte);
	/*Load Extended ID High/Low Registers with 0s*/
	MCP_macF_SendMessage((u8 )(Copy_strtypedef_Message.EID >> 8)); //TXB1EID8 REG
	MCP_macF_SendMessage((u8 )Copy_strtypedef_Message.EID); //TXB1EID0 REG
	/*Load TXB0DLC register*/
	MCP_macF_SendMessage(Local_unTXB0DLC.Byte);
	MCP_macF_CS_PIN_HIGH; // End Communication

	/*Load TXB0Dm*/
	MCP_u8TxBnWrite_DATA_ExD(Copy_strtypedef_Message, TXB0D0);

	return Local_enumErrorState;

}

/*Tx Buffer 1*/
MCP_ERR_entypedef MCP_u8TxB1Config_Extended(
		MCP_ExDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority) {
	MCP_ERR_entypedef Local_enumErrorState = No_ERR;

	MCP_TXBnCTRL_untypedef Local_unTXB1CTRL;
	MCP_TXBnSIDL_untypedef Local_unTXB1SIDL;
	MCP_TXBnDLC_untypedef Local_unTXB1DLC;

	Local_unTXB1CTRL.Bits.TX_Priority = Copy_u8BufferPriority;

	Local_unTXB1SIDL.Bits.ST_ID_2_0 = Copy_strtypedef_Message.SID << 8;
	Local_unTXB1SIDL.Bits.EX_ID_ENABLE = 1;
	Local_unTXB1SIDL.Bits.EX_ID_17_16 = Copy_strtypedef_Message.EID >> 16;

	Local_unTXB1DLC.Bits.DLC_3_0 = Copy_strtypedef_Message.DLC;
	Local_unTXB1DLC.Bits.RTR = Copy_strtypedef_Message.RTR;

	/*Check there no pending transmission in TXB1 before writing to it*/
	while (!Local_unTXB1CTRL.Bits.TX_REQ) {
		PRIVATE_MCP_voidReadByte(MCP_u8_TXB1CTRL_REG, &Local_unTXB1CTRL.Byte);
	}

	/*Configure Transmit Buffer Priority*/
	PRIVATE_MCP_voidWriteByte(MCP_u8_TXB1CTRL_REG,
			Local_unTXB1CTRL.Bits.TX_Priority);

	MCP_macF_CS_PIN_LOW; // Start Communication
	/*Send Load Tx Buffer Instruction*/
	MCP_macF_SendMessage(MCP_INST_LOAD_TXB|0); // 0 for make address point to TXB1SIDH
	/*Load TXB1SIDH register*/
	MCP_macF_SendMessage((Copy_strtypedef_Message.SID >> 3));
	/*Load TXB1SIDL register*/
	MCP_macF_SendMessage(Local_unTXB1SIDL.Byte);
	/*Load Extended ID High/Low Registers with 0s*/
	MCP_macF_SendMessage((u8 )(Copy_strtypedef_Message.EID >> 8)); //TXB1EID8 REG
	MCP_macF_SendMessage((u8 )Copy_strtypedef_Message.EID); //TXB1EID0 REG
	/*Load TXB1DLC register*/
	MCP_macF_SendMessage(Local_unTXB1DLC.Byte);
	MCP_macF_CS_PIN_HIGH; // End Communication

	/*Load TXB1Dm*/
	MCP_u8TxBnWrite_DATA_ExD(Copy_strtypedef_Message, TXB1D0);

	return Local_enumErrorState;

}
/*Tx Buffer 2*/
MCP_ERR_entypedef MCP_u8TxB2Config_Extended(
		MCP_ExDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority);

MCP_ERR_entypedef MCP_u8TxBnWrite_DATA(
		MCP_StDF_strtypedef Copy_strtypedef_Message,
		MCP_TXBnumData_entypedef Copy_u8BufferNum) {
	MCP_ERR_entypedef Local_enErrorState = No_ERR;
	u8 Local_u8Index;

	MCP_macF_CS_PIN_LOW; //Start Communication
	/*Load TXB1Dm*/
	MCP_macF_SendMessage((MCP_INST_LOAD_TXB|Copy_u8BufferNum));
	for (Local_u8Index = 0; Local_u8Index < 8; Local_u8Index++)
		MCP_macF_SendMessage(Copy_strtypedef_Message.DATA[Local_u8Index]);
	MCP_macF_CS_PIN_HIGH; //End Communication

	return Local_enErrorState;
}

MCP_ERR_entypedef MCP_u8TxBnWrite_DATA_ExD(
		MCP_ExDF_strtypedef Copy_strtypedef_Message,
		MCP_TXBnumData_entypedef Copy_u8BufferNum) {
	MCP_ERR_entypedef Local_enErrorState = No_ERR;
	u8 Local_u8Index;

	MCP_macF_CS_PIN_LOW; //Start Communication
	/*Load TXB1Dm*/
	MCP_macF_SendMessage((MCP_INST_LOAD_TXB|Copy_u8BufferNum));
	for (Local_u8Index = 0; Local_u8Index < 8; Local_u8Index++)
		MCP_macF_SendMessage(Copy_strtypedef_Message.DATA[Local_u8Index]);
	MCP_macF_CS_PIN_HIGH; //End Communication

	return Local_enErrorState;
}

void MCP_stDF_TxBnRead_DATA(MCP_StDF_strtypedef *Copy_pstdfMessage,u8 Copy_u8TXBnD0_REG_ADD) {

	u8 Local_u8Index;
	for (Local_u8Index = 0; Local_u8Index < 8; Local_u8Index++)
		PRIVATE_MCP_voidReadByte(Copy_u8TXBnD0_REG_ADD + Local_u8Index,
				&Copy_pstdfMessage->DATA[Local_u8Index]);

}

void MCP_stdfReadRXnBufferID(MCP_StDF_strtypedef *Copy_pstdfMessage,u8 Copy_u8RXBufferNum) {

	MCP_macF_CS_PIN_LOW;					//{Copy_u8RXBufferNum= 0 or 4 only}
	MCP_macF_SendMessage(MCP_INST_READ_RXB|Copy_u8RXBufferNum);	// Read from RXBnSIDH register only

	Copy_pstdfMessage->SID |= ((u16)MCP_macF_ReceiveMessage)<<3;//for RXBnSIDH
	Copy_pstdfMessage->SID |= MCP_macF_ReceiveMessage>>5;//For RXBnSIDL
	MCP_macF_ReceiveMessage; //for RXBnEID8
	MCP_macF_ReceiveMessage; //for RXBnEID0
	Copy_pstdfMessage->DLC=MCP_macF_ReceiveMessage; //For RXBnDLC

	MCP_macF_CS_PIN_HIGH;

}


void MCP_stdfReadRXnBufferData(MCP_StDF_strtypedef *Copy_pstdfMessage,u8 Copy_u8RXBufferNum) {

	u8 Local_u8Index;

	MCP_macF_CS_PIN_LOW;					//{Copy_u8RXBufferNum= 2 or 6 only}
	MCP_macF_SendMessage(MCP_INST_READ_RXB|Copy_u8RXBufferNum);	// Read from Data register only
	for (Local_u8Index = 0; Local_u8Index < 8; Local_u8Index++)
		Copy_pstdfMessage->DATA[Local_u8Index] = MCP_macF_ReceiveMessage;
	MCP_macF_CS_PIN_HIGH;


}

/**************Private Function**********************/
void PRIVATE_MCP_voidWriteByte(u8 Copy_u8Address, u8 Copy_u8Data) {
	MCP_macF_CS_PIN_LOW;
	MCP_macF_SendMessage(MCP_INST_WRITE);
	MCP_macF_SendMessage(Copy_u8Address);
	MCP_macF_SendMessage(Copy_u8Data);
	MCP_macF_CS_PIN_HIGH;
}
void PRIVATE_MCP_voidReadByte(u8 Copy_u8Address, u8 *Copy_ptru8Data) {
	MCP_macF_CS_PIN_LOW;
	MCP_macF_SendMessage(MCP_INST_READ);
	MCP_macF_SendMessage(Copy_u8Address);
	*Copy_ptru8Data = MCP_macF_ReceiveMessage;
	MCP_macF_CS_PIN_HIGH;
}
