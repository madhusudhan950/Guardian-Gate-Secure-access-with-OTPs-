//lcd.c
#include <LPC21xx.h>
#include "lcd.h"
#include "types.h"
#include "delay.h"
void InitLCD(void);
void CmdLCD(u8 cmd);
void WriteLCD(u8 Dat);


void InitLCD(void)
{
	//cfg gpio pins as out for data,rs,rw,en
IODIR0|=1<<LCD_EN|1<<LCD_RW|1<<LCD_RS|0xFF<<LCD_DATA;
	delay_ms(15);
	CmdLCD(0x30);
	delay_ms(5);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);	
}


void CmdLCD(u8 cmd)
{
	//select cmd/ins reg
	IOCLR0=1<<LCD_RS;
	//write cmd into cmd reg
	WriteLCD(cmd);
}


void WriteLCD(u8 Dat)
{
	//select write operation
	IOCLR0=1<<LCD_RW;
	//put data on data pin d0 to d7
	IOPIN0=((IOPIN0&~(0xFF<<LCD_DATA))|(Dat<<LCD_DATA));
	//enable high to low operation
	IOSET0=1<<LCD_EN;
	delay_us(1);//latching time
	IOCLR0=1<<LCD_EN;
	delay_ms(2);//internal processing time
}	

void CharLCD(u8 asciiVal)
{
	//select data reg
	IOSET0=1<<LCD_RS;
	//write asciival/byte into data reg for ddram/cgram
	WriteLCD(asciiVal);	
}



void StrLCD(s8 *s)
{
	while(*s)
		CharLCD(*s++);
}	

void U32LCD(u32 n)
{
	u8 a[10];
	s32 i=0;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n>0)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
		for(--i;i>=0;i--)
		   CharLCD(a[i]);
	}
}

void S32LCD(s32 n)
{
	if(n<0)
	{
		CharLCD('-');
		n=-n;
	}
	U32LCD(n);
}

void F32LCD(f32 f,u32 nDP)
{
	u32 iF;
	s32 i;
	if(f<0.0)
	{
		CharLCD('-');
		f=-f;
	}
  iF=f;
  U32LCD(iF);
  CharLCD('.');
	for(i=0;i<nDP;i++)
	{
		f=(f-iF)*10;
		iF=f;
		CharLCD(iF+48);
	}
}

void HexLCD(u32 n)
{
	u8 a[8],t;
	s32 i=0;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n>0)
		{
			t=n%16;
			(t<10) ? (t+=48) : (t+=55);
			a[i++]=t;
			n/=16;
		}
		for(--i;i>=0;i--)
		   CharLCD(a[i]);
	}
}

void BinLCD(u32 n,u32 nBD)
{
	s32 i;
	for(i=(nBD-1);i>=0;i--)
	{
		CharLCD(((n>>i)&1)+48);
	}
}

void OctLCD(u32 n)
{
    u32 temp = n;
    u32 octal = 0, place = 1;
    if (n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while (temp > 0)
        {
            octal += (temp % 8) * place;
            temp /= 8;
            place *= 10;
        }
        U32LCD(octal);
    }
}

void BuildCGRAM(u8 *p,u32 nBytes)
{
	s32 i;
	//goto cgram start
  	CmdLCD(GOTO_CGRAM_START);
	for(i=0;i<nBytes;i++)
	{
		//write to cgram via data reg
		CharLCD(p[i]);
	}
	//go back to ddram
	CmdLCD(GOTO_LINE1_POS0);	
}
