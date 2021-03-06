/***************************************************
  This sketch shows how to remote control wearable LEDs using text messages.

  I've used the Adafruit Feather FONA. It has  with GSM capabilities and is able to receive and decode SMS.

  A chain of individually adressable WS2801 LEDs is controlled by the Adafruit Feather and the Adafruit WS2801 library.

  This code is under A Creative Commons Attribution/Share-Alike License http://creativecommons.org/licenses/by-sa/4.0/
   (2017) by Imanol Gomez

/****************************************************


 ///////////////////////How to wire things up:///////////////////////

 
-----------------Connection to the LEDs:--------------------------

- We use 12mm Diffused Thin Digital RGB LED Pixels (Strand of 25) - WS2801.
- The pixels are connected by a 4-conductor cable. +5V (Red), Ground (Blue), Data (Yellow) and Clock (Green). 
- At 5 volts, they draw a maximum of 60 milliamps per pixel: 20 mA each for red, green and blue..
- 5V/2A supply should be able to drive 2 or more strands

// LED strand GND/0V/-      <----> Adafruit Feather GND 
// LED strand 5V/+          <----> Adafruit Feather USB output  
// LED strand MOSI/Data in  <----> Adafruit Feather SPI MOSI (GPIO #13)
// LED strand SCLK/Clock    <----> Adafruit Feather SPI SCK  (GPIO #14) 
*/


#include "FonaModule.h"
#include "LedsManager.h"
#include "ReceiveHandler.h"
#include "TimerManager.h"

#define LED_PIN  13


FonaModule fonaModule;
LedsManager leds;
ReceiveHandler receiver(&leds);
TimerManager timer(&leds);


void setup() {

  //while (!Serial); //It get's stuck if not connected to a computer
  
  Serial.begin(115200);
   
   // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  for(int i=0; i<3; i++){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(200); 
  }

  leds.setup();
  fonaModule.setup();
  receiver.setup();
  timer.setup();
}


void loop() {

  leds.update();
  fonaModule.update();
    
  if(fonaModule.isNewMessage()){
      timer.reset();
      Serial.print("NEW MESSAGE RECEIVED: "); Serial.println(fonaModule.getCurrentMessage());
      receiver.parseMessage(fonaModule.getCurrentMessage());   
  }

  timer.update();

}
