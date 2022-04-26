char BYTE;
int buttonR=6;
int buttonL=7;
void setup() {
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  pinMode(buttonR,INPUT);
  pinMode(buttonL,INPUT);

}

void loop() {
  int droite=digitalRead(buttonR);
  int gauche=digitalRead(buttonL);
  if(droite==LOW)
  {
    Serial.write(2);
    Serial.println("deplacement droite");
    delay(500);
    }
    else if(gauche==LOW)
    {
        Serial.write(2);
    Serial.println("deplacement gauche");
    delay(500);
      }
      
    else{
      Serial.write(0);
      Serial.println("pas de deplacement");
      delay(500);
      }
      if(Serial.available()>0)
      {
        BYTE=Serial.read();
        if(BYTE=='1')
        {
          digitalWrite(10,HIGH);
          digitalWrite(11,LOW);
          Serial.write(1);
          Serial.println("collision droite\n");
          }
          else if(BYTE=='2')
          {
            digitalWrite(11,HIGH);
            digitalWrite(10,LOW);
            Serial.write(2);
            Serial.println("collision gauche\n");
            }
            else
            {
              digitalWrite(10,LOW);
              digitalWrite(11,LOW);
              Serial.write(0);
              Serial.println("pas de collision\n");
              }
        }
}
