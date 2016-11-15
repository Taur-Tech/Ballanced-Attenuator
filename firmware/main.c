/*  Copyright 2016 Stefan Andrei Chelariu

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include<p18f1320.h>
#include<delays.h>
//Function Prototypes
void Init(void);
int ADC(int channel);

void main(void)
{
	int GND_FLOAT_VAL;
	int H_VALUE;
	int C_VALUE;
	int MEAN_VALUE;
	int i;
	Init();
	MEAN_VALUE =0;
	i =0;
	while(1)
	{
		GND_FLOAT_VAL=ADC(0);
		H_VALUE=ADC(1);
		if(H_VALUE >= GND_FLOAT_VAL)
			H_VALUE=H_VALUE - GND_FLOAT_VAL;
		else if(H_VALUE < GND_FLOAT_VAL)
			H_VALUE=GND_FLOAT_VAL-H_VALUE;
//		C_VALUE=ADC(1);
//		if(C_VALUE >= GND_FLOAT_VAL)
//			C_VALUE=C_VALUE - GND_FLOAT_VAL;
//		else if(C_VALUE < GND_FLOAT_VAL)
//			C_VALUE=GND_FLOAT_VAL-C_VALUE;
//		MEAN_VALUE=MEAN_VALUE+H_VALUE;
//		if(i==999)
//			{
//				MEAN_VALUE=MEAN_VALUE/1000;
//				CCPR1L=MEAN_VALUE;
//				MEAN_VALUE=0;
//				i=0;
//			}
		if(H_VALUE>MEAN_VALUE)
			MEAN_VALUE=H_VALUE;
		if(i==999)
			{
				MEAN_VALUE=MEAN_VALUE/1.41;
				CCPR1L=MEAN_VALUE;
				MEAN_VALUE=0;
				i=0;
			}		
		i++;

	
	}
}

void Init(void)
{
	TRISBbits.TRISB2 = 0;
	//ADC Setup
	TRISAbits.TRISA0 = 1;
	TRISAbits.TRISA1 = 1;
	TRISAbits.TRISA2 = 1;
	ADCON0 = 0b00000000;	
	ADCON1 = 0b11111000;
	ADCON2 = 0b00011010;
	//PWM Setup
	TRISBbits.TRISB3 = 0;
	PR2 = 0b10011011 ;
	CCPR1L = 0b00000000 ;
	T2CON = 0b00000111 ;
	CCP1CON = 0b00111100 ;


	
}	
int ADC(int channel)
{
	switch(channel)
	{
		case 0:  ADCON0 = 0b00000011; break;
		case 1:  ADCON0 = 0b00000111; break;
		case 2:  ADCON0 = 0b00001011; break;
		default:  ADCON0 = 0b00000011;break;
	}

	while(ADCON0bits.GO_DONE==1);
	return ADRESH;
}	