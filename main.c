//main.c
#include <SI_EFM8BB1_Register_Enums.h>
void InitDevice(void)
{
//Disable Watchdog Timer with key sequence
WDTCN = 0xDE; //First key
WDTCN = 0xAD; //Second key

//Setup Defaults for P1
P1MDOUT = P1MDOUT_B0__OPEN_DRAIN | P1MDOUT_B1__OPEN_DRAIN
| P1MDOUT_B2__OPEN_DRAIN | P1MDOUT_B3__OPEN_DRAIN
| P1MDOUT_B4__PUSH_PULL | P1MDOUT_B5__OPEN_DRAIN
| P1MDOUT_B6__OPEN_DRAIN | P1MDOUT_B7__OPEN_DRAIN;
//Enable Weak Pullups
XBR2 = XBR2_WEAKPUD__PULL_UPS_ENABLED | XBR2_XBARE__ENABLED;
//Disable Interrupts
IE = IE_EA__DISABLED | IE_EX0__DISABLED | IE_EX1__DISABLED
| IE_ESPI0__DISABLED | IE_ET0__DISABLED | IE_ET1__DISABLED
| IE_ET2__ENABLED | IE_ES0__DISABLED;
}
void delayMs(unsigned char i){ // takes what number we put when it gets called from void 0- 255
	char c = 0;
	while(c < i){	// starts looping this timer delay by as many times as we need it
		TMOD = 0x01;//sets timer to 16b modeS
		TH0 = 0xCE;	// for 50ms delay
		TL0 = 0x1D;// for 50ms delay
		TCON |= (1 << 4); // tells the timer to run by setting TR0 to on
		while(!(TCON & 0x20));//checks the state of the overflow flag when it is true but once it gets set it evalutes to false and gets out
		TCON &= ~(1 << 4); //sets TR0 to stop timer
		TCON &= ~(1 << 5); // resets overflow flag to zero
		c++;//increments the loop for while so that we can get a 1000ms delay
		}
	}

main(void){
	unsigned char w;
	unsigned char var = 0x01;
	InitDevice();
	
		while(1){
			for(w=0;w<7;w++){
				if(P0 & (1<<1) && P0 & (1<<2)){// both buttons have to be true if one button is false meaning pushed this statement fails
					P1 = ~var;// invert var to get it to one light on and all off zero turns on leds 1 tunrs off
					delayMs(20);//multipy 50ms delay by 20 to get 1000ms delay becaue we can loop it 20 times in the timer
					var = var << 1; // shift it by 1 to the left 
					P1 = var; // assign to port P1
				}else if(P0&(1<<2)){//condition true if external button is pressed becauase P0.2 is 1 and P0.1 is zero
					P1 = var; // when external button pressed inverts the pattern meaning all on one off
					delayMs(20); // with a 1 second delay
					var = var << 1;
					P1 = var;
				}else if(P0&(1<<1)){//condition true if interal button is pressed P0.2 = 0 and P0.1 = 1
					P1 = ~var; // has same pattern as default which is the if statement
					delayMs(10);//multiply delay by 10 to get a 500ms delay
					var = var << 1;
					P1 = var;
				}else{// when both buttons pressed has inverted pattern and speeds it up
					P1 = var;
					delayMs(10);
					var = var << 1;
					P1 = var;
				}
			}
			for(w=0;w<7;w++){// this does same as top accept everything is shifting to right now this keeps repeating becuase of whie(1)
				if(P0 & (1<<1) && P0 & (1<<2)){
					P1 = ~var;
					delayMs(20);
					var = var >> 1;
					P1 = var;
				}else if(P0&(1<<2)){
					P1 = var;
					delayMs(20);
					var = var >> 1;
					P1 = var;
				}else if(P0&(1<<1)){
					P1 = ~var;
					delayMs(10);
					var = var >> 1;
					P1 = var;
				}else{
					P1 = var;
					delayMs(10);
					var = var >> 1;
					P1 = var;
					}
				}
			}
		}
