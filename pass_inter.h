#include "types.h"
#include <lpc21xx.h>
void VerifyStoredPassword(void);
void CheckPassword(void);
void ChangePassword(void);
void initInterrupt(void);
void INT0ISR(void)__irq;

void i2c_eeprom_pagewrite(u8 slaveAddr,
	                        u8 wBuffStartAddr,
                          u8 *p,
                          u32 nBytes);

void i2c_eeprom_sequentialread(u8 slaveAddr,
	                             u8 rBuffStartAddr,
                               s8 *p,
                               u32 nBytes)   ;
void init_i2c(void);
void initkeypad(void);
char getkey(void);




#define FOSC 12000000 //Hz
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define BAUD 9600
#define BAUDLOADVAL (PCLK/(16 * BAUD))

//defines for UxLSR
#define DR_BIT   0
#define TEMT_BIT 5
//defines for UxLCR
#define WORD_LEN_SEL_BITS 3
#define DLAB_BIT          7
void U0_TxString(const char *);
void U0_TxChar(unsigned char);
void InitUART0(void);



////////////////////////////////////////


#define FOSC 12000000

#define PREINT_VAL ((PCLK / 32768) - 1)
#define PREFRAC_VAL  (PCLK - ((PREINT + 1) * 32768))

#define OTP_TIMEOUT 59
#define OTP_LENGTH 4

////////////////////////////////

#define OTP_LENGTH 4
void generateOTPfunc(void );
void startTimerAndVerifyOTP(void);


void RTC_Init(void);
void RTC_Rtc_Init(void);
unsigned int getRTCSeconds(void);
void startTimer(void);
unsigned int getRTCSeconds(void) ;

void handleSlidingDoorAfterOTP(void);
void loadCustomChar(unsigned char location, unsigned char *charmap);


void OTP(void );
int VerifyOTP(void);



