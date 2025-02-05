

#include "types.h"
#include "delay.h"
#include "lcd.h"
#include <string.h>
#include "pass_inter.h"
#define I2C_EEPROM_SA 0x50 // EEPROM slave address
#define PASSWORD_LENGTH 4
/*void VerifyStoredPassword(void) {
    char stored_password[PASSWORD_LENGTH + 1] = {0};

    // Read the password from EEPROM
    i2c_eeprom_sequentialread(I2C_EEPROM_SA, 0x00, (s8*)stored_password, PASSWORD_LENGTH);
    stored_password[PASSWORD_LENGTH] = '\0'; // Null-terminate the stored password string

    // Display the stored password on the LCD
    CmdLCD(CLEAR_LCD);
    StrLCD("Stored Pwd:");
    delay_ms(1000);
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD(stored_password); // Display the stored password
    delay_ms(3000); // Hold the stored password on the screen
}*/

void CheckPassword(void) {
    char stored_password[PASSWORD_LENGTH + 1] = {0};
    char entered_password[PASSWORD_LENGTH + 1] = {0};
    unsigned char key;
    int i = 0;

    // Read the stored password from EEPROM
    i2c_eeprom_sequentialread(I2C_EEPROM_SA, 0x00, (s8*)stored_password, PASSWORD_LENGTH);
    stored_password[PASSWORD_LENGTH] = '\0';  // Null-terminate the stored password string

    // Prompt the user to enter the password
    CmdLCD(CLEAR_LCD);
    StrLCD("Enter Password:");
    delay_ms(500);
    CmdLCD(GOTO_LINE2_POS0);
 i2c_eeprom_sequentialread(I2C_EEPROM_SA, 0x00, (s8*)stored_password, PASSWORD_LENGTH);
    stored_password[PASSWORD_LENGTH] = '\0'; 
    // Get password input from the keypad
    while (i < PASSWORD_LENGTH) {
        key = getkey();

        if (key != 'x') {
            if (key >= '0' && key <= '9') {
                entered_password[i] = key;
                CharLCD(entered_password[i]);  // Display * instead of the actual number for security
                i++;
            } else if (key == '=') {  // Assuming '=' is the delete key
                if (i > 0) {
                    i--;
                    CmdLCD(GOTO_LINE2_POS0 + i);  // Move cursor back one position
                    CharLCD(' ');  // Clear the last character
                    CmdLCD(GOTO_LINE2_POS0 + i);  // Move cursor back to the cleared position
                }
            }
        }
        delay_ms(200);  // Debounce delay
    } i2c_eeprom_sequentialread(I2C_EEPROM_SA, 0x00, (s8*)stored_password, PASSWORD_LENGTH);
    stored_password[PASSWORD_LENGTH] = '\0'; 
    entered_password[PASSWORD_LENGTH] = '\0';  // Null-terminate the entered password string

    // Compare the entered password with the stored password
    if (strcmp(stored_password, entered_password) == 0) {
        CmdLCD(CLEAR_LCD);
        startTimerAndVerifyOTP();  // Proceed to OTP verification
    } else {
        CmdLCD(CLEAR_LCD);
        StrLCD("Access Denied");
        delay_ms(2000);
    }

    CmdLCD(CLEAR_LCD);
    StrLCD("Restarting...");
    delay_ms(500);
}

void ChangePassword(void) {
    char new_password[PASSWORD_LENGTH + 1] = {0};
    unsigned char key;
    int i = 0;


    CmdLCD(CLEAR_LCD);
    StrLCD("Change Password");
    delay_ms(500);
    CmdLCD(CLEAR_LCD);
    StrLCD("Enter New Pwd:");
    CmdLCD(GOTO_LINE2_POS0);

    // Get new password input from the keypad
    while (i < PASSWORD_LENGTH) {
        key = getkey();
            if ((key = getkey()) != 'x') {
            if (key >= '0' && key <= '9' && i < OTP_LENGTH) {
              new_password[i] = key;
                CmdLCD(GOTO_LINE2_POS0 + i); // Move the cursor to the correct position
                CharLCD(new_password[i]); // Display the entered number
                i++;
            } else if (key == '=' && i > 0) { // Backspace functionality (using '*' as backspace)
                i--;
               new_password[i] = '\0'; // Clear the last entered character
                CmdLCD(GOTO_LINE2_POS0 + i); // Move cursor to the deleted position
                CharLCD(' '); // Clear the character on the LCD
                CmdLCD(GOTO_LINE2_POS0 + i); // Move cursor back to the position
            }
        }
						delay_ms(200); // Debounce delay
    }
		 
    new_password[PASSWORD_LENGTH] = '\0'; // Null-terminate the new password string

    // Write the new password to EEPROM
    i2c_eeprom_pagewrite(I2C_EEPROM_SA, 0x00, (u8*)new_password, PASSWORD_LENGTH);

    CmdLCD(CLEAR_LCD);
    StrLCD("Password Changed");
		 //i2c_eeprom_sequentialread(I2C_EEPROM_SA, 0x00, (s8*)stored_password, PASSWORD_LENGTH);
   // stored_password[PASSWORD_LENGTH] = '\0'; // Null-terminate the stored password string
    delay_ms(500);
    CmdLCD(CLEAR_LCD);
		
		
	//	CheckPassword();
		
		    
}
