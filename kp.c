//keypadfun//
#include<LPC21xx.h>
#define COL1 16
#define COL2 17
#define COL3 18
#define COL4 19
#define row1 21
#define row2 22
#define row3 23
#define row4 24


void initkeypad(void){
IODIR1=0xff<<21;
}

char getkey(void) {
    char key = 'x';  // Default to 'x' if no key is pressed

    // Scan the keypad rows one by one
    IOCLR1 |= 0xff << 21;
    IOSET1 |= 0x0E << 21;
    if (((IOPIN1 >> COL1) & 1) == 0) { key = '7'; }
    else if (((IOPIN1 >> COL2) & 1) == 0) { key = '8'; }
    else if (((IOPIN1 >> COL3) & 1) == 0) { key = '9'; }
    else if (((IOPIN1 >> COL4) & 1) == 0) { key = '/'; }

    IOCLR1 |= 0xff << 21;
    IOSET1 |= 0x0D << 21;
    if (((IOPIN1 >> COL1) & 1) == 0) { key = '4'; }
    else if (((IOPIN1 >> COL2) & 1) == 0) { key = '5'; }
    else if (((IOPIN1 >> COL3) & 1) == 0) { key = '6'; }
    else if (((IOPIN1 >> COL4) & 1) == 0) { key = '*'; }

    IOCLR1 |= 0xff << 21;
    IOSET1 |= 0x0B << 21;
    if (((IOPIN1 >> COL1) & 1) == 0) { key = '1'; }
    else if (((IOPIN1 >> COL2) & 1) == 0) { key = '2'; }
    else if (((IOPIN1 >> COL3) & 1) == 0) { key = '3'; }
    else if (((IOPIN1 >> COL4) & 1) == 0) { key = '-'; }

    IOCLR1 |= 0xff << 21;
    IOSET1 |= 0x07 << 21;
    if (((IOPIN1 >> COL1) & 1) == 0) { key = 'o'; }
    else if (((IOPIN1 >> COL2) & 1) == 0) { key = '0'; }
    else if (((IOPIN1 >> COL3) & 1) == 0) { key = '='; }
    else if (((IOPIN1 >> COL4) & 1) == 0) { key = '+'; }

    return key;
}
