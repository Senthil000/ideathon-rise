#include <SPI.h>
#include <LCD-I2C.h>
#include <nRF24L01.h>
#include <RF24.h>
LCD_I2C lcd(0x27, 16, 2);  
// CE and CSN pins
RF24 radio(7, 8);

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
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    
    Serial.print("Received: ");
    Serial.println(text);
    lcd.setCursor(0, 0); 
    lcd.print("sent:"); 
   
    
    // You can make spaces using well... spaces
    // Or setting the cursor in the desired position.
    lcd.print(text);
    delay(500);
    lcd.clear();
delay(1000);
  }
}
