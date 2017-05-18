#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "Keypad.h"

#define ROWS 4
#define COLS 4
int i;
int oper = 0;
int decision;

char keys[ROWS][COLS] = {
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '/'},
    {'*', '0', '#', '='}
};

byte rowPins[ROWS] = {A1, A2, A3, A4};
byte colPins[COLS] = {3, 4, 5, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
    lcd.begin(16, 2); 
    lcd.setBacklight(HIGH);
    lcd.home(); 
    Serial.begin(9600);

    i = -1;
}

void loop() {        
  int b = 0;
  int a = 0;
  String msg;
  char key = keypad.getKey();
  msg = key;
  if(msg != "-" && msg != "+" && msg != "/" && msg != "*"){
    if(oper == 0){ a = dataProcessing (msg); i = -1; }
    else b = dataProcessing (msg);
  }else{
    if(msg == "-") oper = 1;
    if(msg == "+") oper = 2;
    if(msg == "/") oper = 3;
    if(msg == "*") oper = 4;   
  }
  if(a != 0 && b != 0 && msg == "=")
    decision = counting(a, b, oper);
  
  
//  Serial.println(decision);
  Serial.print(a);
  Serial.print(" MMM ");
  Serial.println(b);

      
//  lcdPrint(mcg2, 0, 0);
} 

void lcdPrint(String msg, int numberStr, int startSymbol) {
    lcd.setCursor(0, numberStr); 
    lcd.print("                ");
    lcd.setCursor(startSymbol, numberStr); 
    lcd.print(msg);
}

int dataProcessing (String msg){
    
  if(msg == "1"){
    if(i == -1) i = 1;
    else i = i * 10 + 1;
  }
  
  if(msg == "2"){
     if(i == -1) i = 2;
    else i = i * 10 + 2;
  }
  
  if(msg == "3"){
     if(i == -1) i = 3;
    else i = i * 10 + 3;
  }
  
  if(msg == "4"){
     if(i == -1) i = 4;
    else i = i * 10 + 4;
  }
  
  if(msg == "5"){
     if(i == -1) i = 5;
    else i = i * 10 + 5;
  }
  
  if(msg == "6"){
     if(i == -1) i = 6;
    else i = i * 10 + 6;
  }
  
  if(msg == "7"){
     if(i == -1) i = 7;
    else i = i * 10 + 7;
  }
   
  if(msg == "8"){
    if(i == -1) i = 8;
    else i = i * 10 + 8;
  }

  if(msg == "9"){
    if(i == -1) i = 9;
    else i = i * 10 + 9;
  }
  
  if(msg == "0"){
    if(i == -1) i = 0;
    else i = i * 10;
  }
  
  return i;
  
}

int counting (int chislo1, int chislo2, int op){
  int out;
  
  if(op == 1) out = chislo1 - chislo2;
  if(op == 2) out = chislo1 + chislo2;
  if(op == 3) out = chislo1 / chislo2;
  if(op == 4) out = chislo1 * chislo2;

  return out;
  
}

