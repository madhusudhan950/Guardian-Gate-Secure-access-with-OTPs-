#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "lcd.h"
#include <string.h>
#include "pass_inter.h"
#define I2C_EEPROM_SA 0x50 // EEPROM slave address
#define PASSWORD_LENGTH 4

s8 rByte __attribute__ ((at(0x40000010)));
//s8 rBytes[10] __attribute__ ((at(0x40000020)));

main() {
    init_i2c();
    InitLCD();
    initkeypad();
    initInterrupt();
	  InitUART0(); // Initialize UART for sending OTP
   RTC_Init(); // Initialize RTC for timing


   i2c_eeprom_pagewrite(I2C_EEPROM_SA, 0x00, (u8*)"1111", 4);
   // i2c_eeprom_sequentialread(I2C_EEPROM_SA, 0x00, rBytes, 4);
   
    CmdLCD(CLEAR_LCD);
    StrLCD("Welcome!");
    delay_ms(500);
    CmdLCD(CLEAR_LCD);
     {

		while(1){	
		
         CheckPassword();

			
			
		}
}}





