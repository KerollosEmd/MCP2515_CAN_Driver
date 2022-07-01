/****************************************/
/*				Name: kerollos Emad 	*/
/* 				Date: 18-9-2021			*/
/*				SWC	: LCD				*/
/*				Version: 1.0			*/
/****************************************/

#ifndef _LCD_INTERFACE_H 
#define _LCD_INTERFACE_H

void LCD_voidInit(void);

void LCD_voidWriteChar(u8 Copy_u8Char);

void LCD_voidWriteCommand(u8 Copy_u8Cmnd);

void LCD_voidWriteString(u8* Copy_Pu8String);

void LCD_voidWritNumber(u32 Copy_u32Number);

void LCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos);

/*macros for lines  of lcd*/
#define LCD_u8_LINE_1 		0
#define LCD_u8_LINE_2		1

/*macros for instructions*/
#define LCD_Clear                 0x01                /* replace all characters with ASCII 'space'                       */
#define LCD_Home                  0x02                /* return cursor to first position on first line                   */
#define LCD_EntryMode             0x06                // shift cursor from left to right on read/write
#define LCD_DisplayOff            0x08                // turn display off
#define LCD_DisplayOn             0x0C                // display on, cursor off, don't blink character
#define LCD_Disp_Curser_Bl 	      0x0f                // display on, cursor on , blink character
#define LCD_FunctionReset         0x30                // reset the LCD
#define LCD_FunctionSet8bit       0x38                // 8-bit data, 2-line display, 5 x 7 font
#define LCD_SetCursor             0x80                // set cursor position

#endif
