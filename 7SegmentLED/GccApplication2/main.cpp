/*
 * GccApplication2.cpp
 *
 * Changed: 05/03/16 18:36:04
 * Author : Kaspar Siricenko
 * Number : B00076450
 */ 

// Video demonstration of the working example: https://www.youtube.com/watch?v=Rg77iY35Das


#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#define BTN_PIN PIND2   // button pin
#define LED_PIN PORTB5  // led pin
 
#define LED_DDRD 0xF8   // b1111 1000
#define LED_DDRB 0x07   // b0000 0111
 
#define	LED_a  PORTB0   // pin 7   on  Seven-SEG Display 
#define	LED_b  PORTD7   // pin 6   on  Seven-SEG Display 
#define	LED_c  PORTD4   // pin 4   on  Seven-SEG Display 
#define	LED_d  PORTD5	// pin 2   on  Seven-SEG Display 
#define	LED_e  PORTD6	// pin 1   on  Seven-SEG Display 
#define	LED_f  PORTB1	// pin 9   on  Seven-SEG Display 
#define	LED_g  PORTB2	// pin 10  on  Seven-SEG Display 
#define LED_DP PORTD3   // pin 5   on  Seven-SEG Display 

#define CLR_PORTD() clearPORTD()
#define CLR_PORTB() clearPORTB()
#define CLR_LED()	clearLED()
#define TEST_LED()	testLED()
#define SET_LED(n)	setLED(&n)
#define CHK_BTN(n)	checkButton(&n)


//Prototype
void clearPORTD();
void clearPORTB();
void clearLED();
void testLED();
void checkButton(uint8_t*);
void setLED(uint8_t*);


//Main thread
int main(void)
{
  //----SETUP STAGE
  
  //Setups I/O PINS
	DDRD &= ~(1<<BTN_PIN);
	DDRB |=	 (1<<LED_PIN);
	DDRD |= LED_DDRD;
	DDRB |= LED_DDRB;
  
  //Activates pull-up resistors
	PORTD |= (1<<BTN_PIN);	
  
  //Initializes counter for digits from 0 to 9
	uint8_t currentDigit = 0x00;	
  
  
  //----LOOP STAGE
  
	while (1) 
	{ 
	   //A test for the pin position
		//TEST_LED(); 
    
       //Sets LEDs to display digits
		SET_LED(currentDigit);
	   //Waits for the pressing a button and changes digit
		CHK_BTN(currentDigit);
	}
}



// Functions
void clearPORTD() {
	PORTD &= ~LED_DDRD;  //Clears screen for Port B
}

void clearPORTB() {
	PORTB &= ~LED_DDRB;  //Clears screen for Port D
}

//Clears SCREEN
void clearLED() {
	CLR_PORTD();
	CLR_PORTB();
}

//Waits for the pressing a button and changes digit
void checkButton(uint8_t* n) {
	while(1) {
		if((PIND & (1<<BTN_PIN))) {
  			_delay_ms(10);
  			if(!(PIND & (1<<BTN_PIN))) {
    			PORTB ^= (1<<LED_PIN);
    			(*n)++;
    			return;
  			}
		}
	}  
}

//A test for the pin position
void testLED() {
	const uint8_t aSize = 0x08;
	uint8_t a[aSize] = {LED_a, LED_b, LED_c, LED_d, LED_e, LED_f, LED_g, LED_DP};
	for(uint8_t i = 0; i < aSize; CHK_BTN(i)) {
		CLR_LED();
		if(a[i] == LED_a || a[i] == LED_f || a[i] == LED_g)
			PORTB |= (1<<a[i]);
		else
			PORTD |= (1<<a[i]);
	}
}

//Sets LEDs to display digits
void setLED(uint8_t *n) {
	uint8_t aSize = 0x08;
	uint8_t a[aSize];
	switch(*n) {
    
		case 1: /*BC*/
			aSize = 2;
			a[0] = LED_b;
			a[1] = LED_c;
			break;
		
		case 2: /*ABGED*/
			aSize = 5;
			a[0] = LED_a;
			a[1] = LED_b;
			a[2] = LED_g;
			a[3] = LED_e;
			a[4] = LED_d;
			break;
		
		case 3: /*ABGCD*/
			aSize = 5;
			a[0] = LED_a;
			a[1] = LED_b;
			a[2] = LED_g;
			a[3] = LED_c;
			a[4] = LED_d;
			break;
		
		case 4: /*FGBC*/
			aSize = 4;
			a[0] = LED_f;
			a[1] = LED_g;
			a[2] = LED_b;
			a[3] = LED_c;
			break;
		
		case 5: /*AFGCD*/
			aSize = 5;
			a[0] = LED_a;
			a[1] = LED_f;
			a[2] = LED_g;
			a[3] = LED_c;
			a[4] = LED_d;
			break;
		
		case 6: /*AFGCED*/
			aSize = 6;
			a[0] = LED_a;
			a[1] = LED_f;
			a[2] = LED_g;
			a[3] = LED_c;
			a[4] = LED_e;
			a[5] = LED_d;
			break;
		
		case 7: /*ABC*/
			aSize = 3;
			a[0] = LED_a;
			a[1] = LED_b;
			a[2] = LED_c;	
			break;
		
		case 8: /*ABCDEFG*/
			aSize = 7;
			a[0] = LED_a;
			a[1] = LED_b;
			a[2] = LED_c;
			a[3] = LED_d;
			a[4] = LED_e;
			a[5] = LED_f;
			a[6] = LED_g;
			break;
		
		case 9: /*ABCDFG*/
			aSize = 6;
			a[0] = LED_a;
			a[1] = LED_b;
			a[2] = LED_c;
			a[3] = LED_d;
			a[4] = LED_f;
			a[5] = LED_g;
			break;
		
		default: /*ABCDEF*/
    		aSize = 6;
    		a[0] = LED_b;
    		a[1] = LED_c;
    		a[2] = LED_d;
    		a[3] = LED_e;
    		a[4] = LED_a;
    		a[5] = LED_f;
        
			(*n) = 0;
			break;
	}
	
	CLR_LED(); 
  
	for (uint8_t i = 0; i < aSize; i++) {
		if(a[i] == LED_a || a[i] == LED_f || a[i] == LED_g)
			PORTB |= (1<<a[i]);
		else
			PORTD |= (1<<a[i]);
	}
}

// Old stuff from the previous labs..

		/*	else
				PORTB &= ~(1<<PORTB5);
										*/
		/*	PORTB |=  (1<<PORTB5);
			_delay_ms(100);
			PORTB &= ~(1<<PORTB5);
			_delay_ms(100);  */	
		
		/*
		else {
			PORTB |=  (1<<PORTB5);
			_delay_us(1);
			
			PORTB &= ~(1<<PORTB5);
			_delay_us(1);
		}
		*/
		//_delay_ms(50);