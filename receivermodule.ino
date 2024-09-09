#include <SPI.h>
#include <LCD-I2C.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<string.h>
LCD_I2C lcd(0x27, 16, 2);  
// CE and CSN pins
RF24 radio(10, 14);

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
   Wire.begin();
    lcd.begin(&Wire);
    lcd.display();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(" REC:-RECEIVED MESSAGE ");
    delay(300);
    for(int i=0;i<22;i++){
    lcd.scrollDisplayLeft();
    delay(500);}
    lcd.clear();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    
    Serial.print("Received: ");
    Serial.println(text);
    lcd.setCursor(0, 0);
    
    
  if(strlen(text)>1){ 
     
   
    
    // You can make spaces using well... spaces
    // Or setting the cursor in the desired position.
    if(strlen(text)>12){
    lcd.print("REC:");
    lcd.print(text);
    delay(1000);
    for(int i=0;i<(strlen(text)-11);i++){
    lcd.scrollDisplayLeft();
    delay(500);}}
    else{
    lcd.print("REC:");
    lcd.print(text);
    delay(1000); 

    }
    lcd.clear();}
    else{
       lcd.print("REC:"); 
   
    
    // You can make spaces using well... spaces
    // Or setting the cursor in the desired position.
    lcd.print(text);
    delay(500);
    }
   
    lcd.clear();

  }
}