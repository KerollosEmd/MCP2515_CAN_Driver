/*
 * MCP2515_private.h
 *
 *  Created on: Apr 6, 2022
 *      Author: KeroEmad
 */

#ifndef MCP2515_PRIVATE_H_
#define MCP2515_PRIVATE_H_

/*Transmit Buffer 0 CTRL/ARBITRATION Registers*/
#define MCP_u8_TXB0CTRL_REG		0x30
#define MCP_u8_TXB0SIDH_REG		0x31
#define MCP_u8_TXB0SIDL_REG		0x32
#define MCP_u8_TXB0EID8_REG		0x33
#define MCP_u8_TXB0EID0_REG		0x34
#define MCP_u8_TXB0DLC_REG		0x35
/*Transmit Buffer 0 Data Registers*/
#define MCP_u8_TXB0D0_REG		0x36
#define MCP_u8_TXB0D1_REG		0x37
#define MCP_u8_TXB0D2_REG		0x38
#define MCP_u8_TXB0D3_REG		0x39
#define MCP_u8_TXB0D4_REG		0x3A
#define MCP_u8_TXB0D5_REG		0x3B
#define MCP_u8_TXB0D6_REG		0x3C
#define MCP_u8_TXB0D7_REG		0x3D

/*Transmit Buffer 1 CTRL/ARBITRATION Registers*/
#define MCP_u8_TXB1CTRL_REG		0x40
#define MCP_u8_TXB1SIDH_REG		0x41
#define MCP_u8_TXB1SIDL_REG		0x42
#define MCP_u8_TXB1EID8_REG		0x43
#define MCP_u8_TXB1EID0_REG		0x44
#define MCP_u8_TXB1DLC_REG		0x45
/*Transmit Buffer 1 Data Registers*/
#define MCP_u8_TXB1D0_REG		0x46
#define MCP_u8_TXB1D1_REG		0x47
#define MCP_u8_TXB1D2_REG		0x48
#define MCP_u8_TXB1D3_REG		0x49
#define MCP_u8_TXB1D4_REG		0x4A
#define MCP_u8_TXB1D5_REG		0x4B
#define MCP_u8_TXB1D6_REG		0x4C
#define MCP_u8_TXB1D7_REG		0x4D

/*Transmit Buffer 2 CTRL/ARBITRATION Registers*/
#define MCP_u8_TXB2CTRL_REG		0x50
#define MCP_u8_TXB2SIDH_REG		0x51
#define MCP_u8_TXB2SIDL_REG		0x52
#define MCP_u8_TXB2EID8_REG		0x53
#define MCP_u8_TXB2EID0_REG		0x54
#define MCP_u8_TXB2DLC_REG		0x55
/*Transmit Buffer 2 Data Registers*/
#define MCP_u8_TXB2D0_REG		0x56
#define MCP_u8_TXB2D1_REG		0x57
#define MCP_u8_TXB2D2_REG		0x58
#define MCP_u8_TXB2D3_REG		0x59
#define MCP_u8_TXB2D4_REG		0x5A
#define MCP_u8_TXB2D5_REG		0x5B
#define MCP_u8_TXB2D6_REG		0x5C
#define MCP_u8_TXB2D7_REG		0x5D

/*CONFIGURATION REGISTERS ADDRESSES*/
#define MCP_u8_CNF1_REG			0x2A
#define MCP_u8_CNF2_REG			0x29
#define MCP_u8_CNF3_REG			0x28

/*CAN Registers Addresses*/
#define MCP_u8_CANSTAT			0x0E
#define MCP_u8_CANCTRL			0x0F
/*SPI INSTRUCTION SET*/
#define MCP_INST_WRITE			0x02
#define MCP_INST_READ			0x03
#define MCP_INST_BIT_MODIFY		0x05
#define MCP_INST_READ_STATUS	0xA0
#define MCP_INST_RX_STATUS		0xB0
#define MCP_INST_RESET			0xC0

#define MCP_INST_RTS			0x80
#define MCP_INST_READ_RXB		0x90
#define MCP_INST_LOAD_TXB		0x40
/****************************************************/
/******************typedef section*******************/

typedef struct MCP_StRemote_Frame{
	u16 ID			:11;
	u8	DLC			:4;
}MCP_StRemF_strtypedef;


typedef struct MCP_ExRemote_Frame{
	u32 EID			:29;
	u8	DLC			:4;
}MCP_ExRemF_strtypedef;

/*TX Buffer n Registers' Bits Definition*/
typedef union MCP_untypedef_TXBnCTRL{
	struct TXBnCTRL{
		u8 TX_Priority 		:2;
		u8 UNIMPLEMENTED_2	:1;
		u8 TX_REQ			:1;
		u8 TX_ERR			:1;
		u8 TX_LostArbit		:1;
		u8 TX_AbortFlag		:1;
		u8 UNIMPLEMENTED_7	:1;
	}Bits;
	u8 Byte;
}MCP_TXBnCTRL_untypedef;

/*TX Buffer n Standard Identifier Low Register Bits Definition*/
typedef union MCP_untypedef_TXBnSIDL{
	struct TXBnSIDL{
		u8 EX_ID_17_16		:2;
		u8 UNIMPLEMENTED_2	:1;
		u8 EX_ID_ENABLE		:1;
		u8 UNIMPLEMENTED_4	:1;
		u8 ST_ID_2_0		:3;
	}Bits;
	u8 Byte;
}MCP_TXBnSIDL_untypedef;

/*TX Buffer n Data Length Code Register Bits Definition*/
typedef union MCP_untypedef_TXBnDLC{
	struct TXBnDLC{
		u8 DLC_3_0			:4;
		u8 UNIMPLEMENTED4_5	:2;
		u8 RTR				:1;
		u8 UNIMPLEMENTED_7	:1;
	}Bits;
	u8 Byte;
}MCP_TXBnDLC_untypedef;

/*TX Buffer n Data byte m*/
typedef struct MCP_untypedef_DATA{
	u8 DATA ;
	u8 BUFFER_NUM_n		:2;
	u8 DATA_NUM_m		:3;
}MCP_TXDATA_untypedef;

/*CAN timing Configuration Registers*/
/*Configuration Register 1*/
typedef union MCP_u8typdef_CNF1{
	struct CNF1{
		u8 BRP5_0			:6; //Baud Rate Prescaler bits
		u8 SJW1_0			:2; //Synchronization Jump Width Length bits
	}Bits;
	u8 Byte;
}MCP_CNF1_untypedef;

/*Configuration Register 2*/
typedef union MCP_u8typdef_CNF2{
	struct CNF2{
		u8 PRSEG2_0			:3; //Propagation Segment Length bits
		u8 PHSEG1_2_0		:3; //PS1 Length bits
		u8 SAM				:1; //Sample Point Configuration bit
		u8 BTLMODE			:1; //PS2 Bit Time Length bit
	}Bits;
	u8 Byte;
}MCP_CNF2_untypedef;

/*Configuration Register 3*/
typedef union MCP_u8typdef_CNF3{
	struct CNF3{
		u8 PHSEG2_2_0		:3; //PS2 Length bits
		u8 UNIMP_5_3		:3; //Unimplemented bits
		u8 WAKFIL			:1; //Wake-up Filter bit
		u8 SOF				:1; //Start-of-Frame signal bit
	}Bits;
	u8 Byte;
}MCP_CNF3_untypedef;



/*CAN CONTROL REGISTER*/
typedef union MCP_u8typdef_CANCTRL{
	struct CANCTRL{
		u8 CLKPRE			:2;
		u8 CLKEN			:1;
		u8 OSM				:1;
		u8 ABAT				:1;
		u8 REQOP			:3;
	}Bits;
	u8 Byte;
}MCP_CANCTRL_untypedef;
/*CAN STATUS REGISTER*/
typedef union MCP_u8typdef_CANSTAT{
	struct CANSTAT{
		u8 UNIMP0			:1;
		u8 ICODE			:3;
		u8 UNIMP4			:1;
		u8 OPMOD			:3;
	}Bits;
	u8 Byte;
}MCP_CANSTAT_untypedef;


/****************************************************/
/**************Private Function**********************/
void PRIVATE_MCP_voidWriteByte(u8 Copy_u8Address, u8 Copy_u8Data);
void PRIVATE_MCP_voidReadByte(u8 Copy_u8Address, u8 *Copy_ptru8Data);

#endif /* MCP2515_PRIVATE_H_ */

/*
 * *****************BIT TIME****************
 * Useful Equations for Bit Timing
 * EQTN1: NBR= F_bit =1/T_bit
 * EQTN2: T_bit = T_SyncSeg + T_PropSeg + T_PS1 + T_PS2
 * NOTE1: T_PS2= IPT= 2TQ
 * EQTN3: TQ= 2.BRP.T_OSC= 2.BRP/F_OSC
 *
 */
