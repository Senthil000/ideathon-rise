#include <Keypad.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LCD-I2C.h>
#include<string.h>
LCD_I2C lcd(0x27, 16, 2);
RF24 radio(10, 14);
int n=0;
const byte address[6] = "00001"; 
const byte ROWS = 4; 
const byte COLS = 4; 
String c="";

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
      
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
  
}
  
void loop(){
  char a = customKeypad.getKey();
  
  
  if((a =='1')||(a=='2')||a=='3'||a=='4'||a=='5'||a=='6'||a=='7'||a=='8'||a=='9'||a=='A'||a=='B'|| a=='C'||a=='D'||a=='*'||a=='0'||a=='#' ){
    const char text[] = "";
  radio.write(&text, sizeof(text));
  Serial.println("Sent: ");
  Serial.println(text);
    if(a == '#'){

   char text[32];
   c.toCharArray(text,32);
  //c.toCharArray(text,c.length());
  radio.write(&text, sizeof(text));
  
  Serial.println("Sent: ");
  Serial.println(text);
  c="";
  lcd.clear();
   lcd.setCursor(0, 0); 
    lcd.print("sent:"); 
   
    
    // You can make spaces using well... spaces
    // Or setting the cursor in the desired position.
    lcd.print(text);
    delay(1000);
    lcd.clear();
delay(1000); 
  
  
  }else{
  c +=a;
  lcd.setCursor(0, 0); 
    lcd.print(c);
    delay(1000); 
    if(c.length()>16){
      for(int j =0;j<(c.length()-16);j++){
        lcd.scrollDisplayLeft();
        delay(300);
      }

    } 
    
  Serial.print(c);}    
}
}