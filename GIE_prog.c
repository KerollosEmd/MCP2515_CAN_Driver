/*
 * EXTI_prog.c
 *
 *  Created on: Oct 2, 2021
 *      Author: KeroEmad
 */
#include "STD_Types.h"
#include "BIT_MATH.h"


#define GIE_u8_SREG_REG     *((volatile u8*)0x5F)

void GIE_voidEnable(void){
    SET_BIT(GIE_u8_SREG_REG,7);
}
void GIE_voidDisable(void){
    CLR_BIT(GIE_u8_SREG_REG,7);
}


