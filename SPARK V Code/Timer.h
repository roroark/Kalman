/********************************************************************************
 Platform: SPARK V
 Experiment: 3_Timer1_Overflow_Interrupt
 Written by: Vinod Desai, NEX Robotics Pvt. Ltd.
 Edited By: Sachitanand Malewar, NEX Robotics Pvt. Ltd.
 Last Modification: 22nd September 2010
 AVR Studio Version 4.17, Build 666
 
 Concepts covered: Use of timer overflow interrupt to do tasks in a peirodic way

 This experiment demonstrates use of timer overflow interrupt

 In this example timer 1's overflow interrupt is used to turn on and off Buzzer 
 with the time peirod of 1 second. The Buzzer is connected at PORTC3
 
 Note: 
 
 1. Make sure that in the configuration options following settings are 
 	done for proper operation of the code

 	Microcontroller: atmega16
 	Frequency: 7372800
 	Optimization: -O0 (For more information read section: Selecting proper 
	              optimization options below figure 4.22 in the hardware manual)

 2. TIMSK = 0x04; //timer1 overflow interrupt enable must be done in init devices. 
    It should not be done in timer1_init()

*********************************************************************************/
#ifndef TIMER
#define TIMER

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//TIMER1 initialize - prescale:1024
// WGM: 0) Normal, TOP=0xFFFF
// desired value: 1Hz
// actual value:  1.000Hz (0.0%)
void timer1_init(void)
{
 TCCR1B = 0x00; //stop
 TCNT1H = 0x00; //setup
 TCNT1L = 0x00;
 OCR1AH = 0x1C;
 OCR1AL = 0x1F;
 OCR1BH = 0x1C;
 OCR1BL = 0x1F;
 ICR1H  = 0x1C;
 ICR1L  = 0x1F;
 TCCR1A = 0x00;
 TCCR1B = 0x02; //start Timer
}
// Max Delay = 8.88ms
// Pre Scalar 8 : 0.0711s
// 71ms / 0.0711 = 1
int tcount = 0;
void every_time(void);
//This ISR can be used to toggle the buzzer input
ISR(TIMER1_OVF_vect)
{
 tcount++;
 if (tcount >= 2) {
	every_time();
	tcount = 0;
 }
} 

//void init_devices(void)
//{
 //cli();          //Clears the global interrupts
 //timer1_init();
// TIMSK = 0x04;   //timer1 interrupt sources
// sei();          //Enables the global interrupts
//}

#endif
