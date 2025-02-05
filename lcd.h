
#include "types.h"

#define LCD_DATA 8       // P0.8/D0-P0.15/D7
#define LCD_RS   17     // p0.16
#define LCD_RW   18     // p0.17
#define LCD_EN	 19    // p0.18



void InitLCD(void);
void CmdLCD(u8 cmd);
void CharLCD(u8 asciiVal);
void StrLCD(s8 *s);
void U32LCD(u32 n);
void S32LCD(s32 n);
void F32LCD(f32 f, u32 nDP);
void HexLCD(u32 n);
void BinLCD(u32 n, u32 nBD);
void OctLCD(u32 n);
void BuildCGRAM(u8 *p, u32 nBytes);


//HD44780 Commands
#define CLEAR_LCD            0x01
#define RET_CUR_HOME         0x02
#define SHIFT_CUR_RIGHT      0x06
#define SHIFT_CUR_LEFT       0x07
#define DSP_OFF              0x08

#define DSP_ON_CUR_OFF       0x0c
#define DSP_ON_CUR_ON        0x0E
#define DSP_ON_CUR_BLINK     0x0F
#define SHIFT_DISP_LEFT      0x10
#define SHIFT_DISP_RIGHT     0x14

#define MODE_8BIT_1LINE      0x30
#define MODE_4BIT_1LINE      0x20
#define MODE_8BIT_2LINE      0x38
#define MODE_4BIT_2LINE      0x28
#define GOTO_LINE1_POS0      0x80
#define GOTO_LINE2_POS0      0xC0
#define GOTO_LINE3_POS0      0x94
#define GOTO_LINE4_POS0      0xD4
#define GOTO_CGRAM_START     0x40

