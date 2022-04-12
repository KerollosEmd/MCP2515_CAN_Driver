/*
 * EXTI_private.h
 *
 *  Created on: Oct 2, 2021
 *      Author: KeroEmad
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define EXTI_u8_GICR_REG		*((volatile u8*)0x5B)
#define EXTI_u8_GIFR_REG		*((volatile u8*)0x5A)

#define EXTI_u8_MCUCR_REG		*((volatile u8*)0x55)
#define EXTI_u8_MCUCSR_REG		*((volatile u8*)0x54)


#endif /* EXTI_PRIVATE_H_ */
