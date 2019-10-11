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
uint8_t coord[9] = {};
int ind = 0;
int soma;
int divisor = 15;

ISR(TWI_vect)
{

//	status = TWSR;
	Slave_CallBack();
}

// This function define how to deal with the information received from the master
void I2C_recv()
{	
	/*
	if(TWSR == 0x80){	//Configuracao do TWSR
		coord[ind] = TWDR;	//Armazena primeiro "caractere" no array coord[]
		USART.write(ind);
		USART.write(": ");
		USART.write(coord[ind]);
		USART.write("\n\r");
		ind++;
		//Quando o ind extrapola o limite da array ele para de atualizar coord[]
		//A transmissao via USART esta comecando em ind = 1 e nao i = 0
	}
	else{
		ind=0;
	}*/
	//for(int i=1;i<=8;i++){
		coord[ind] = TWDR;
		ind++;	
		if(ind == 9) {
			
			for(int a=0;a<8;a++){
				soma+=coord[a];
			}
			ind = 0;			
		}
	//}
	int resultado = soma%divisor;
	if(resultado == coord[8]){
		for(int i=0;i < 8;i++){
			USART.write(coord[i]);
			USART.write("\n");
		}
	}
	else{
		coord[9] = NULL;
		USART.write("DEU RUIM!\n");
		USART.write(resultado);
		USART.write("\n");
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





