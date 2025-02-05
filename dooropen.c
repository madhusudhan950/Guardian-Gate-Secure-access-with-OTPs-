#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "lcd.h"
#include <string.h>
#include "pass_inter.h"

void loadSlidingDoorGraphics(void) {
    unsigned char solidBlock[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};  // Full black block (closed door)
    unsigned char emptyBlock[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  // Empty space (fully open)

    // Load the custom characters into CGRAM
    loadCustomChar(0, solidBlock);  // Load to CGRAM location 0 (closed)
    loadCustomChar(1, emptyBlock);  // Load to CGRAM location 1 (open)
}

void displaySlidingDoorOpening(void) {
    int leftPos, rightPos;
		IODIR0 |= 1 << 22;

    // Start with a fully closed door (all solid blocks)
    CmdLCD(CLEAR_LCD);
    IOSET0 |= 1 << 22;
    StrLCD("Door Opening...");
    delay_ms(1000);  // Display the message briefly
    
    CmdLCD(GOTO_LINE2_POS0);
    for (leftPos = 0; leftPos < 16; leftPos++) {
        CharLCD(0);  // Display solid block across the entire line
    }

    // Gradually replace the solid blocks with empty blocks from the center outwards
    for (leftPos = 7, rightPos = 8; leftPos >= 0; leftPos--, rightPos++) {
        CmdLCD(GOTO_LINE2_POS0 + leftPos);
        CharLCD(1);  // Replace left side with an empty block (open space)
        
        CmdLCD(GOTO_LINE2_POS0 + rightPos);
        CharLCD(1);  // Replace right side with an empty block (open space)
        
        delay_ms(100);  // Adjust delay for smoother/slower animation
    }

    delay_ms(2000);  // Hold the fully open door for a while
}

void displaySlidingDoorClosing(void) {
    int leftPos, rightPos;

    // Start with a fully open door (all empty blocks)
    CmdLCD(CLEAR_LCD);
    IOCLR0 |= 1 << 22;
    StrLCD("Door Closing...");
    delay_ms(1000);  // Display the message briefly

    // Gradually replace the empty blocks with solid blocks from the edges inwards
    for (leftPos = 0, rightPos = 15; leftPos <= 7; leftPos++, rightPos--) {
        CmdLCD(GOTO_LINE2_POS0 + leftPos);
        CharLCD(0);  // Replace left side with a solid block (closed door)
        
        CmdLCD(GOTO_LINE2_POS0 + rightPos);
        CharLCD(0);  // Replace right side with a solid block (closed door)
        
        delay_ms(100);  // Adjust delay for smoother/slower animation
    }

    delay_ms(2000);  // Hold the fully closed door for a while
}

void loadCustomChar(unsigned char location, unsigned char *charmap) {
    unsigned char i;
    location &= 0x07;  // Only 8 locations available (0-7)
    CmdLCD(0x40 | (location << 3));  // Set CGRAM address
    for (i = 0; i < 8; i++) {
        CharLCD(charmap[i]);
    }
}

void handleSlidingDoorAfterOTP(void) {
    loadSlidingDoorGraphics();  // Load sliding door graphics into CGRAM
    displaySlidingDoorOpening();  // Display opening animation
    delay_ms(1000);  // Hold the door open for a few seconds
    displaySlidingDoorClosing();  // Display closing animation
//CheckPassword();
    
}
