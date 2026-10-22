//  REFER TO WOKWI for simulation  https://wokwi.com/projects/349112511412306515

//  * key is to hide or unhide password
//  B key is to delete entered password
//  D key is to submit password
 
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>
int i=1;
int hide=0;
char one, two, three, four, hash;
char first='1'; char second='2'; char third='4'; char forth='7';
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
                             {'1','2','3','A'},
                             {'4','5','6','B'},
                             {'7','8','9','C'},
                             {'*','0','#','D'}
                                              };
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  pinMode(11,INPUT);
  pinMode(12,OUTPUT);
  lcd.begin(16,2);
  while(1)
  {
      //*Password*//
  lcd.print("Enter Password");
  delay(500);
  lcd.setCursor(0, 1);
  
  int w=0;
  while(w==0)
  {
    int i=1;
    while(i<6)
    {
      if(i==1)
      {
        lcd.setCursor(0,1);
        one = customKeypad.getKey();
        while (one == NO_KEY || one=='A' || one=='B' || one=='C' || one=='D' || one=='#' || one=='*')  one = customKeypad.getKey();
        if(hide==1)
          {
            lcd.print(one);
          }
          else
          {
            lcd.print("*");
          }
        i=2;
      }
      if(i==2)
      {
        lcd.setCursor(1,1);
        two = customKeypad.getKey();
        while (two == NO_KEY || two=='A' || two=='C' || two=='D' || two=='#') two = customKeypad.getKey();
        if(two=='B')
        {
          lcd.setCursor(0,1);
          lcd.print(" ");
          i=1;
        }
        else if(two == '*')
        {
          if(hide==0)
          {
            lcd.setCursor(0,1);
            lcd.print(one);
            hide=1;
          }
          else
          {
            lcd.setCursor(0,1);
            lcd.print("*");
            hide=0;
          }
          i=2;
        }
        else
        {
          if(hide==1)
          {
            lcd.print(two);
          }
          else
          {
            lcd.print("*");
          }
          i=3;
        }
      }
      if(i==3)
      {
        lcd.setCursor(2,1);
        three = customKeypad.getKey();
        while (three == NO_KEY || three=='A' || three=='C' || three=='D' || three=='#') three = customKeypad.getKey();
        if(three=='B')
        {
          lcd.setCursor(1,1);
          lcd.print(" ");
          i=2;
        }
        else if(three == '*')
        {
          if(hide==0)
          {
            lcd.setCursor(0,1);
            lcd.print(one);
            lcd.print(two);
            hide=1;
          }
          else
          {
            lcd.setCursor(0,1);
            lcd.print("**");
            hide=0;
          }
          i=3;
        }
        else
        {
          if(hide==1)
          {
            lcd.print(three);
          }
          else
          {
            lcd.print("*");
          }
          i=4;
        }
      }
      if(i==4)
      {
        lcd.setCursor(3,1);
        four = customKeypad.getKey();
        while (four == NO_KEY || four=='A' || four=='C' || four=='D' || four=='#') four = customKeypad.getKey();
        if(four=='B')
        {
          lcd.setCursor(2,1);
          lcd.print(" ");
          i=3;
        }
        else if(four == '*')
        {
          if(hide==0)
          {
            lcd.setCursor(0,1);
            lcd.print(one);
            lcd.print(two);
            lcd.print(three);
            hide=1;
          }
          else
          {
            lcd.setCursor(0,1);
            lcd.print("***");
            hide=0;
          }
        }
        else
        {
          if(hide==1)
          {
            lcd.print(four);
          }
          else
          {
            lcd.print("*");
          }
          i=5;
        }
      }
      if(i==5)
      {
        char hash = customKeypad.getKey();
        while (hash == NO_KEY || hash=='0' || hash=='1' || hash=='2' || hash=='3' || hash=='4' || hash=='5' || hash=='6' || hash=='7' || hash=='8' || hash=='9' || hash=='A' || hash=='C' || hash=='#') 
          hash = customKeypad.getKey();
        if(hash=='B')
        {
          lcd.setCursor(3,1);
          lcd.print(" ");
          i=4;
        }
        else if(hash == '*')
        {
          if(hide==0)
          {
            lcd.setCursor(0,1);
            lcd.print(one);
            lcd.print(two);
            lcd.print(three);
            lcd.print(four);
            hide=1;
          }
          else
          {
            lcd.setCursor(0,1);
            lcd.print("****");
            hide=0;
          }
          i=5;
        }
        else
        {
          i=6;
        }
      }
    }
    if(one=='1' && two=='2' && three=='3' && four=='4')
      w=1;
    else
    { 
      lcd.print(" -->wrong");
      delay(2000);
      lcd.clear();
      lcd.print("Enter Again");
      lcd.setCursor(0, 1);
      hide=0;
    }    
  }
  lcd.print(" -->correct");
  delay(2000);
  lcd.clear();
  lcd.print("    Unlocked    ");
  delay(2000);
  lcd.clear();
  hide=0;
  }
}
void loop() {
}
