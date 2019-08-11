/////////////////////////////////////////////////////////////////////////////////////////////////////
///  Project Name : home_security
//
//  Target Board : atmega32
//
//  Date Created : 7/25/2017 11:46:05 AM
// 
//  Online Resource  : www.electronicsforstudents.com
//
//  Libraries Included : -->gsm 
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include<avr/io.h>
#include<util/delay.h>


#include "serial.h"
#include "lcd.h"


int main()
{
	serial_init(9600);
	serial_select(1);
	lcd_init();
	gsm_init();
	char msg[30],phone[11];
	int security_status;
	lcd_string("welcome to smart\nhome");

	while (1)
	{
		while(gsm_waitformsg()==0)
		{
			if(security_status==1)
			{
				if(read(portc,0)==1)			// read from sensor
				{
					write(porta,3,h);		// write high to buzzer
					_delay_ms(2000);
					write(porta,3,l);
				}
			}
		}
					
		
		gsm_readmsg(msg,phone);
		phone[10]='\0';
		lcd_clear();
		lcd_string(msg);
		lcd_gotoxy(0,1);
		lcd_string(phone);
		_delay_ms(3000);
		
		if(compare(phone,"9632663099")==1)
		{
			if(compare(msg,"security on")==1)
			{
				gsm_sendmsg("security activated","9632663099");
				security_status=1;
			}
			
			if(compare(msg,"security off")==1)
			{
				gsm_sendmsg("security deactivated","9632663099");
				security_status=0;
			}

		
		}
		else
		{
			char newstring[50];
			sprintf(newstring,"intruder alert: %s",phone);
			gsm_sendmsg(newstring,"9632663099");
		}
		
		
		


	}

}