const int a = 2;           // # connect different LEDs to pins 
const int b = 3;           // # Red
const int c = 6;           // # Green 
const int d = 7;           // # Blue 
#define TIME_DELAY 1       // # Time Delay in ms

void setup() {
 pinMode(a,OUTPUT);
 pinMode(b,OUTPUT);
 pinMode(c,OUTPUT);
 pinMode(d,OUTPUT);
 Serial.begin(57600);           // # Keep baud rate same as in Controller.py
 pinMode(LED_BUILTIN,OUTPUT);   // Pin 13 or other, arudino IDE takes care of this itself
}

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
  if((control_signal & 0x0C) ==      0x00){
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    }
  else if((control_signal & 0x0C) == 0x04){ // 0000 0100
    digitalWrite(a,HIGH);
    digitalWrite(b,LOW);
    }
  else if((control_signal & 0x0C) == 0x08){ // 0000 1000
    digitalWrite(a,LOW);
    digitalWrite(b,HIGH);
    }

    if((control_signal & 0x03) ==    0x00){
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    }
  else if((control_signal & 0x03) == 0x01){
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    }
  else if((control_signal & 0x03) == 0x02){
    digitalWrite(c,LOW);
    digitalWrite(d,HIGH);
    }
    
    
    // End of all conditions 
  delay(TIME_DELAY); 
  }  
}
