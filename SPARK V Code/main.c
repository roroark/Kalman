#include "Serial.h"
//#include "I2C.h"
//#include "HMC5883L.h"
#include "Timer.h"
#include "PEM.h"
#include <avr/io.h>


int moving = 0;

void every_time() {
	//Set Some Pin High
	PORTC = PORTC | 0x01;
	_delay_us(100);
	PORTC = PORTC & 0xFE;
	_delay_us(10);
	//Send your own shit;

	uart_transmit("Readings\n");
	uart_transmit("PEL: ");
	uart_uint16(ShaftCountLeft);
	uart_transmit("\nPER: ");
	uart_uint16(ShaftCountRight);
	uart_transmit("\n");

}

void recv(unsigned char what) {
	//Serial In
}

void init_devices() {
	cli();
	uart0_init();
	//TWIInit();
	DDRC = DDRC | 0x01;
	PORTC = PORTC | 0x00;
	timer1_init();
	TIMSK = 0x04;
 	pem_port_init();
 	left_position_encoder_interrupt_init();
 	right_position_encoder_interrupt_init();
	sei();
}

int main() {
	init_devices();

		
	while(1)
	{
		uart_transmit("START\n");
		moving = 1;
		forward_mm(500);          //Moves robot forward 0.5m
		_delay_ms(500);
		soft_left_2_degrees(90);        //Rotate robot left by 90 degrees
		_delay_ms(500);

		forward_mm(500);          //Moves robot forward 0.5m
		_delay_ms(500);
		soft_left_2_degrees(90);        //Rotate robot left by 90 degrees
		_delay_ms(500);


		forward_mm(500);          //Moves robot forward 0.5m
		_delay_ms(500);
		soft_left_2_degrees(90);        //Rotate robot left by 90 degrees
		_delay_ms(500);

		
		forward_mm(500);          //Moves robot forward 0.5m
		_delay_ms(500);
		soft_left_2_degrees(90);        //Rotate robot left by 90 degrees
		_delay_ms(500);
		
		uart_transmit("END\n");
		break;	//Only do this once
	}
	return 0;
}
