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
String waitForString(){ 
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