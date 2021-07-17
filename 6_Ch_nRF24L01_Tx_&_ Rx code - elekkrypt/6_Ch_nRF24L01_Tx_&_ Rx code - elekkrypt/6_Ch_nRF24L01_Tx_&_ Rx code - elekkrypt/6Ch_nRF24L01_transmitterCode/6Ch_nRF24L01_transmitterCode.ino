/*
 * This is a 6 channel nrf24l01 transmitter and receiver code.
 * There are 6 outputs in the transmitter end, of which 2 inputs are for pushbutton and the remaining 4 inputs are for 2 joystick modules which controls the led in the receiver.
 * 
 * To know more refer the below links:
 *  https://youtu.be/Pd7rus79j_4
 *  https://dhirajkushwaha.com/elekkrypt
 *  
 */

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// declaring where the toggle switches are connected in Arduino
int toggleSwitch01pin = 3;
int toggleSwitch02pin = 4;

// declaring where the leftHandside joystick is connected
int joystickLeft_VRxPin = A0;
int joystickLeft_VRyPin = A1;

// declaring where the rightHandside joystick is connected
int joystickRight_VRxPin = A2;
int joystickRight_VRyPin = A3;

RF24 radio(7,8);
const byte address[] = "node1";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();

  pinMode(toggleSwitch01pin, INPUT);
  pinMode(toggleSwitch02pin, INPUT);

}

struct datapack{
  bool toggleSwitch01 ;
  bool toggleSwitch02 ;
  
  int joystickLeft_x ;
  int joystickLeft_y ;

  int joystickRight_x ;
  int joystickRight_y ;  
};
datapack data;

void loop() {
  data.toggleSwitch01 = digitalRead(toggleSwitch01pin);
  data.toggleSwitch02 = digitalRead(toggleSwitch02pin);

  data.joystickLeft_x = map(analogRead(joystickLeft_VRxPin), 0, 1023,0,255);
  data.joystickLeft_y = map(analogRead(joystickLeft_VRyPin), 0, 1023,0,255);

  data.joystickRight_x = map(analogRead(joystickRight_VRxPin) , 0, 1023,0,255); 
  data.joystickRight_y = map(analogRead(joystickRight_VRyPin) , 0, 1023,0,255);
  
  radio.write(&data, sizeof(data));
}
