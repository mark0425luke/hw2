
#include "mbed.h"

DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
#define Switch_enable 0

Serial pc( USBTX, USBRX);
AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

char table[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x80};//最後0x80是只有那個點
int sample = 1000;
float ADCdata[5000];

int main()
{

	//calculate frequency
	//////////////////////////////////////////////////////////

	int numbers[3];
	int freq=0;
	
	for (int i = 0; i < 5*sample; i++)
	{
	  
	  ADCdata[i] = Ain;
	  wait(1./sample);
	}
	
	for (int i = 0; i < 5*sample; i++)
	{
	  if(ADCdata[i-1]<0.01 && ADCdata[i]>0.01)
	  {
	    //pc.printf("%d   ", i);
	    //pc.printf("%1.5f\r\n", ADCdata[i]);
	    freq++;
	  }
	  
	  //pc.printf("%1.5f\r\n", ADCdata[i]); //here I take this line out, just for demo, otherwise it will take some time
	  //wait(0.001);
	}
	//q = q*0.99;
	
	freq=freq/5;
	//pc.printf("%d\r\n", q/5);
	for(int i=2;i>=0;i--)
	{
		numbers[i]=freq%10;
		freq=freq/10;
	}
	
	
	//////////////////////////////////////////////////////////

	


	//switch button
	//////////////////////////////////////////////////////////
	while(1)
	{
		Aout = Ain;
		if(Switch==0)
		{
			redLED = 0;
			greenLED = 1;
			//display=table[10];

			
			int convert;
			for(int i=0;i<2;i++)//先搞定前3位數
			{
				
				convert=numbers[i];
				switch(convert)
				{
					case 0:	
						display=table[0];//actually don't need switch, just need display=table[convert]
						break;
					case 1:	
						display=table[1];
						break;
					case 2:	
						display=table[2];
						break;
					case 3:	
						display=table[3];
						break;
					case 4:	
						display=table[4];
						break;
					case 5:	
						display=table[5];
						break;
					case 6:	
						display=table[6];
						break;
					case 7:	
						display=table[7];
						break;
					case 8:	
						display=table[8];
						break;
					case 9:	
						display=table[9];
						break;
					default:
						display=table[0];
						break;	
				}
				wait(1);				
			}

			switch(convert)
			{
				case 0:	
					display=(table[0])+(table[10]);
					break;
				case 1:	
					display=(table[1]+table[10]);
					break;
				case 2:	
					display=(table[2]+table[10]);
					break;
				case 3:	
					display=(table[3]+table[10]);
					break;
				case 4:	
					display=(table[4]+table[10]);
					break;
				case 5:	
					display=(table[5]+table[10]);
					break;
				case 6:	
					display=(table[6]+table[10]);
					break;
				case 7:	
					display=(table[7]+table[10]);
					break;
				case 8:	
					display=(table[8]+table[10]);
					break;
				case 9:	
					display=(table[9]+table[10]);
					break;
				default:
					display=(table[10]);
					break;	
			}
			wait(1);
			
		}

		else
		{
			redLED = 1;
			greenLED = 0;
			display=0;
			
		}
	}
	//////////////////////////////////////////////////////////


}



