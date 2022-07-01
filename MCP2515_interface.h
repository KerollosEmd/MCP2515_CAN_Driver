/*
 * MCP2515_interface.h
 *
 *  Created on: Apr 6, 2022
 *      Author: KeroEmad
 */

#ifndef MCP2515_INTERFACE_H_
#define MCP2515_INTERFACE_H_

/*Operation Modes*/
#define MCP_MODE_NORMAL			0x00
#define MCP_MODE_SLEEP			0x01
#define MCP_MODE_LOOPBACK		0x02
#define MCP_MODE_LISTENONLY		0x03
#define MCP_MODE_CONFIG			0x04

/*Interrupt Flag Code*/
#define MCP_IFCOD_NO_INT		0x00
#define MCP_IFCOD_ERR_INT		0x01
#define MCP_IFCOD_WAKE_UP		0x02
#define MCP_IFCOD_TXB0_INT		0x03
#define MCP_IFCOD_TXB1_INT		0x04
#define MCP_IFCOD_TXB2_INT		0x05
#define MCP_IFCOD_RXB0_INT		0x06
#define MCP_IFCOD_RXB1_INT		0x07

typedef enum MCP_ERROR_entypedef {
	No_ERR,
	ERR_INT
} MCP_ERR_entypedef;

typedef enum MCP_TXBnumData{
	TXB0D0 =1,
	TXB1D0 =3,
	TXB2D0 =5
}MCP_TXBnumData_entypedef;

/*
 * Frame data type structure
 */
typedef struct MCP_Standard_Data_Frame {
	u16 SID :11;
	u16 RTR :1;
	u16 DLC :4;
	u8 DATA[8];
} MCP_StDF_strtypedef;
typedef struct MCP_Extended_Data_Frame {
	u16 SID :11;
	u32 EID :18;
	u8 RTR :1;
	u8 DLC :4;
	u8 DATA[8];
} MCP_ExDF_strtypedef;

/*
 * Initialization of MCP2515
 * Configure Baud Rate to reach 500 Kbit/sec
 * SJW = 2 TQ , BRP =0,
 */
void MCP_voidInit(void);

/*Modes of Operation*/

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
/*Tx Buffer 0*/
MCP_ERR_entypedef MCP_u8TxB0Config_Standard(
		MCP_StDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority);


/*Tx Buffer 1*/
MCP_ERR_entypedef MCP_u8TxB1Config_Standard(
		MCP_StDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority);

/*Tx Buffer 2*/
MCP_ERR_entypedef MCP_u8TxB2Config_Standard(
		MCP_StDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority);

/*Tx Buffer 0*/
MCP_ERR_entypedef MCP_u8TxB0Config_Extended(
		MCP_ExDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority);

/*Tx Buffer 1*/
MCP_ERR_entypedef MCP_u8TxB1Config_Extended(
		MCP_ExDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority);

/*Tx Buffer 2*/
MCP_ERR_entypedef MCP_u8TxB2Config_Extended(
		MCP_ExDF_strtypedef Copy_strtypedef_Message, u8 Copy_u8BufferPriority);

MCP_ERR_entypedef MCP_u8TxBnWrite_DATA(
		MCP_StDF_strtypedef Copy_strtypedef_Message, MCP_TXBnumData_entypedef Copy_u8BufferNum);

MCP_ERR_entypedef MCP_u8TxBnWrite_DATA_ExD(
		MCP_ExDF_strtypedef Copy_strtypedef_Message, MCP_TXBnumData_entypedef Copy_u8BufferNum);

void MCP_stdfReadRXnBufferID(MCP_StDF_strtypedef *Copy_pstdfMessage,u8 Copy_u8RXBufferNum);

void MCP_stdfReadRXnBufferData(MCP_StDF_strtypedef *Copy_pstdfMessage,u8 Copy_u8RXBufferNum);

void MCP_stDF_TxBnRead_DATA(MCP_StDF_strtypedef *Copy_pstdfMessage,u8 Copy_u8TXBnD0_REG_ADD);
#endif /* MCP2515_INTERFACE_H_ */
