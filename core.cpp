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
//#include "Usart.hrt.hw...................er.hUsart........h" // deve usar a op��o -std=gnu++11
#include "Usart.h"

//LED PB5. Pino 13 no arduino uno
//SDA PC4. Pino AD4 no arduino uno
//SCL PC5. pino AD5 no arduino uno


#define Adrress 0x08
#define BUFF_SIZE 16 
#define DIVISOR 16
//#define TWACK (TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA))

uint8_t status=0xFF;
uint8_t coord[BUFF_SIZE] = {};
int ind = 0;
int soma;

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
		coord[ind] = TWDR;		//Armazena byte na posicao ind (variando de 0 a 15)
		ind++;					//Incrementa ind
		if(ind == BUFF_SIZE) {			//Se ap�s incrementar, ind = 16:
			
			for(int a=0;a<15;a++){	//Soma os elementos de coord[0:14]
				soma+=coord[a];
			}
			ind = 0;			//Reinicia ind			
		}
	//}
	int resultado = soma%DIVISOR;//Resultado eh o resto da divisao soma/divisor
	if(resultado == coord[15]){	//Se o resultado for o ultimo byte (coord[16]):
		for(int i=0;i < 15;i++){
			USART.write(coord[i]);//Envia elementos de coord separados por linha via USART
			USART.write("\n");
		}
	}
	else{						//Se o resultado for diferente do ultimo byte:
		coord[BUFF_SIZE] = {};		//Zera o array
		USART.write("ERRO DE CHECKSUM!\n");//Envia na USART a msg de erro
		USART.write(resultado);		//Envia resultado do checksum
		USART.write(" != ");
		USART.write(coord[15]);		
		USART.write("\n");			//pula linha
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





