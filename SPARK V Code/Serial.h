#ifndef SERIAL
#define SERIAL
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


//UART0 initialisation
// desired baud rate: 9600
// actual: baud rate:9600 (0.0%)
// char size: 8 bit
// parity: Disabled
void uart0_init(void)
{
 UCSRB = 0x00; //disable while setting baud rate
 UCSRA = 0x00;
 UCSRC = 0x86;
 UBRRL = 0x2F; //set baud rate lo  //67 is for 16MHz 9600 baudrate
 UBRRH = 0x00; //set baud rate hi
 UCSRB = 0x98; 
}


//ADD THIS TO INIT DEVICES:
//void init_devices (void)
//{
// cli();         //Clears the global interrupts
// uart0_init();
// sei();         //Enables the global interrupts
//}
void uart_single(unsigned char data) {
	while (!( UCSRA & (1<<UDRE)));                // wait while register is free
    UDR = data;
}

void uart_transmit(unsigned char * data) {
	while (*data !=0) {
		while (!( UCSRA & (1<<UDRE)));                // wait while register is free
    	UDR = *data;
		data++;
	}
}
void uart_uint16(int16_t data16) {
	unsigned char buffer[20];
	itoa(data16, buffer, 10);
	uart_transmit(buffer);
}
//IMPLEMENT THIS IN MAIN FILE
void recv(unsigned char);
SIGNAL(SIG_UART_RECV) 
{
 unsigned char receive_data=0;   // used to save Receiving data

 receive_data = UDR;
 recv(receive_data);
//Handle Template:
 //if(receive_data == 'w')        //ASCII value of 8
 //{
//	forward();  
//	uart_transmit("Forward!\n");
// }

}

#endif

