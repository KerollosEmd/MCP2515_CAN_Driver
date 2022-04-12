/*
 * SPI_interface.h
 *
 *  Created on: Apr 6, 2022
 *      Author: KeroEmad
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidMasterInit(void);
void SPI_voidSlaveInit(void);

void SPI_voidMasterTransmission(u8 Copy_u8Data);
u8   SPI_u8MasterReceive(void);
u8 	 SPI_u8SlaveReceive(void);

u8 	 SPI_u8CallBack(void(*Copy_PtrToFun)(void));

#endif /* SPI_INTERFACE_H_ */
