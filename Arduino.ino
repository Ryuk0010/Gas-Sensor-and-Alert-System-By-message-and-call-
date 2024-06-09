#include <SoftwareSerial.h>   
SoftwareSerial SIM900A(10,11); // SoftSerial( RX , TX );   

int LED1 = 8;
int LED2 = 9;
int FAN = 4;
int piezo = 5;
int LED2State = HIGH;
int temp = 7;
int x = 0;


void setup(){
  pinMode(2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(FAN, OUTPUT);
  SIM900A.begin(9600); // Setting the baud rate of GSM Module    
  Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)   
  Serial.println ("SIM900A Ready");   
  delay(1000);   

}

void loop(){
  int gasSensor = digitalRead(2);

  if(gasSensor == LOW){
    digitalWrite(piezo, HIGH);
    digitalWrite(LED1, LOW); 
    digitalWrite(LED2, HIGH);
    digitalWrite(FAN, HIGH);
    if(x%5 == 0){
      message();
      delay(5000);
    }
    if(x % 10 == 0){
      call();
      delay(5000);
    }
    if(x == 80){
      fireStation();
    }
    x = x + 1;

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

void message(){
     Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000); 
     Serial.println("AT+CMGS=\"+91xxxxxxxxx\"\r"); // Mobile number
     Serial.println("Gas Leakage Alert");// The SMS 
     Serial.println((char)26);
     delay(8000);
}


void fireStation(){
     Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000); 
     Serial.println("AT+CMGS=\"+91xxxxxxxxx\"\r"); // Mobile number
     Serial.println("Fire has been detected. This is a automatic system. Address- your address goes here, you can also take the location from google map. Phone No of the Ownwe - +91xxxxxxxxxx");
     Serial.println((char)26);
     delay(8000);
}