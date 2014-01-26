#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <TFT.h>  // Arduino LCD library
/*
GND	 G
3V3	 3V3	 
CE	 6	 chip enable 
CSN	 7	 chip select
SCK	 13	 
MOSI 11  (SDA)
MISO 12	
*/
RF24 radio(6,7);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

typedef enum { role_ping_out = 1, role_pong_back } role_e;

role_e role = role_pong_back;


/*
// pin definition for the Uno
#define cs   2
#define dc   9   (A0) 
#define rst  8  
*/



// create an instance of the library
TFT TFTscreen = TFT(4, 9, 8);

void setup (void) {

	 Serial.begin(57600);
  	printf_begin();
  	radio.begin();
  	radio.setRetries(15,15);
  	radio.setPayloadSize(8);
  	radio.printDetails();
    TFTscreen.begin();

    // clear the screen with a black background
    TFTscreen.background(0, 0, 0);
  
    // write the static text to the screen
    // set the font color to white
    TFTscreen.stroke(255,255,255);
    // set the font size
    TFTscreen.setTextSize(2);
    // write the text to the top left corner of the screen
    TFTscreen.text("Initialisation faite :\n ",0,0);

    TFTscreen.stroke(0,0,0);
    TFTscreen.text("Initialisation faite :\n ",0,0);
    
    
}

void loop(void){
    String opt; 
    bool quit = false;
    Serial.println("SVP faite un choix d'action");
    do{

    opt = getString(); 
     
      if(opt.equalsIgnoreCase("mode")){
            changeMode();
            opt = "";
      }

      if(role == role_ping_out  ){
        
        TFTscreen.stroke(255,255,255);
        TFTscreen.setTextSize(2);
        TFTscreen.text("Mode master :\n ",0,0);
        delay(10);
        TFTscreen.stroke(0,0,0);
        TFTscreen.text("Mode master :\n ",0,0);
        radio.printDetails();
        modeMaster();
      }
      else if(role == role_pong_back) {

        TFTscreen.stroke(255,255,255);
        TFTscreen.setTextSize(2);
        TFTscreen.text("Mode slave :\n ",0,0);
        delay(10);
        TFTscreen.stroke(0,0,0);
        TFTscreen.text("Mode slave :\n ",0,0);
        radio.printDetails();
        modeSlave();
      }
    
      opt ="";
      Serial.println("SVP faite un choix d'action");
    }while(quit!=true);
}

void changeMode(void){
    String mode = "";
    printf("Selection du mode\n");
    printf("Choisir le mode de transmision T ou R \n");
      

            mode = getString(); 
            mode.trim();
            if ( mode.equalsIgnoreCase("T")){
              role = role_ping_out;
              radio.openWritingPipe(pipes[0]);
              radio.openReadingPipe(1,pipes[1]);
              printf("mode transmision choisi\n");
            }
            else if ( mode.equalsIgnoreCase("R") ){
              role = role_pong_back;
              radio.openWritingPipe(pipes[1]);
              radio.openReadingPipe(1,pipes[0]);
              printf("mode reception choisi\n");
            }
}


void modeMaster(){
           
            Serial.println("Entre un msg a envoyer");
            String msg = getString();
            sendRadioString(msg);
}

bool sendRadioString(String string){
    radio.stopListening();  
    
    bool status;

            for (int i = 0; i<string.length(); i++){
                
                char s = string.charAt(i);
                Serial.print("caractere:");
                Serial.print(s);
                disableDevice2();
                status = radio.write( &s, sizeof(char));
                Serial.println(status);
                if (status){
                    printf(" ok...\n");
                }else{
                    printf(" failed.\n\r");   
                }
                delay(100);
            }
            char c = '\n';
            status = radio.write( &c, sizeof(char));
                
            if (status){
                printf(" ok...\n");
            }else{
                printf(" failed.\n\r");   
            }
    
}

void modeSlave(){
    
    bool quit = false;
    String string = "";
     
    radio.startListening();
    while (quit != true){

        delay(100);
               
        while ( radio.available()>0 ){
            char d;
            bool done = false;
            while (!done){
               disableDevice2();
              done = radio.read( &d, sizeof(char) );

                if (d=='\n'){
                    Serial.println(string);
                    quit = true;
                }else{
                   string += d;
                }
            }
        }
    }
}

String getString(){ 
        String inData = "";
        bool quit = false;
        while(quit == false){
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
void disableDevice2(void){
                pinMode(4,OUTPUT);
                digitalWrite(4,HIGH);
                pinMode(6,INPUT);
                digitalWrite(6,LOW);

}