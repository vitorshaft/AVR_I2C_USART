///*
// * core.cpp
// *
// *  Created on: 26 de mar de 2017
// *      Author: educampos
// */
//
//
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include "I2CSLAVE.h"
//#include "Usart.h" // deve usar a opção -std=gnu++11
//
////LED PB5. Pino 13 no arduino uno
////SDA PC4. Pino AD4 no arduino uno
////SCL PC5. pino AD5 no arduino uno
//
//
//#define Adrress 0x08
//
//// This function define how to deal with the information received from the master
//void I2C_recv()
//{
//
//	USART.write(">");
//	USART.write(TWDR);
//	USART.write("\n\r");
//
//}
//
//
//void setup() {
//
//
//
//	I2C_Slave.attach_Receive(I2C_recv);
//	I2C_Slave.Open(Adrress);
//
//	// initialize serial communication
//	USART.begin(57600);
//	sei(); //interrupt enable
//
//}
//
//
//void loop() {
//}
//
//
//
//int main(void)
//{
//	setup();
//
//	for (;;)
//		loop();
//
//	return 0;
//}
//
//
//
//
//
