const int m1 = 9;

#define TIME_DELAY 1       // # Time Delay in ms

void setup() {

 pinMode(m1,OUTPUT);
 Serial.begin(57600);           // # Keep baud rate same as in Controller.py
 pinMode(LED_BUILTIN,OUTPUT);   // Pin 13 or other, arudino IDE takes care of this itself

}

uint8_t val = 0x00;

void loop() {
 
  while(!Serial.available())digitalWrite(LED_BUILTIN,HIGH);  //# On if not receiving anything
  while(Serial.available()){                                 //#Off if data is incoming
  digitalWrite(LED_BUILTIN,LOW);
  int control_signal = (char(Serial.read()) & 0xFF)-1;
  Serial.println(control_signal);

  /*
   _____                        __  __                
  / ____|                      |  \/  |               
 | (___   ___  _ __ ___   ___  | \  / | ___  _ __ ___ 
  \___ \ / _ \| '_ ` _ \ / _ \ | |\/| |/ _ \| '__/ _ \
  ____) | (_) | | | | | |  __/ | |  | | (_) | | |  __/
 |_____/ \___/|_| |_| |_|\___| |_|  |_|\___/|_|  \___|
                                                      
  ____  _ _   __  __       _   _     
 |  _ \(_) | |  \/  |     | | | |    
 | |_) |_| |_| \  / | __ _| |_| |__  
 |  _ <| | __| |\/| |/ _` | __| '_ \ 
 | |_) | | |_| |  | | (_| | |_| | | |
 |____/|_|\__|_|  |_|\__,_|\__|_| |_| 
 
  */
  
  if(control_signal == 0x001){
    if(val < 255 ) val+=1;
    }
  else if(control_signal == 0x02){ 
    if (val < 0 ) val-=1;
    }
  else if(control_signal == 0x04){ 
    digitalWrite(m1,LOW);
    exit(0);
    }
    
  analogWrite(m1,val);
    // End of all conditions 
    
  delay(TIME_DELAY); 
  }  
}
