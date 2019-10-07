/*
 * core.cpp
 *
 *  Created on: 26 de mar de 2017
 *      Author: educampos
 */

#include "avr_config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2CSLAVE.h"
//#include "Usart.hrt.hw...................er.hUsart........h" // deve usar a opção -std=gnu++11
#include "Usart.h"

//LED PB5. Pino 13 no arduino uno
//SDA PC4. Pino AD4 no arduino uno
//SCL PC5. pino AD5 no arduino uno


#define Adrress 0x08

uint8_t status=0xFF;
uint8_t coord[] = {};
uint8_t a = 0;

ISR(TWI_vect)
{

//	status = TWSR;
	Slave_CallBack();
}

// This function define how to deal with the information received from the master
void I2C_recv()
{	
	/*
	std::vector<uint8_t> coord;
	coord.push_back(1);
	USART.write(coord[8]);
	*/
	uint8_t val = TWDR;
	uint8_t *valor = &val;
	
	USART.writeByte(*valor);
	
	if(*valor == 1){
		USART.write("\n");
	}
	else{
		USART.write(" ");
	}	
	
	/*
	USART.write(">");
	USART.write(TWDR);
	USART.write("\n\r");	
	*/
}

void I2C_Request()
{

	static uint8_t contador=0;
	TWDR=contador;
	contador++;

}


void setup() {



	I2C_Slave.attach_Receive(I2C_recv);
	I2C_Slave.attach_Request(I2C_Request);
	I2C_Slave.Open(Adrress);

	// initialize serial communication
	USART.begin(57600);
	sei(); //interrupt enable

}


void loop() {

//	if (status != 0xFF)
//	{
//	USART.write("=");
//	USART.write(status);
//	USART.write("\n\r");
//	status=0xff;
//	}

}



int main(void)
{
	setup();

	for (;;)
		loop();

	return 0;
}





