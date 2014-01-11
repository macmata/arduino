String getStringBuffer(){ 
    String inData = "";
     char recieved = 1;
     if(Serial.available()){
         while(true){
            if(Serial.available()){
                recieved = Serial.read();
                if (recieved == '\n'){
                    return inData;
                }else{
                  inData += recieved; 
                }
            }
        }     
    }  
}

String getString(){ 
    String inData = "";
    char recieved = 1;
    while(true){
        if(Serial.available()){
            recieved = Serial.read();
            if (recieved == '\n'){
                return inData;
            }else{
              inData += recieved; 
            }
        }
    }   
}