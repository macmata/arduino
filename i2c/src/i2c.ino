
#include <Wire.h>

void setup() {
  Wire.begin(0x04);
  Wire.onReceive(receiveEvent); // register event

}

void loop() {
  
  
}

void receiveEvent(int howMany)
{
  while(0 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
}
//twst