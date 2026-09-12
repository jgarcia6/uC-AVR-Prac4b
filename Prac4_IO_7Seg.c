#include <avr/io.h>

#define SetBitPort(port, bit) __asm__ ( ?? )
#define ClrBitPort(port, bit) __asm__ ( ?? )

// Macros
#define INC_BUTTON PK0
#define DEC_BUTTON PK1
#define DISPLAY_PORT PORTL

typedef enum ButtonStates
{
    eBtnUndefined = 0,
    eBtnShortPressed = 1,
    eBtnLongPressed = 5
}Button_State_t;

extern void delay(uint16_t mseg); // To be defined in ASM (external .S file)
void InitPorts(void);
Button_State_t check_Btn(volatile uint8_t *pin_register, uint8_t pin_number);
void Display7Seg(uint8_t data);

int main(void)
{
	uint8_t count = 0;
	UCSR0B &= ~(1<<TXEN0); // Disable UART-TX

	InitPorts();
	
	while(1){
		count += check_Btn(&PINK, INC_BUTTON);
		count -= check_Btn(&PINK, DEC_BUTTON);
		Display7Seg(count & 0xF); // Only displaying the 4 LSB
		delay(1);
	}
}
