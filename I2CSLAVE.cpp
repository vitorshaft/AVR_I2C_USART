/*
 * I2C.cpp
 *
 *  Created on: 28 de jul de 2018
 *      Author: educampos
 */

#include <avr/interrupt.h>
#include "I2CSLAVE.h"
#include <util/twi.h>

I2CSLAVE I2C_Slave;              // preinstatiate

#ifdef SRC_I2CSLAVE_H_

#endif

void Slave_CallBack(void){

	switch(TW_STATUS)
	{
	//Slave Receiver mode-------------------------------------------------------
	case TW_SR_SLA_ACK: //SLA+W received, ACK returned
		TWCR = TWCR_DEFAULT_SLAVE;
		break;

//	case TW_SR_ARB_LOST_SLA_ACK:
//		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEN);
//		break;

	case TW_SR_DATA_ACK:
		// received data from master, call the receive callback
		I2C_Slave.Rec_Callback();
		TWCR = TWCR_DEFAULT_SLAVE;
		break;

	case TW_SR_STOP:
		TWCR = TWCR_DEFAULT_SLAVE;
		break;

	//Slave Transmitter Mode-------------------------------------------------------
	case TW_ST_SLA_ACK: //SLA+R received, ACK returned */
		I2C_Slave.Req_Callback();
		TWCR = TWCR_DEFAULT_SLAVE;
		break;
	case TW_ST_ARB_LOST_SLA_ACK:
	case TW_ST_DATA_ACK:
		// master is requesting data, call the request callback
		I2C_Slave.Req_Callback();
		TWCR = TWCR_DEFAULT_SLAVE;
		break;
	case TW_ST_DATA_NACK: // data transmitted, NACK received
		TWCR = TWCR_DEFAULT_SLAVE;
		break;

	//error------------------------------------------------------------------------
	case TW_BUS_ERROR:
		// some sort of erroneous state, prepare TWI to be readdressed
		TWCR = (1<<TWSTO);
		asm("nop");
		asm("nop");
		TWCR = TWCR_DEFAULT_SLAVE;
		break;
	default:
//		TWCR = TWCR_DEFAULT_SLAVE;
		break;
	}

}

void I2CSLAVE::Open(uint8_t Address){

	cli();

	// load address into TWI address register
	TWAR = Address << 1;

	// set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);

	sei();

}

void I2CSLAVE::attach_Receive(void (*isr)()){

	Rec_Callback = isr;

}
void I2CSLAVE::attach_Request(void (*isr)()){

	Req_Callback = isr;

}

void I2CSLAVE::I2C_stop(void)
{
  // clear acknowledge and enable bits
  cli();
  TWCR = 0;
  TWAR = 0;
  sei();
}

I2CSLAVE::~I2CSLAVE() {
	// TODO Auto-generated destructor stub
}