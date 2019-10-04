/*
 * I2C.h
 *
 *  Created on: 28 de jul de 2018
 *      Author: educampos
 */

#ifndef SRC_I2CSLAVE_H_
#define SRC_I2CSLAVE_H_

#include <stdint.h>

#define TWCR_DEFAULT_SLAVE (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN)

class I2CSLAVE{
public:
	virtual ~I2CSLAVE();
	void I2C_stop(void);

	void Open(uint8_t Address);
	void (*Rec_Callback)();
	void (*Req_Callback)();
	void attach_Receive(void (*isr)());
	void attach_Request(void (*isr)());
};
extern I2CSLAVE I2C_Slave;


void Slave_CallBack(void);
#endif /* SRC_I2CSLAVE_H_ */
