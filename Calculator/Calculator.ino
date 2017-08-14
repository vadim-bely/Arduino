#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "Keypad.h"
#include <stdlib.h>

#define ROWS 4
#define COLS 4
int i;
int decision;
boolean q;

char keys[ROWS][COLS] = {
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '/'},
    {'*', '0', '#', '='}
};

byte rowPins[ROWS] = {A1, A2, A3, 8};
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

String msg;
//String a;
//String b;
//String operationSymbol;
String result;
//String num;
String str;
boolean n = false;


void loop() {
  Serial.println(splitEquation("2+222*23111+(2+92)*22222"));
  String* s = splitString(splitEquation("2+222*23111+(2+2)*22222"), ' ');
  Serial.println("-------");
  for (int i = 0; i < sizeof(s); i++) {
//    Serial.println(s[i]);
  }

  delay(10000);


 //   Serial.println("---------------");
//    Serial.println(equation.length());
//    for (int i = 0; i < sizeof(equationMass); i++) {
 //     Serial.print(equationMass[i]);
//    }
//    Serial.println("|");
 //   Serial.println("---------------");
 //   delay(10000000);


  /*
  char key = keypad.getKey();
  if (key != NO_KEY) {
    if (key != '=') {
      if (n){
        result = "";
        str = "";
      }
      msg += key;
      str = msg ;

    } else {
      str += "=";
      str += execute("2 + 2");
      msg = "";
      n = true;
            Serial.println(str);

    }
//      Serial.println(key);
  }
//        Serial.println(msg);

  lcdPrint(str, 0, 0);
  */
}

void lcdPrint(String msg, int numberStr, int startSymbol) {
    lcd.setCursor(0, numberStr);
    lcd.print("                ");
    lcd.setCursor(startSymbol, numberStr);
    lcd.print(msg);
}

String execute(String equation) {
    //  return to_string(sumEquation(priorityProcessing(parenthesisPriority(splitEquation(equation)))));
    //  return splitEquation(equation);
    return to_string(sumEquation(priorityProcessing(parenthesisPriority(equation))));
}

String splitEquation(String equation){
    char equationMass[equation.length()];
    equation.toCharArray(equationMass, equation.length()+1);

    String result = "";
    String lastNum = "";

    for (int i = 0; i < sizeof(equationMass); i++) {
        char ch = equationMass[i];
        if (ch != ' ') {
            if (ch == '*' || ch == '/' || ch == '+' || ch == '-') {
                result += lastNum;
                result += " ";
                result += ch;
                result += " ";
                lastNum = "";
            } else if (ch == '(' || ch == ')') {
                if (lastNum != "") {
                    result += lastNum;
                    result += " ";
                    lastNum = "";
                }
                result += ch;
                if (ch != ')') {
                    result += " ";
                }
            } else {
                lastNum += ch;
            }
        }
    }
    result += lastNum;
    return result;
}

String* splitString(String equation, char separator) {
    char equationMass[equation.length()];
    equation.toCharArray(equationMass,equation.length()+1);

    String result[equation.length()];

    int count = 0;

    for (i = 0; i < equation.length(); i++) {
        char ch = equationMass[i];
        if (ch != separator){
            result[count] += ch;
        } else {
            count++;
        }
    }

//        Serial.println(sizeof(result));
    for (int i = 0; i < count+1; i++) {
//        Serial.println(result[i]);
    }

    String* mass = malloc(count+1);

    for (int i = 0; i < count+1; i++) {
        mass[i] = result[i];
    }
//    memcpy(mass, result, count);

    return mass;
}

String* parenthesisPriority(String equation) {

//  char* eq [equation.length()];

  String* equationMass/*[sizeof(splitString(equation, ' '))]*/ = splitString(equation, ' ');
  // = equation.split(" ");
  String result[sizeof(equationMass)];
  String parenthesisMass[sizeof(equationMass) - 2];
  boolean brace = false;
  int countParenthesis = 0;
  int countResult = 0;

  for (i = 0; i < sizeof(equationMass); i++) {
    String value = equationMass[i];
    if (value.equals("(")){
      brace = true;
    } else if (value.equals(")")) {
      brace = false;

      String tmpMass[countParenthesis];
      memcpy(tmpMass, parenthesisMass, countParenthesis);
//      System.arraycopy(parenthesisMass, 0, tmpMass, 0, countParenthesis);

      result[countResult] = to_string(sumEquation(priorityProcessing(tmpMass)));
      countResult++;
      countParenthesis = 0;
      parenthesisMass[sizeof(equationMass) - 2];
      parenthesisMass[countParenthesis] = value;
      countParenthesis++;
    } else {
    result[countResult] = value;
    countResult++;
    }
  }

  equationMass[countResult];
  memcpy(equationMass, result, countResult);
//  System.arraycopy(result, 0, equationMass, 0, countResult);
  return equationMass;
  }

String* priorityProcessing (String equationMass[]) {

  int e = sizeof(equationMass) / sizeof(String);
  String result[e];

  int count = 0;
  String lastNum = "";
  String lastSymbol = "";

  for (int i = 0; i < e; i++) {
    String str = equationMass[i];

    if (lastNum == "") {
      lastNum = str;
      } else if (str.equals("*") || str.equals("/")) {
        lastSymbol = str;
      } else if (lastSymbol != "") {
        int preNum = atoi(lastNum.c_str());
       int postNum = atoi(str.c_str());
        lastNum = to_string(dataProcessing(preNum, postNum, lastSymbol));
        lastSymbol = "";
      } else {
        result[count++] = lastNum;
        result[count++] = str;
        lastNum = "";
      }

    if (i == e - 1) {
        result[count] = lastNum;
    }
  }

  equationMass = new String[count + 1];
  for ( i = 0; i < count + 1; i++){
     equationMass[i] = result[i];
  }

  return equationMass;
}

int dataProcessing(int firstNum, int secondNum, String operationSymbol) {
  if (operationSymbol == "-") {
    return firstNum - secondNum;
  }else if (operationSymbol == "+"){
    return firstNum + secondNum;
  }else if (operationSymbol == "*"){
    return firstNum * secondNum;
  }else if (operationSymbol == "/") {
    return firstNum / secondNum;
  }

}

int sumEquation(String equationMass[]) {
  String lastNum = "";
  String lastSymbol = "";

  for (int i = 0; i < sizeof(equationMass); i++) {
    String str = equationMass[i];

    if (lastNum == "") {
      lastNum = str;
    } else if (lastSymbol == "") {
      lastSymbol = str;
    } else if (lastSymbol.equals("+") || lastSymbol.equals("-")) {
      int preNum =  atoi(lastNum.c_str());
      int postNum =  atoi(str.c_str());
      lastNum = to_string(dataProcessing(preNum, postNum, lastSymbol));
     lastSymbol = "";
   }
  }
  return atoi(lastNum.c_str());
}

String to_string(int n)
{
    char sCount[5];
    itoa(n, sCount, 10);

    return sCount;
}