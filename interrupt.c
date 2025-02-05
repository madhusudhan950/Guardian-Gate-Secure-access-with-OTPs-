

#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "lcd.h"
#include <string.h>
#include "pass_inter.h"
#include <stdlib.h>
void initInterrupt(void)
	{
VICIntEnable=0x01<<14;
//enable external interrupt 0
VICVectCntl0=(0x01<<5)|14;
//enable vectored irqslot and as int src 14;
VICVectAddr0=(unsigned)INT0ISR;
//assiging the isr address in respective address slot

//INT0 SPECIFIC CONFIGURATION
//
	
	PINSEL1=0x15400001;//p0.16 as INT0
	EXTMODE|=0x01;//INT0 set to edge sensitve
	EXTPOLAR|=0x00;//INT0 set falling edge
}
	
	char generateOTP[OTP_LENGTH + 1] = {0};
	
void INT0ISR(void) __irq {
    unsigned int temp;
    temp = EXTINT;  // Read the value of the external interrupt flag register
   
    CmdLCD(CLEAR_LCD);
    StrLCD("Verifying OTP");
    delay_ms(1000);

    // Generate and send OTP via GSM
    OTP();
       
    // Verify OTP before allowing password reset
    if (VerifyOTP()) {
        CmdLCD(CLEAR_LCD);
        StrLCD("Change Password:");
        delay_ms(500);
        ChangePassword(); // Call the function to reset the password
    } else {
        CmdLCD(CLEAR_LCD);
        StrLCD("ACCESS DENIED!");
        delay_ms(2000);
        CmdLCD(CLEAR_LCD);
        
    }

    EXTINT = 1 << 0;  // Clear the interrupt flag for INT0
    VICVectAddr = 0x00;  // Mark the end of the ISR
}

int VerifyOTP(void) {
    unsigned int timeLeft  = OTP_TIMEOUT;  // Store the OTP sent time
   // unsigned int currentTime;
    char entere_otp[OTP_LENGTH + 1] = {0}; // Store entered OTP
    unsigned char key;
    int i = 0;

    // Generate a new OTP
    // generateOTP(generatedOTP); // Uncomment this if you want to generate a new OTP

     while (timeLeft > 0) {
        // Display the countdown timer on the first line
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("Time left: ");
        CharLCD('0' + timeLeft / 10); // Display tens digit
        CharLCD('0' + timeLeft % 10); // Display units digit

        // Check if the user has entered the OTP
              if ((key = getkey()) != 'x') {
            if (key >= '0' && key <= '9' && i < OTP_LENGTH) {
                entere_otp[i] = key;
                CmdLCD(GOTO_LINE2_POS0 + i); // Move the cursor to the correct position
                CharLCD(entere_otp[i]); // Display the entered number
                i++;
            } else if (key == '=' && i > 0) { // Backspace functionality (using '*' as backspace)
                i--;
                entere_otp[i] = '\0'; // Clear the last entered character
                CmdLCD(GOTO_LINE2_POS0 + i); // Move cursor to the deleted position
                CharLCD(' '); // Clear the character on the LCD
                CmdLCD(GOTO_LINE2_POS0 + i); // Move cursor back to the position
            }
        }

        // If OTP is fully entered, verify it immediately
        if (i == OTP_LENGTH) {
            entere_otp[OTP_LENGTH] = '\0'; // Null-terminate the entered OTP string
            if (strcmp(generateOTP,entere_otp) == 0) {
                CmdLCD(CLEAR_LCD);
                StrLCD("OTP Verified");
                delay_ms(2000);
                return 1; // Exit the function upon successful verification
            } else {
                CmdLCD(CLEAR_LCD);
                StrLCD("Invalid OTP");
                delay_ms(2000);
                // Exit the function on failure to verify OTP
            return 0;
						}
        }

        delay_ms(300); // Wait for 1 second before updating the countdown
timeLeft --;
        if (timeLeft <= 0) {
            CmdLCD(CLEAR_LCD);
            StrLCD("Time's up!");
            delay_ms(2000);
                      return 0;
  // Exit the function if time runs out
        }
    }  return 0;

    // If OTP verification fails or time runs out, return to waiting for password
  
}




void OTP( ) {

	int i;
	unsigned int seed = getRTCSeconds(); // Use RTC seconds as the seed
    srand(seed);  // Seed the random number generator

    for (i = 0; i < OTP_LENGTH; i++) {
       generateOTP[i] = '0' + rand() % 10; // Generate a digit between '0' and '9'
    }
    // Send OTP via UART GSM;
		 U0_TxString("ATE0\r\n");
    delay_ms(500);

    // Set GSM module to SMS text mode
    U0_TxString("AT+CMGF=1\r\n");
    delay_ms(500);
    // Send the SMS command with the recipient's phone number
    U0_TxString("AT+CMGS=\"6301507552\"\r\n");
    delay_ms(500);
    // Send the OTP message
    U0_TxString("Your OTP is: ");
    U0_TxString(generateOTP);
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
   // VerifyOTP( );// Start the 30-second timer
}
