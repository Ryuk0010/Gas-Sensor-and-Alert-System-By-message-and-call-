#include <SoftwareSerial.h>

SoftwareSerial SIM900A(2,3);//TX, RX
int LED1 = 8;
int LED2 = 9;
int FAN = 4;
int piezo = 5;
int LED2State = HIGH;
int x = 0;
void setup()
{
  SIM900A.begin(9600);   
  Serial.begin(9600);    
  pinMode(7, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(FAN, OUTPUT);
  Serial.println ("Starting...");
  delay(100);

}


void loop()
{
   int gasSensor = digitalRead(7);

  if(gasSensor == LOW){
      digitalWrite(piezo, HIGH);
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, HIGH);
      digitalWrite(FAN, HIGH);
//      x = x + 1;
//      if(x % 2 == 0){
       
//      }
      
//      delay(1000);
      SendMessage();
      delay(1000);
      Call();  
      delay(1000); 
      fire(); 
      delay(1000);
       
  }
  else{
      digitalWrite(piezo, LOW);
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(FAN, LOW);
      x = 0;
  }
  
  Serial.print("GasSensor = ");
  Serial.print(" ");
  Serial.print(gasSensor);
  Serial.println();
  
  delay(1000);

}


void SendMessage()   
  {   
  Serial.println ("Sending Message");   
  SIM900A.println("AT+CMGF=1");    
  delay(2000);   
  SIM900A.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");   
  delay(3000);      
  SIM900A.println("Alert!!! Gas Detected");
  delay(100);   
  Serial.println ("Finish");   
  SIM900A.println((char)26);  
  delay(1000);   
  Serial.println ("Message has been sent");   
  } 


void Call()
{
    Serial.println("Calling...");
    delay(2000);
    SIM900A.println("ATD+91xxxxxxxxxx;");
    delay(16000);
    SIM900A.println("ATH");
}

void fire()   
  {   
  Serial.println ("FireStation Message");   
  SIM900A.println("AT+CMGF=1");    
  delay(2000);   
  SIM900A.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");   
  delay(4000);      
  SIM900A.println("Alert!!! Fire Detected. Address: Sector V, Saltlake Electronics Complex.  This is a automated gas detection system. Please do the needful");   
  delay(100);   
  Serial.println ("Done");   
  SIM900A.println((char)26);  
  delay(1000);   
  Serial.println ("Firestation informed");   
  }
