#include <Servo.h> 
#include <Wire.h>

const int OPEN  = 0;
const int WAIT  = 1000;

int wireValue  = 180;
int wireValueTmp = 0;

Servo myservo;  

int pushButton = 13;
int powerPin = 12;
int gndPin = 11;
int button1;

void setup(){ 
  
  Wire.begin(0x04);
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
  myservo.attach(8);
  
  pinMode(pushButton, INPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  digitalWrite(gndPin, LOW);
} 
 
 
void loop(){ 
  
    String string = getString();
    int button1 = digitalRead(pushButton);

  if (string.length() > 0){
    //Serial.print("string : ");
    //Serial.println(string);
    wireValue = atoi(string.c_str());
  }

  if (wireValueTmp > 0){
      //Serial.print("value : ");
      //Serial.println(wireValueTmp);
      wireValue = wireValueTmp;
      wireValueTmp = 0;  
  }

  if(button1 == HIGH){
      applyButton1Action(wireValue);
  }  
}


String getString(){ 
    String inData = "";
    bool quit = false;
     if (Serial.available() > 0 ){
       while(quit == false){

            if(Serial.available() > 0 ){
              
              char recieved = Serial.read();
              if (recieved == '\n'){
                return inData;
              }else{
                inData += recieved; 
              }
            }
        }
    }
    return inData;     
}



void applyButton1Action (int wireValue){

    int bt = digitalRead(pushButton);
    
    if(bt == LOW){// on release
  
        if(myservo.read() > 90){  
           
            setServo(OPEN);
                
        }else{
    
            setServo(wireValue);
        }
    }
}

void setServo(int degre){
    myservo.write(degre);
    delay(WAIT);
}
/*
*Set to receive int 
*/
void receiveEvent(int howMany){
    int c = 0;
    while(0 < Wire.available()) {
      c = Wire.read(); // receive byte as a character
      //Serial.println(c);
    }
    wireValueTmp = c;
}