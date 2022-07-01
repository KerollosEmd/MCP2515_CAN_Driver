/*
 * EXTI_interface.h
 *
 *  Created on: Oct 2, 2021
 *      Author: KeroEmad
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


/*macros for EXTI Number*/
//#define exti 

typedef enum{
    EXTI_u8_EXTI_0 =0,
    EXTI_u8_EXTI_1,
    EXTI_u8_EXTI_2
}EXTINum_enumType;

typedef enum{
    EXTI_u8_FALLING_EDGE =0,
    EXTI_u8_RISING_EDGE,
    EXTI_u8_ANY_LOGICAL_CHANGE,
    EXTI_u8_LOW_LEVEL
}EXTITrigSourc_enumType;

void EXTI_voidEnable(void);

u8 EXTI_u8INIT(EXTINum_enumType COPY_enuEXTI_NUM, EXTITrigSourc_enumType COPY_u8EXTI_SenseControl);

u8 EXTI_u8Enable(EXTINum_enumType COPY_enuEXTI_NUM);

u8 EXTI_u8Disable(EXTINum_enumType COPY_enuEXTI_NUM);

u8 EXTI_u8SetCallBack(EXTINum_enumType Copy_enumEXTINum, void(*Copy_PtrToFun)(void));




#endif /* EXTI_INTERFACE_H_ */
