#include <lpc21xx.h>
#include "types.h"
#include "delay.h"
//pins connected to i2c bus lines
#define SCL 2  //p0.2
#define SDA 3  //p0.3

//defines for I2C_SPEED Configuration
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define I2C_SPEED   100000    //100KHz

#define LOADVAL ((PCLK/I2C_SPEED)/2)

//bit defines for I2CONSET sfr?
#define   AA_BIT 2
#define   SI_BIT 3
#define  STO_BIT 4
#define  STA_BIT 5
#define I2EN_BIT 6

//bit defines for I2CONCLR sfr?
#define   AAC_BIT 2
#define   SIC_BIT 3
#define  STAC_BIT 5
#define I2ENC_BIT 6

void init_i2c(void)
{
        //cfg p0.2 & p0.3 as scl,sda pins
        PINSEL0|=0x00000050;
        //enable i2c peripheral operation
        I2CONSET=1<<I2EN_BIT;
        //cfg i2c speed
        I2SCLH=LOADVAL;
        I2SCLL=LOADVAL;
}

void i2c_start(void)
{
 // start condition
 I2CONSET=1<<STA_BIT;
 //wait for SI bit status
 while(((I2CONSET>>SI_BIT)&1)==0);
 //clear start condition
 I2CONCLR=1<<STAC_BIT;
}

void i2c_write(u8 wByte)
{
 // place data in buffer
 I2DAT=wByte;
 //clear SI bit to trigger byte transfer
 I2CONCLR=1<<SIC_BIT;
 //wait for SI bit status
 while(((I2CONSET>>SI_BIT)&1)==0);
 //ack expected
}

void i2c_stop(void)
{
 // start condition
 I2CONSET=1<<STO_BIT;
 //clear SI bit to trigger stop bit send
 I2CONCLR=1<<SIC_BIT;
}

void i2c_restart(void)
{
   // start condition
   I2CONSET=1<<STA_BIT;
   //clr SI_BIT to trigger restart bit send
   I2CONCLR=1<<SIC_BIT;
   //wait for SI bit status
   while(((I2CONSET>>SI_BIT)&1)==0);
   // clear restart condition
   I2CONCLR=1<<STAC_BIT;
}

u8 i2c_nack(void)
{
   //Assert Not of Ack?
   I2CONSET = 0x00;
   //Clear SI bit to trigger reception of byte
   I2CONCLR = 1<<SIC_BIT;
   //wait for byte reception
   while(((I2CONSET>>SI_BIT)&1)==0);
   //read received byte;
   return I2DAT;
}

u8 i2c_mack(void)
{
   //Assert  Ack
   I2CONSET = 1<<AA_BIT;
   //Clear SI bit to trigger reception of byte
   I2CONCLR = 1<<SIC_BIT;
   //wait for byte reception
   while(((I2CONSET>>SI_BIT)&1)==0);
         //clear AA_BIT
         I2CONCLR=1<<AAC_BIT;
   //read received byte;
   return I2DAT;
}

void i2c_eeprom_bytewrite(u8 slaveAddr,
                                u8 wBuffAddr,
                          u8 wByte)
{
        i2c_start();
        i2c_write(slaveAddr<<1);
        i2c_write(wBuffAddr);
        i2c_write(wByte);
        i2c_stop();
        delay_ms(1);
}

u8 i2c_eeprom_randomread(u8 slaveAddr,
                               u8 rBuffAddr)

{
        u8 rByte;
        i2c_start();
        i2c_write(slaveAddr<<1);
        i2c_write(rBuffAddr);
        i2c_restart();
        i2c_write((slaveAddr<<1)|1);
        rByte=i2c_nack();
        i2c_stop();
        return rByte;
}

void i2c_eeprom_pagewrite(u8 slaveAddr, u16 wBuffStartAddr,u8 *p,u32 nBytes)
{
        u32 i;
        i2c_start();
        i2c_write(slaveAddr<<1);
        i2c_write(((wBuffStartAddr>>8)&0xff));
                i2c_write(((wBuffStartAddr)&0xff));
        for(i=0;i<nBytes;i++)
        {
          i2c_write(p[i]);
        }
        i2c_stop();
        delay_ms(10);
}

void i2c_eeprom_sequentialread(u8 slaveAddr,
                                     u16 rBuffStartAddr,
                               s8 *p,
                               u32 nBytes)
{
        u32 i;
        i2c_start();
        i2c_write(slaveAddr<<1);
        i2c_write(((rBuffStartAddr>>8)&0xff));
                i2c_write(((rBuffStartAddr)&0xff));
        i2c_restart();
        i2c_write((slaveAddr<<1)|1);
        for(i=0;i<(nBytes-1);i++)
        {
          p[i]=i2c_mack();
        }
        p[i]=i2c_nack();
        i2c_stop();
}