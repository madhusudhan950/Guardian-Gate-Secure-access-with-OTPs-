//timer.c
#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "lcd.h"
#include <string.h>
#include "pass_inter.h"

void RTC_Init(void) {
    PREINT = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;
    CCR = 0x01; // Enable RTC
}
void RTC_Rtc_Init(void) {
    YEAR = 2024;
    MONTH = 5;
    DOM = 21;
    HOUR = 19;
    MIN = 50;
    SEC = 0;
    DOW = 2;
}
unsigned int getRTCSeconds(void) {
    return SEC; // Return the seconds value from RTC
}

/*void startTimer(void) {
    unsigned int startTime = getRTCSeconds(); // Get the starting time
    unsigned int currentTime;
    unsigned int timeLeft;

    while (1) {
        currentTime = getRTCSeconds();
        timeLeft = OTP_TIMEOUT - (currentTime - startTime);
        
        CmdLCD(CLEAR_LCD);
        StrLCD("Time left:");
        //CmdLCD(GOTO_LINE2_POS0);
        CharLCD('0' + timeLeft / 10); // Display tens digit
        CharLCD('0' + timeLeft % 10); // Display units digit
        delay_ms(1000); // Wait for 1 second before updating the countdown

        if (timeLeft <= 0) {
            CmdLCD(CLEAR_LCD);
            StrLCD("Time's up!");
            delay_ms(2000);
            break;
        }
    }

    VerifyOTP(); // Prompt for OTP verification after countdown
}
*/
