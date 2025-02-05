//otp.c
#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "lcd.h"
#include <string.h>
#include "pass_inter.h"
#include <stdlib.h>
#include <time.h>

char generatedOTP[OTP_LENGTH + 1] = {0};


void generateOTPfunc( ) {
	int i;
	unsigned int seed = getRTCSeconds(); // Use RTC seconds as the seed
    srand(seed);  // Seed the random number generator

    for (i = 0; i < OTP_LENGTH; i++) {
       generatedOTP[i] = '0' + rand() % 10; // Generate a digit between '0' and '9'
    }
    // Send OTP via UART GSM;
		 U0_TxString("ATE0\r\n");
    delay_ms(500);

    // Set GSM module to SMS text mode
    U0_TxString("AT+CMGF=1\r\n");
    delay_ms(500);
    // Send the SMS command with the recipient's phone number
    U0_TxString("AT+CMGS=\"7674957276\"\r\n");
    delay_ms(500);
    // Send the OTP message
    U0_TxString("Your OTP is: ");
    U0_TxString(generatedOTP);
    delay_ms(500);
    // End the SMS with Ctrl+Z (0x1A)
    U0_TxChar(0x1A);
    delay_ms(500);  // Wait for the GSM module to process and send the message
    //U0_TxString("Your OTP is: ");
    //U0_TxString(generatedOTP);
    //U0_TxString("\r\n");

    // Display OTP sent message
    CmdLCD(CLEAR_LCD);
    StrLCD("OTP Sent!");
    delay_ms(1000);
    // Start the 30-second timer
}



void startTimerAndVerifyOTP(void) {
    unsigned int timeLeft = OTP_TIMEOUT; // 30 seconds countdown
    char entered_otp[OTP_LENGTH + 1] = {0}; // Buffer to store the entered OTP
    unsigned char key;
    int i = 0;

    // Generate a new OTP and send it via GSM
    generateOTPfunc();
    //sendOTPViaGSM(generatedOTP);

    while (timeLeft > 0) {
        // Display the countdown timer on the first line
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("Time left: ");
        CharLCD('0' + timeLeft / 10); // Display tens digit
        CharLCD('0' + timeLeft % 10); // Display units digit

        // Check for user input (non-blocking)
        if ((key = getkey()) != 'x') {
            if (key >= '0' && key <= '9' && i < OTP_LENGTH) {
                entered_otp[i] = key;
                CmdLCD(GOTO_LINE2_POS0 + i); // Move the cursor to the correct position
                CharLCD(entered_otp[i]); // Display the entered number
                i++;
            } else if (key == '=' && i > 0) { // Backspace functionality (using '*' as backspace)
                i--;
                entered_otp[i] = '\0'; // Clear the last entered character
                CmdLCD(GOTO_LINE2_POS0 + i); // Move cursor to the deleted position
                CharLCD(' '); // Clear the character on the LCD
                CmdLCD(GOTO_LINE2_POS0 + i); // Move cursor back to the position
            }
        }

        // If OTP is fully entered, verify it immediately
        if (i == OTP_LENGTH) {
            entered_otp[OTP_LENGTH] = '\0'; // Null-terminate the entered OTP string
            if (strcmp(generatedOTP, entered_otp) == 0) {
                CmdLCD(CLEAR_LCD);
                StrLCD("OTP Verified");
                delay_ms(500);
                handleSlidingDoorAfterOTP();
                return; // Exit the function upon successful verification
            } else {
                CmdLCD(CLEAR_LCD);
                StrLCD("Invalid OTP");
                delay_ms(500);
                break; // Exit the function on failure to verify OTP
            }
        }

        // Wait for 1 second before updating the countdown
        delay_ms(300);
        timeLeft--; // Decrement the countdown timer

        // If time runs out, display a timeout message
        if (timeLeft == 0) {
            CmdLCD(CLEAR_LCD);
            StrLCD("Time's up!");
            delay_ms(500);
            break; // Exit the function if time runs out
        }
    }
}
