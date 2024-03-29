// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>
// changed by VSAT M2 Team <www.github.com/vitorshaft/AVR_I2C_USART>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Increased with checksum for 8-byte data

// Created 29 March 2006
// Changed 10 October 2019

// This example code is in the public domain.


#include <Wire.h>
int soma = 0;
int divisor = 16;
void setup() {
  //Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
}

int coord[16] = {8,3,15,1,34,52,53,1,15,46,48,1,47,55,45};
//08 03 15 S/034 52 53 W (Recife) 15 46 48 S/047 55 45 W (Brasilia)
//8,3,15,1,34,52,53,1,15,46,48,1,47,55,45,<8>checksum(424/16)
void loop() {
  soma = 0;
  for (int a=0;a<15;a++){
    //coord[a] = coord[a]+1;
    soma+=coord[a];
  };
  soma = soma%divisor;
  coord[15] = soma; //Insert checksum to the end of array
  Wire.beginTransmission(8); // transmit to device #8
  for (int i=0; i<16; i++){
    Wire.write(coord[i]);
    //Serial.println(coord[i]);
  };
  
  Wire.endTransmission();    // stop transmitting
  delay(5000);
}
