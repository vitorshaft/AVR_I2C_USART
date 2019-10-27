/*
 * core.cpp
 *
 *  Created on: 26 de mar de 2017
 *      Author: educampos
 *	Remixed on: 11 de out de 2019
 *		By: Ana Carolina Cabral, Joaquim Alves Jr,Vitor Domingues
 */

#include "avr_config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "I2CSLAVE.h"
//#include "Usart.hrt.hw...................er.hUsart........h" // deve usar a opção -std=gnu++11
#include "Usart.h"

#define Adrress 0x08
#define BUFF_SIZE 16 
#define DIVISOR 16

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
		coord[ind] = TWDR;		//Armazena byte na posicao ind (variando de 0 a 15)
		ind++;					//Incrementa ind
		soma+=coord[ind];
		int resultado;
		if(ind == BUFF_SIZE) {			//Se após incrementar, ind = 16:
			resultado = soma%DIVISOR;
			soma=0;
			ind = 0;			//Reinicia ind	
			if(resultado == coord[BUFF_SIZE-1]){	//Se o resultado for igual ao ultimo byte (coord[15]):
				for(int i=0;i < BUFF_SIZE-1;i++){
				USART.write(coord[i]);//Envia elementos de coord separados por linha via USART
				USART.write("\n");
				}
			}
			else{						//Se o resultado for diferente do ultimo byte:
				coord[BUFF_SIZE] = {};		//Zera o array
				USART.write("ERRO DE CHECKSUM!\n");//Envia na USART a msg de erro
				USART.write(resultado);		//Envia resultado do checksum
				USART.write(" != ");
				USART.write(coord[BUFF_SIZE-1]);		
				USART.write("\n");			//pula linha
				USART.write(soma);
				USART.write("\n");
				}						
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
	//Teste de sleep (25/10/19)
	
	set_sleep_mode(SLEEP_MODE_STANDBY);
    sei();
    sleep_mode();
	
	/*
	set_sleep_mode(SLEEP_MODE_STANDBY);
    sleep_enable();
    sei();
    sleep_cpu();
	*/
}



int main(void)
{
	setup();

	for (;;)
		loop();

	return 0;
}





