#include <LPC21xx.h>
#include "types.h"
#include "pass_inter.h"

#define DLAB_BIT 7
//#define WORD_LEN_SEL_BITS 0x03 // 8-bit character length
//#define BAUDLOADVAL 97 // Value for setting baud rate (assuming 9600 baud rate)
//#define TEMT_BIT 6
#define DR_BIT 0

void InitUART0(void) {
    // Configure pin connect block for P0.0/TXD0 & P0.1/RXD0
    PINSEL0 |= 0x00000005;

    // Configure U0LCR (Line Control Register)
    U0LCR = (1 << DLAB_BIT) | WORD_LEN_SEL_BITS;

    // Configure Baudrate generator
    U0DLM = BAUDLOADVAL >> 8;
    U0DLL = BAUDLOADVAL;

    // Clear DLAB bit
    U0LCR &= ~(1 << DLAB_BIT);
}

void U0_TxChar(u8 sByte) {
    // Place data/byte to be serialized out into TX buffer
    U0THR = sByte;

    // Wait until transmission completion status
    while (((U0LSR >> TEMT_BIT) & 1) == 0);
}

u8 U0_RxChar(void) {
    // Wait until reception status
    while (((U0LSR >> DR_BIT) & 1) == 0);

    // Read received data
    return U0RBR;
}

void U0_TxString(const char* str) {
    while (*str) {
        U0_TxChar(*str++);
    }
}

