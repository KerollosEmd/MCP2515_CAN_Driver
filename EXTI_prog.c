/*
 * EXTI_prog.c
 *
 *  Created on: Oct 2, 2021
 *      Author: KeroEmad
 */
#include "STD_Types.h"
#include "BIT_MATH.h"

#include "EXTI_config.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"

/*array of global pointers to function*/
static void (*EXTI_APtrToFun[3])(void)={
		NULL, NULL, NULL
};


u8 EXTI_u8INIT(EXTINum_enumType COPY_enuEXTI_NUM, EXTITrigSourc_enumType COPY_enuEXTI_SenseControl){
	u8 Local_u8ErrorState = STD_TYPES_OK;

	/*Select EXTI Number*/
	switch (COPY_enuEXTI_NUM)
	{
	case EXTI_u8_EXTI_0:
		/* select trigger */
		switch (COPY_enuEXTI_SenseControl)
		{
		case EXTI_u8_ANY_LOGICAL_CHANGE:
			/* code */
			CLR_BIT(EXTI_u8_MCUCR_REG,1);
			SET_BIT(EXTI_u8_MCUCR_REG,0);
			/*enable EXTI 0*/
			SET_BIT(EXTI_u8_GICR_REG,6);

			break;

		case EXTI_u8_LOW_LEVEL:
			/* code */
			CLR_BIT(EXTI_u8_MCUCR_REG,1);
			CLR_BIT(EXTI_u8_MCUCR_REG,0);
			/*enable EXTI 0*/
			SET_BIT(EXTI_u8_GICR_REG,6);

			break;
		case EXTI_u8_RISING_EDGE:
			/* code */
			SET_BIT(EXTI_u8_MCUCR_REG,1);
			SET_BIT(EXTI_u8_MCUCR_REG,0);
			/*enable EXTI 0*/
			SET_BIT(EXTI_u8_GICR_REG,6);

			break;

		case EXTI_u8_FALLING_EDGE:
			/* code */
			SET_BIT(EXTI_u8_MCUCR_REG,1);
			CLR_BIT(EXTI_u8_MCUCR_REG,0);
			/*enable EXTI 0*/
			SET_BIT(EXTI_u8_GICR_REG,6);

			break;

		default:Local_u8ErrorState=STD_TYPES_NOTOK;
		break;
		}
		break;

		case EXTI_u8_EXTI_1:
			/* select trigger */
			switch (COPY_enuEXTI_SenseControl)
			{
			case EXTI_u8_ANY_LOGICAL_CHANGE:
				/* code */
				CLR_BIT(EXTI_u8_MCUCR_REG,3);
				SET_BIT(EXTI_u8_MCUCR_REG,2);
				/*enable EXTI 0*/
				SET_BIT(EXTI_u8_GICR_REG,7);

				break;

			case EXTI_u8_LOW_LEVEL:
				/* code */
				CLR_BIT(EXTI_u8_MCUCR_REG,3);
				CLR_BIT(EXTI_u8_MCUCR_REG,2);
				/*enable EXTI 0*/
				SET_BIT(EXTI_u8_GICR_REG,7);

				break;
			case EXTI_u8_RISING_EDGE:
				/* code */
				SET_BIT(EXTI_u8_MCUCR_REG,3);
				SET_BIT(EXTI_u8_MCUCR_REG,2);
				/*enable EXTI 0*/
				SET_BIT(EXTI_u8_GICR_REG,7);

				break;

			case EXTI_u8_FALLING_EDGE:
				/* code */
				SET_BIT(EXTI_u8_MCUCR_REG,3);
				CLR_BIT(EXTI_u8_MCUCR_REG,2);
				/*enable EXTI 0*/
				SET_BIT(EXTI_u8_GICR_REG,7);

				break;

			default: Local_u8ErrorState=STD_TYPES_NOTOK;
			break;
			}
			break;
			case EXTI_u8_EXTI_2:
				/* select trigger */
				switch (COPY_enuEXTI_SenseControl)
				{
				case EXTI_u8_RISING_EDGE:
					/* code */
					SET_BIT(EXTI_u8_MCUCSR_REG,6);
					/*enable EXTI 0*/
					SET_BIT(EXTI_u8_GICR_REG,5);

					break;

				case EXTI_u8_FALLING_EDGE:
					/* code */
					CLR_BIT(EXTI_u8_MCUCSR_REG,6);
					/*enable EXTI 0*/
					SET_BIT(EXTI_u8_GICR_REG,5);

					break;

				default:
					Local_u8ErrorState=STD_TYPES_NOTOK;
					break;
				}
				break;
				default:
					Local_u8ErrorState=STD_TYPES_NOTOK;
					break;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8Enable(EXTINum_enumType COPY_enuEXTI_NUM){
	u8 Local_u8ErrorState = STD_TYPES_OK;

	switch (COPY_enuEXTI_NUM)
	{
	case EXTI_u8_EXTI_0: SET_BIT(EXTI_u8_GICR_REG,6);break;
	case EXTI_u8_EXTI_1: SET_BIT(EXTI_u8_GICR_REG,7);break;
	case EXTI_u8_EXTI_2: SET_BIT(EXTI_u8_GICR_REG,5);break;

	default: Local_u8ErrorState=STD_TYPES_NOTOK;
	break;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8Disable(EXTINum_enumType COPY_enuEXTI_NUM){
	u8 Local_u8ErrorState = STD_TYPES_OK;

	switch (COPY_enuEXTI_NUM)
	{
	case EXTI_u8_EXTI_0: CLR_BIT(EXTI_u8_GICR_REG,6);break;
	case EXTI_u8_EXTI_1: CLR_BIT(EXTI_u8_GICR_REG,7);break;
	case EXTI_u8_EXTI_2: CLR_BIT(EXTI_u8_GICR_REG,5);break;

	default: Local_u8ErrorState=STD_TYPES_NOTOK;
	break;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8SetCallBack(EXTINum_enumType Copy_enumEXTINum, void(*Copy_PtrToFun)(void)){
	u8 Local_u8ErrorState =STD_TYPES_OK;

	if((Copy_PtrToFun!=NULL)&&(Copy_enumEXTINum<3)&&(Copy_enumEXTINum>=0)){
		/*update global pointer  to functions*/
		EXTI_APtrToFun[Copy_enumEXTINum]=Copy_PtrToFun;
	}else{
		Local_u8ErrorState=STD_TYPES_NOTOK;
	}

	return Local_u8ErrorState;
}

void __vector_1(void) __attribute__((signal));

void __vector_1(void){
	if(EXTI_APtrToFun[EXTI_u8_EXTI_0]!=NULL){
		EXTI_APtrToFun[EXTI_u8_EXTI_0]();
	}
}

void __vector_2(void) __attribute__((signal));

void __vector_2(void){
	if(EXTI_APtrToFun[EXTI_u8_EXTI_1]!=NULL){
		EXTI_APtrToFun[EXTI_u8_EXTI_1]();
	}
}

void __vector_3(void) __attribute__((signal));

void __vector_3(void){
	if(EXTI_APtrToFun[EXTI_u8_EXTI_2]!=NULL){
		EXTI_APtrToFun[EXTI_u8_EXTI_2]();
	}
}

