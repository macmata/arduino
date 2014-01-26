/*
  Arduino TFT text example
  
  This example demonstrates how to draw text on the 
  TFT with an Arduino. The Arduino reads the value 
  of an analog sensor attached to pin A0, and writes 
  the value to the LCD screen, updating every
  quarter second.
  
  This example code is in the public domain

  Created 15 April 2013 by Scott Fitzgerald
 
  http://arduino.cc/en/Tutorial/TFTDisplayText
 
 */

#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <Wire.h>

// pin definition for the Uno
#define cs   10
#define dc   9
#define rst  8  

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);


void setup() {
  Wire.begin(0x04);
  Wire.onReceive(receiveEvent); // register event
  TFTscreen.begin();
  Serial.begin(9600);
  
  
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);
  
  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255,255,255);
  // set the font size
  TFTscreen.setTextSize(2);
  // write the text to the top left corner of the screen
  TFTscreen.text("Test :\n ",0,0);
  // ste the font size very large for the loop
  TFTscreen.setTextSize(1);
}

void loop() {
  String fromCom = getString();
  Serial.print(fromCom);
  char charArray[100];
  
  fromCom.toCharArray(charArray,100);
  
  TFTscreen.stroke(255,255,255);
  TFTscreen.text(charArray, 0, 20);
  
  delay(1000);
  
  TFTscreen.stroke(0,0,0);
  TFTscreen.text(charArray, 0, 20);
  
}
String getString(){ 
        String inData = "";
        bool quit = false;
        while(quit !=true){
           while (Serial.available() > 0){
            char recieved = Serial.read();
                if (recieved == '\n'){
                    quit = true;
                }else{
                  inData += recieved; 
                }
            }
        }
        return inData;     
}
void receiveEvent(int howMany)
{
  while(0 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  //int x = Wire.read();    // receive byte as an integer
  //Serial.println(x);         // print the integer
}
