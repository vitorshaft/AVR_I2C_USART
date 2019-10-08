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
#define TWACK (TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA))

uint8_t status=0xFF;
uint8_t coord[8] = {};
int i = 0;

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
	
	lista = [1,2,3,4]
	lista.append(valor)
	*/
	//char val[15] = TWDR;
	/*
	
	USART.writeByte(*valor);
	
	if(*valor == 1){
		USART.write("\n");
	}
	else{
		USART.write(" ");
	}	
	
	for(int i=0;i<8;i++){
		USART
	}*/
	/*
	for(int i=0;i<15;i++){
		coord[i] = TWDR;
		USART.write(coord[i]);
		USART.write("\n\r");
	}
	*/
	/*
	if(TWDR == 1){
		USART.write(coord[0]);
		USART.write("\n\r");
		USART.write(coord[1]);
		USART.write("\n\r");
		USART.write(coord[2]);
		USART.write("\n\r");
		USART.write(coord[3]);
		USART.write("\n\r");
		i=0;
	}
	
	else{
		coord[i] = TWDR;
		USART.write(i);
		USART.write("\n\r");		
		i+=1;
	}
	*/
	
	//USART.write(">");
	//USART.write(TWD0);
	//USART.write("\n\r");
	/*
	while(!TWCR){
		coord[i] = TWDR;
		i++;
	}
	*/
	if(TWSR == 0x80){
		coord[i] = TWDR;
		USART.write(i);
		USART.write(": ");
		USART.write(coord[i]);
		USART.write("\n\r");
		i++;
		//Quando o i extrapola o limite da array ele para de atualizar coord[]
		//A transmissao via USART esta comecando em i = 1 e nao i = 0
	}
	else{
		i=0;
	}
	
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





