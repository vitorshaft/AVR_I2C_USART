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
  Wire.begin(); // join i2c bus (address optional for master)
}
/*
byte lat[] = {8,3,15,1};  //08 03 15 S
byte lon[] = {34,52,53,1}; //034 52 53 W
*/
int coord[] = {8,3,15,1,34,52,53,1};  //08 03 15 S/034 52 53 W
//8,3,15,1,34,52,53,1,7(167/16)
void loop() {
  for (int a=0;a<8;a++){
    //coord[a] = coord[a]+1;
    soma+=coord[a];
  };
  soma = soma%divisor;
  coord[8] = soma;
  Wire.beginTransmission(8); // transmit to device #8
  for (int i=0; i<9; i++){
    Wire.write(coord[i]);
  };
  
  
  //Wire.write("x is ");        // sends five bytes
  /*String str = "abc";
  for(char& c : str) {
    Wire.write(c);
  };
  */
  //Wire.write(x);              // sends one byte
  //x++;
  //delay(500);
  //Wire.write(y);
  Wire.endTransmission();    // stop transmitting
  delay(500);
}
