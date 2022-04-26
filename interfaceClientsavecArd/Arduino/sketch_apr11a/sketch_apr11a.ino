

#include <Keypad.h>


char data;

//Keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};
  

String ch;
int buzzer = 11;
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup() {
 
  Serial.println("Robojax 4x4 keypad");
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()){     
    
    data=Serial.read();  
    
     if(data=='1') 
    {
      
      Serial.write('1'); 
      delay(300);
       tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      
      
     }  
    
    else if(data=='2') 
    {
     
      Serial.write('1'); 
       delay (300);
   
   
         tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
       tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
      
     }  

      else if(data=='3') 
    {
      
      Serial.write('1'); 
       delay (300);
   
   
         tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
       tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
      tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
      
     } 
     else if(data=='4') 
    {
      
      Serial.write('1'); 
       delay (300);
   
   
         tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
       tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
      tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
      tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
     } 
   else if(data=='5') 
    {
      
      Serial.write('1'); 
       delay (300);
   
   
         tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
       tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
      tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
      tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
      tone (buzzer, 450);
      delay (500);
      noTone (buzzer);
      delay(500);
     }
      
  }
  
  char key = keypad.getKey();
    // just print the pressed key
   if (key){
    ch+=key; 
    Serial.print(key);
  
   } 
    
    
}
