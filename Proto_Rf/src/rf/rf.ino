/*
 Copyright (C) 2013 Alexandre Leblanc info@alexandre-leblanc.com

This arduino application was inspired from the work of J. Coliz <maniacbug@ymail.com>. 
You can find is work in gitub.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(8,9);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

typedef enum { role_ping_out = 1, role_pong_back } role_e;

role_e role;

void setup(void){


  Serial.begin(57600);
  printf_begin();
  radio.begin();
  radio.setRetries(15,15);
  radio.setPayloadSize(8);
  radio.printDetails();
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
        printf("modeMaster\n");
        modeMaster();
      }
      else if(role == role_pong_back) {
        printf("modeSlave\n");
        modeSlave();
      }
    
      opt ="";
    }while(quit!=true);
}

void changeMode(void){
    String mode = "";
    printf("Selection du mode\n");
    printf("Choisir le mode de transmision T ou R ");
      

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

                status = radio.write( &s, sizeof(char));
                
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
//test
