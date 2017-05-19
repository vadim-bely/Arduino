#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "Keypad.h"

#define ROWS 4
#define COLS 4
int i;
int oper = 0;
int decision;
boolean q;

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

    i = 0;
    q = false;
}

void loop() {        
  int b;
  int a;
  String msg;
  char key = keypad.getKey();
  msg = key;

  if(msg == "-" || msg == "+" || msg == "/" || msg == "*"){
    if(msg == "-") oper = 1;
    if(msg == "+") oper = 2;
    if(msg == "/") oper = 3;
    if(msg == "*") oper = 4; 
    i = 0;
    q = false;  
  }
  
  if(oper == 0) a = dataProcessing (msg);
  else b = dataProcessing (msg);


  if(msg == "=")
    decision = counting(a, b, oper);
  
  
  Serial.print(a);
  Serial.print(" MMM ");
  Serial.print(b);
  Serial.print(" MMM ");
  Serial.println(decision);

      
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
    if(q == false) {
      i = 1;
      q = true;
    }else{
      i = i * 10 + 1;
    }
  }
  
  if(msg == "2"){
     if(q == false) {
      i = 2;
      q = true;
     }else{ 
      i = i * 10 + 2;
     }
  }
  
  if(msg == "3"){
     if(q == false) {
      i = 3;
      q = true;
     }else{
      i = i * 10 + 3;
     }
  }
  
  if(msg == "4"){
     if(q == false) {
      i = 4;
      q = true;
     }else{
      i = i * 10 + 4;
     }
  }
  
  if(msg == "5"){
     if(q == false) {
      i = 5;
      q = true;
     }else{
      i = i * 10 + 5;
     }
  }
  
  if(msg == "6"){
     if(q == false) {
      i = 6;
      q = true;
     }else{
      i = i * 10 + 6;
     }
  }
  
  if(msg == "7"){
     if(q == false) {
      i = 7;
      q = true;
     }else{
      i = i * 10 + 7;
     }
  }
   
  if(msg == "8"){
     if(q == false) {
      i = 8;
      q = true;
     }else{
      i = i * 10 + 8;
     }
  }

  if(msg == "9"){
     if(q == false) {
      i = 9;
      q = true;
     }else{
      i = i * 10 + 9;
     }
  }
  
  if(msg == "0"){
     if(q == false) {
      i = 0;
      q = true;
     }else{
      i = i * 10;
     }
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

