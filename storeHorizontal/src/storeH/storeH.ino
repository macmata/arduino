#include <Servo.h> 
#include <Wire.h>
const int OPEN  = 0;
const int wait  = 1000;
int cl  = 180;
int tempsValue = 0;
String strTmp = "";
int intTmp = 0;
Servo myservo;  

int pushButton = 13;
int powerPin = 12;
int gndPin = 11;

int state; 
int buttonState;
int interupteur;

void setup(){ 
  
  Wire.begin(0x04);
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
 
  
  pinMode(pushButton, INPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  digitalWrite(gndPin, LOW);
} 
 
 
void loop(){ 
  
  String string = getString();
  
  if (string.length() > 0){
    Serial.print("string : ");
    Serial.println(string);
    cl = atoi(string.c_str());
  }
  
  
  if (intTmp > 0){
      Serial.print("value : ");
      Serial.println(intTmp);
      cl = intTmp;
      intTmp = 0;  
  }

  
  int buttonState = digitalRead(pushButton);
  
  if(buttonState == HIGH){
    
    Serial.println(digitalRead(pushButton));
    buttonState = digitalRead(pushButton);
    
    if(buttonState == LOW){// on release
    
      Serial.println(digitalRead(pushButton));
      myservo.attach(8);
  
        if(myservo.read() > 90){   // si t'est bugger ouvre  
           
              myservo.write(OPEN);
              delay(wait);
              state = OPEN;
              myservo.detach();
          
            
        }else{
    
            myservo.write(cl);
            delay(wait);
            state = cl;
            myservo.detach();
        }
    }
  }  
}


String getString(){ 
        String inData = "";
        bool quit = false;
        
         if (Serial.available() > 0 ){
           while(quit !=true){
  
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

void receiveEvent(int howMany){
    String inData = "";
    int c = 0;
    while(0 < Wire.available()) {
      c = Wire.read(); // receive byte as a character
      Serial.println(c);
      
    }
    intTmp = c;
}
//test