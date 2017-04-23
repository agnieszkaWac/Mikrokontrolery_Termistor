#include <targets/AT91SAM7.h>
#include <stdint.h>
#include"adc.h"
#include"lcd.h"
#define SW_1 PIOB_SODR_P24

#define LCD_BACKLIGHT PIOB_SODR_P20 

__attribute__ ((section(".fast"))); 
void delay(int n){
	volatile int i;
	for(i=3000*n; i>0; i--){
		__asm__("nop");
	}
}
 
int main()
{
    PMC_PCER=PMC_PCER_PIOB |PMC_PCER_PIOA |PMC_PCER_ADC;
    ADC_CR = ADC_CR_SWRST;
    ADC_CHER = ADC_CHER_CH6;


    int out, a, b;
    ADC_MR = (23<<ADC_MR_PRESCAL_BIT) | (2<<ADC_MR_STARTUP_BIT) | (1<<ADC_MR_SHTIM_BIT);
    float stopnie;
    char* outstr;

    InitLCD(); 
    InitADC(); 
    LCDSettings(); 
    LCDClearScreen();
    PIOB_SODR|= LCD_BACKLIGHT;


    while(1)
    {
      
      for(int j=0; j<115; j=j+5){
		LCDPutStr("|",j,20,SMALL,WHITE,BLACK);
      }

      LCDPutStr("38",5,0,SMALL,WHITE,BLACK);
      LCDPutStr("36",15,0,SMALL,WHITE,BLACK);
      LCDPutStr("34",25,0,SMALL,WHITE,BLACK);
      LCDPutStr("32",35,0,SMALL,WHITE,BLACK);
      LCDPutStr("30",45,0,SMALL,WHITE,BLACK);
      LCDPutStr("28",55,0,SMALL,WHITE,BLACK);
      LCDPutStr("26",65,0,SMALL,WHITE,BLACK);
      LCDPutStr("24",75,0,SMALL,WHITE,BLACK);
      LCDPutStr("22",85,0,SMALL,WHITE,BLACK);
      LCDPutStr("20",95,0,SMALL,WHITE,BLACK);
      LCDPutStr("18",105,0,SMALL,WHITE,BLACK);
      LCDPutStr("16",115,0,SMALL,WHITE,BLACK);



      int i;
      for(int i = 28; i <=123; i=i+6)
      {
        LCDPutStr("_",104,i,LARGE,WHITE,BLACK);
      }
      

     int time = 25;
     while(1)
     {    
		  delay(700);
		  ADC_CR = ADC_CR_START;
		  out = GetAdcChanel(ADC_CHN_6);
		  stopnie = ((out - 535)/5.6) + 24;
		  stopnie = stopnie*100;
		  out=(int)stopnie;
		  a=out/100;
		  b=out%100;
		  outstr = (char*)malloc(20);
		  sprintf(outstr,"%d.%d \0", a,b);
		  if(time<125){
              LCDPutStr(outstr,120,100,SMALL,WHITE,BLACK);
              if(a<15)
              {
                  LCDPutStr(".",118,time,LARGE,WHITE,BLACK);
              }
              else if(a<16)
              {
                  LCDPutStr(".",113,time,LARGE,WHITE,BLACK);
              }
              else if(a<17)
              {
                  LCDPutStr(".",108,time,LARGE,WHITE,BLACK);
              }
              else if(a<18)
              {
                  LCDPutStr(".",103,time,LARGE,WHITE,BLACK);
              }
              else if(a<19)
              {
                  LCDPutStr(".",98,time,LARGE,WHITE,BLACK);
              }else if(a<20)
              {
                  LCDPutStr(".",93,time,LARGE,WHITE,BLACK);
              }
              else if(a<21)
              {
                  LCDPutStr(".",88,time,LARGE,WHITE,BLACK);
              }
              else if(a<22)
              {
                  LCDPutStr(".",83,time,LARGE,WHITE,BLACK);
              }
              else if(a<23)
              {
                  LCDPutStr(".",78,time,LARGE,WHITE,BLACK);
              }
              else if(a<24)
              {
                  LCDPutStr(".",73,time,LARGE,WHITE,BLACK);
              }
              else if(a<25)
              {
                  LCDPutStr(".",68,time,LARGE,WHITE,BLACK);
              }
              else if(a<26)
              {
                  LCDPutStr(".",63,time,LARGE,WHITE,BLACK);
              }
              else if(a<27)
              {
                  LCDPutStr(".",58,time,LARGE,WHITE,BLACK);
              }
              else if(a<28)
              {
                  LCDPutStr(".",53,time,LARGE,WHITE,BLACK);
              }
              else if(a<29)
              {
                  LCDPutStr(".",48,time,LARGE,WHITE,BLACK);
              }
              else if(a<30)
              {
                  LCDPutStr(".",43,time,LARGE,WHITE,BLACK);
              }
              else if(a<31)
              {
                  LCDPutStr(".",38,time,LARGE,WHITE,BLACK);
              }
              else if(a<32)
              {
                  LCDPutStr(".",33,time,LARGE,WHITE,BLACK);
              }
              else if(a<33)
              {
                  LCDPutStr(".",28,time,LARGE,WHITE,BLACK);
              }
              else if(a<34)
              {
                  LCDPutStr(".",23,time,LARGE,WHITE,BLACK);
              }
              else if(a<35)
              {
                  LCDPutStr(".",18,time,LARGE,WHITE,BLACK);
              }
              else if(a<36)
              {
                  LCDPutStr(".",13,time,LARGE,WHITE,BLACK);
              }
              else if(a<37)
              {
                  LCDPutStr(".",8,time,LARGE,WHITE,BLACK);
              }
              else if(a<38)
              {
                  LCDPutStr(".",3,time,LARGE,WHITE,BLACK);
              }
              time=time+5;
          }else 
          {     
                LCDPutStr("                       ",0,25,LARGE,WHITE,BLACK);
                LCDPutStr("                       ",15,25,LARGE,WHITE,BLACK);
                LCDPutStr("                       ",30,25,LARGE,WHITE,BLACK);
                LCDPutStr("                       ",45,25,LARGE,WHITE,BLACK);
                LCDPutStr("                       ",60,25,LARGE,WHITE,BLACK);
                LCDPutStr("                       ",75,25,LARGE,WHITE,BLACK);
                LCDPutStr("                       ",90,25,LARGE,WHITE,BLACK);
                time = 25;
          }


          free(outstr);
          if((PIOB_PDSR & SW_1) == 0)
          {        
              PIOB_CODR|= LCD_BACKLIGHT;

          }
		}
    }
    return 0;
}