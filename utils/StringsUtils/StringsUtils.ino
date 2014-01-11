String getString(){ 
        String inData = "";
        bool quit = false;
        
         if (Serial.available() > 0 ){
            if(Serial.available() > 0 ){
              char recieved = Serial.read();
              if (recieved == '\n'){
                return inData;
              }else{
                inData += recieved; 
              }
            }
        }
        return inData;     
}
String waitForString(){ 
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