//delay.c
void delay_us(unsigned int dlyUS)
{
         //@FOSC=12MHz,CCLK=60MHz
         //for(dlyUS*=12;dlyUS>0;dlyUS--);
   dlyUS*=12;
         while(dlyUS--);
}

void delay_ms(unsigned int dlyMS)
{
         //@FOSC=12MHz,CCLK=60MHz
         //for(dlyMS*=12000;dlyMS>0;dlyMS--);
   dlyMS*=12000;
         while(dlyMS--);
}

void delay_s(unsigned int dlyS)
{
         //@FOSC=12MHz,CCLK=60MHz
         //for(dlyS*=12000000;dlyUS>0;dlyUS--);
   dlyS*=12000000;
         while(dlyS--);
}
