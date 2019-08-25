/////////////////////////////////////////////////////////////////////////////////////////////////////
///  Project Name : 4
//
//  Target Board : atmega32
//
//  Date Created : 22-03-2018 22:11:29
// 
//  Online Resource  : www.electronicsforstudents.com
//
//  Libraries Included : -->wifiadvanced -->rgb 
/////////////////////////////////////////////////////////////////////////////////////////////////////
#define cloudid  "v36365"
#define INTERNET WIFI
#include<avr/io.h>
#include<util/delay.h>


#include "serial.h"
#include "adc.h"
#include "clobous.h"
#include "DS18B20.h"
#include "lcd.h"


int main()
{
	lcd_init();
	lcd_string("Home Automation ");
	serial_init(9600);
	serial_select(2);
	
	wifi_init();
	wifi_connect("kedar","kedar1234");
	lcd_clear();
	lcd_string("Home");
	rgb_init();
	rgb_setpin(portb,3);
	char lr[5],br[5],rgb[5];
	int i,a,b,c,d,x=0,y=0,z=0;
	char security[10],response[25];
	adc_init();
	ds18b_init(porta,1);
	while (1)
	{	
		{
			lcd_clear();
			lcd_string("Home S/A");

			data_retrieve("vr",br);	
			data_retrieve("vr",lr);
			data_retrieve("vr",rgb);
				if(compare(lr,"on1")==1)
					{	
						write(portb,7,h);
					}
				if(compare(lr,"off1")==1) 
					{	
						write(portb,7,l);
					}
					
				if(compare(rgb,"on2")==1)
				{	
					write(portb,2,h);
					for(i=0;i<8;i++)
					{	
						set_led(255,255,255,i);
					}
				}	
					
				if(	compare(rgb,"off2")==1)
				{	
					write(portb,2,l);
					for(i=0;i<8;i++)
					{	
						set_led(1,1,1,i);
					}
				}	
				if(compare(rgb,"red")==1)
				{
					for(i=0;i<8;i++)
					{	
						set_led(255,0,0,i);
					}
				}
				if(compare(rgb,"blue")==1)
				{
					for(i=0;i<8;i++)
					{	
						set_led(0,0,255,i);
					}
				}
				
				}
				if(compare(rgb,"green")==1)
				{
					for(i=0;i<8;i++)
					{	
						set_led(0,255,0,i);
					}
				}
				if(compare(rgb,"crimson")==1)
				{
					for(i=0;i<8;i++)
					{	
						set_led(220,20,60,i);
					}
				}
				if(compare(rgb,"yellow")==1)
				{
					for(i=0;i<8;i++)
					{	
						set_led(255,255,0,i);
					}
				}
				wifi_http("http://api.clobous.com/v36365/data/retrieve?security",response);
				jsonparser(response,"security",security);
				if(compare(security,"on")==1)
				{
					a=adc_read(0);
					lcd_clear();
					lcd_num(a);
					_delay_ms(1000);
					b=read_temp();
					lcd_clear();
					lcd_num(b);
					_delay_ms(1000);
					c=read(portb,5);
					lcd_clear();
					lcd_num(c);
					_delay_ms(1000);
					d=read(portb,6);
						if(a>400)
						{	
							x=x+1;
							if(x==1)
							{
								wifi_http("http://api.clobous.com/v36365/sendmsg/9632663099/gas leak detected");
							}	
						}
						if(x<400)
						{	
							x=0;
						}	
						if(b>70)
						{	
							y=y+1;
							if(y==1)
							{
								wifi_http("http://api.clobous.com/v36365/sendmsg/9632663099/fire  detected");
							}
						}
						if(b<70)
						{
							y=0;
						}	
						if((c==1)||(d==1))
						{
							z=z+1;
							if(z==1)
							{
								wifi_http("http://api.clobous.com/v36365/sendmsg/9632663099/intruder detected");
							}
						}
						if((c==0)&&(d==0))
						{
							z=0;
						}
				}		

}				
	
}