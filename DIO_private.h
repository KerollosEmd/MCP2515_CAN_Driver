/****************************************/
/*				Name: kerollos Emad 	*/
/* 				Date: 18-9-2021			*/
/*				SWC	: LCD				*/
/*				Version: 1.0			*/
/****************************************/

#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

/* Registers Defination for DIO */
/* PORTA Registers */
#define DIO_u8_PORTA_REG     *((volatile u8*)0x3B)
#define DIO_u8_DDRA_REG      *((volatile u8*)0x3A)
#define DIO_u8_PINA_REG      *((volatile u8*)0x39)
								 
/* PORTB Registers */            
#define DIO_u8_PORTB_REG     *((volatile u8*)0x38)
#define DIO_u8_DDRB_REG      *((volatile u8*)0x37)
#define DIO_u8_PINB_REG      *((volatile u8*)0x36)
/* PORTC Registers */            
#define DIO_u8_PORTC_REG     *((volatile u8*)0x35)
#define DIO_u8_DDRC_REG      *((volatile u8*)0x34)
#define DIO_u8_PINC_REG      *((volatile u8*)0x33)
								 
/* PORTD Registers */            
#define DIO_u8_PORTD_REG     *((volatile u8*)0x32)
#define DIO_u8_DDRD_REG      *((volatile u8*)0x31)
#define DIO_u8_PIND_REG      *((volatile u8*)0x30)

#define DIO_u8_INPUT_INIT                      0
#define DIO_u8_OUTPUT_INIT                     1

#define DIO_u8_OUTPUT_HIGH                     1
#define DIO_u8_OUTPUT_LOW                      0
#define DIO_u8_INPUT_FLOATING                  0
#define DIO_u8_INPUT_PULLED_UP                 1

#define PRIVATE_u8_CONC(B7,B6,B5,B4,B3,B2,B1,B0)		PRIVATE_u8_CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)
#define PRIVATE_u8_CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)	0b##B7##B6##B5##B4##B3##B2##B1##B0

#endif
