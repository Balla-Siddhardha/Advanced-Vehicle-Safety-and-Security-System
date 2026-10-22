#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Wire.h>
#include <EEPROM.h>
const byte ROWS = 4, COLS = 4;
char hexaKeys[ROWS][COLS] = {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
byte rowPins[ROWS] = {31, 33, 35, 37}, colPins[COLS] = {41, 43, 45, 47};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(0,1,2,3,4,5);     //RS,E,D4,D5,D6,D7
char one, two, three, four, enter, sk1, sk2, sk3, sk4, sk5, sk6, skenter, new1, new2, new3, new4, newenter, cf1, cf2, cf3, cf4, cfenter;
int pw1, pw2, pw3, pw4, ch1, ch2, ch3, ch4, write1, write2, write3, write4, block_1=0, i=1, j=1, hide=1, alc=11, hel=12, Block_2=0, detection, curspeed, maxspeed=60, buzzer=13, maximum=1000, watch=0,delaytime=30, ij=0, twotimes=0, motor=7;
char message[]="Emergency. Location:Latitude, Longitude";
#include <MPU6050.h>
MPU6050 mpu;
int detect(){
  int a; const int alc=11, hel=12;
  if(digitalRead(alc) == HIGH && digitalRead(hel) == HIGH)  a=2;
  if(digitalRead(alc) == HIGH && digitalRead(hel) == LOW)  a=4;
  if(digitalRead(alc) == LOW && digitalRead(hel) == HIGH)  a=1;
  if(digitalRead(alc) == LOW && digitalRead(hel) == LOW)  a=3;
  return a;}
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
void SendMessage(){
  mySerial.println("AT+CMGF=1"); delay(1000);
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); delay(1000);
  mySerial.println(message); delay(100);
  mySerial.println((char)26); delay(1000); }
int RXPin=48,TXPin=49; SoftwareSerial gpsSerial(RXPin, TXPin);
void setup() {
  lcd.begin(16, 2); pinMode(motor, OUTPUT); analogWrite(motor, 0);
  while(block_1==0) {
    if(i==1 && j==1) {lcd.clear(); lcd.setCursor(0,0); lcd.print("Enter Password");
      one = customKeypad.getKey(); while (one == NO_KEY || one=='B' || one=='C' || one=='D' || one=='#' || one=='*')  one = customKeypad.getKey();
      if(one=='A'){i=2;j=1;lcd.clear();lcd.print("Forgot Password!");delay(2000);lcd.clear();hide=1;}
      else{lcd.setCursor(0,1);lcd.print("*");i=1;j=2;}}
    if(i==1 && j==2){two = customKeypad.getKey();while (two == NO_KEY || two=='B' || two=='D' || two=='#') two = customKeypad.getKey();
      if(two == 'C'){lcd.clear();i=1;j=1;hide=1;}
      else if(two == 'A'){i=2;j=1;lcd.clear();lcd.print("Forgot Password");delay(2000);lcd.clear();hide=1;}
      else if(two == '*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);lcd.print(one);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);lcd.print("*");hide=1;}i=1;j=2;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(one);lcd.print(two);}
        else{lcd.setCursor(0,1);lcd.print("**");}i=1;j=3;}}
    if(i==1 && j==3){three = customKeypad.getKey();
      while (three == NO_KEY || three=='B' || three=='D' || three=='#') three = customKeypad.getKey();
      if(three=='C'){lcd.clear();i=1;j=1;hide=1;}
      else if(three=='A'){i=2;j=1;lcd.clear();lcd.print("Forgot Password");delay(2000);lcd.clear();hide=1;}
      else if(three=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);lcd.print(one);lcd.print(two);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);lcd.print("**");hide=1;}i=1;j=3;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(one);lcd.print(two);lcd.print(three);}
        else{lcd.setCursor(0,1);lcd.print("***");}i=1;j=4;}}
    if(i==1 && j==4){four = customKeypad.getKey();
      while (four == NO_KEY || four=='B' || four=='D' || four=='#') four = customKeypad.getKey();
      if(four=='C'){lcd.clear();i=1;j=1;hide=1;}
      else if(four=='A'){i=2;j=1;lcd.clear();lcd.print("Forgot Password");delay(2000);lcd.clear();hide=1;}
      else if(four=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);lcd.print(one);lcd.print(two);lcd.print(three);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);lcd.print("***");hide=1;}i=1;j=4;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(one);lcd.print(two);lcd.print(three);lcd.print(four);}
        else{lcd.setCursor(0,1);lcd.print("****");}i=1;j=5;}}
    if(i==1 && j==5){enter = customKeypad.getKey();
      while (enter == NO_KEY || enter=='0' || enter=='1' || enter=='2' || enter=='3' || enter=='4' || enter=='5' || enter=='6' || enter=='7' || enter=='8' || enter=='9' || enter=='B' || enter=='#') enter = customKeypad.getKey();
      if(enter=='C'){lcd.clear();i=1;j=1;hide=1;}
      else if(enter=='A'){i=2;j=1;lcd.clear();lcd.print("Forgot Password");delay(2000);lcd.clear();hide=1;}
      else if(enter=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);lcd.print(one);lcd.print(two);lcd.print(three);lcd.print(four);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Enter Password");lcd.setCursor(0,1);lcd.print("****");hide=1;}i=1;j=5;}
      else{pw1=EEPROM.read(1);pw2=EEPROM.read(2);pw3=EEPROM.read(3);pw4=EEPROM.read(4);ch1=one-'0';ch2=two-'0';ch3=three-'0';ch4=four-'0';
        if(pw1==ch1 && pw2==ch2 && pw3==ch3 && pw4==ch4){
          lcd.clear();lcd.print("Access granted");delay(2000);block_1=1;}
        else{lcd.clear();lcd.print("Access denied");delay(2000);lcd.clear();i=1;j=1;hide=1;}}}
    if(i==2 && j==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");sk1 = customKeypad.getKey();
      while (sk1 == NO_KEY || sk1=='B' || sk1=='C' || sk1=='D' || sk1=='#' || sk1=='*')  sk1 = customKeypad.getKey();
      if(sk1 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else{lcd.setCursor(0,1);lcd.print("*");i=2;j=2;}}
    if(i==2 && j==2){sk2 = customKeypad.getKey();
      while (sk2 == NO_KEY || sk2=='B' || sk2=='D' || sk2=='#') sk2 = customKeypad.getKey();
      if(sk2 == 'C'){lcd.clear();i=2;j=1;hide=1;}
      else if(sk2 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(sk2 == '*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print(sk1);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print("*");hide=1;}i=2;j=2;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);}
        else{lcd.setCursor(0,1);lcd.print("**");}i=2;j=3;}}
    if(i==2 && j==3){sk3 = customKeypad.getKey();
      while (sk3 == NO_KEY || sk3=='B' || sk3=='D' || sk3=='#') sk3 = customKeypad.getKey();
      if(sk3=='C'){lcd.clear();i=2;j=1;hide=1;}
      else if(sk3 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(sk3=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print("**");hide=1;}i=2;j=3;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);lcd.print(sk3);}
        else{lcd.setCursor(0,1);lcd.print("***");}i=2;j=4;}}
    if(i==2 && j==4){sk4 = customKeypad.getKey();
      while (sk4 == NO_KEY || sk4=='B' || sk4=='D' || sk4=='#') sk4 = customKeypad.getKey();
      if(sk4=='C'){lcd.clear();i=2;j=1;hide=1;}
      else if(sk4 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(sk4=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);lcd.print(sk3);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print("***");hide=1;}i=2;j=4;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);lcd.print(sk3);lcd.print(sk4);}
        else{lcd.setCursor(0,1);lcd.print("****");}i=2;j=5;}}
    if(i==2 && j==5){sk5 = customKeypad.getKey();
      while (sk5 == NO_KEY || sk5=='B' || sk5=='D' || sk5=='#') sk5 = customKeypad.getKey();
      if(sk5=='C'){lcd.clear();i=2;j=1;hide=1;}
      else if(sk5 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(sk5=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);lcd.print(sk3);lcd.print(sk4);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print("****");hide=1;}i=2;j=5;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);lcd.print(sk3);lcd.print(sk4);lcd.print(sk5);}
        else{lcd.setCursor(0,1);lcd.print("*****");}i=2;j=6;}}
    if(i==2 && j==6){sk6 = customKeypad.getKey();
      while (sk6 == NO_KEY || sk6=='B' || sk6=='D' || sk6=='#') sk6 = customKeypad.getKey();
      if(sk6=='C'){lcd.clear();i=2;j=1;hide=1;}
      else if(sk6 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(sk6=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);lcd.print(sk3);lcd.print(sk4);lcd.print(sk5);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print("*****");hide=1;}i=2;j=6;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);lcd.print(sk3);lcd.print(sk4);lcd.print(sk5);lcd.print(sk6);}
        else{lcd.setCursor(0,1);lcd.print("******");}i=2;j=7;}}
    if(i==2 && j==7){skenter = customKeypad.getKey();
      while (skenter == NO_KEY || skenter=='0' || skenter=='1' || skenter=='2' || skenter=='3' || skenter=='4' || skenter=='5' || skenter=='6' || skenter=='7' || skenter=='8' || skenter=='9' || skenter=='B' || skenter=='#') skenter = customKeypad.getKey();
      if(skenter=='C'){lcd.clear();i=2;j=1;hide=1;}
      else if(skenter == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(skenter=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print(sk1);lcd.print(sk2);lcd.print(sk3);lcd.print(sk4);lcd.print(sk5);lcd.print(sk6);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Security Key");lcd.setCursor(0,1);lcd.print("******");hide=1;}i=2;j=7;}
      else{
        if(sk1=='1' && sk2=='2' && sk3=='3' && sk4=='4' && sk5=='5' && sk6=='6'){
          lcd.clear();lcd.print("Correct");delay(2000);lcd.clear();i=3;j=1;hide=1;}
        else{lcd.clear();lcd.print("Wrong");delay(2000);lcd.clear();i=2;j=1;hide=1;}}}
    if(i==3 && j==1){lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");new1 = customKeypad.getKey();
      while (new1 == NO_KEY || new1=='B' || new1=='C' || new1=='D' || new1=='#' || new1=='*')  new1 = customKeypad.getKey();
      if(new1 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else{lcd.setCursor(0,1);lcd.print("*");i=3;j=2;}}
    if(i==3 && j==2){new2 = customKeypad.getKey();
      while (new2 == NO_KEY || new2=='B' || new2=='D' || new2=='#') new2 = customKeypad.getKey();
      if(new2 == 'C'){lcd.clear();i=3;j=1;hide=1;}
      else if(new2 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(new2 == '*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);lcd.print(new1);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);lcd.print("*");hide=1;}i=3;j=2;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(new1);lcd.print(new2);}
        else{lcd.setCursor(0,1);lcd.print("**");}i=3;j=3;}}
    if(i==3 && j==3){new3 = customKeypad.getKey();
      while (new3 == NO_KEY || new3=='B' || new3=='D' || new3=='#') new3 = customKeypad.getKey();
      if(new3=='C'){lcd.clear();i=3;j=1;hide=1;}
      else if(new3 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(new3=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);lcd.print(new1);lcd.print(new2);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);lcd.print("**");hide=1;}i=3;j=3;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(new1);lcd.print(new2);lcd.print(new3);}
        else{lcd.setCursor(0,1);lcd.print("***");}i=3;j=4;}}
    if(i==3 && j==4){new4 = customKeypad.getKey();
      while (new4 == NO_KEY || new4=='B' || new4=='D' || new4=='#') new4 = customKeypad.getKey();
      if(new4=='C'){lcd.clear();i=3;j=1;hide=1;}
      else if(new4 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(new4=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);lcd.print(new1);lcd.print(new2);lcd.print(new3);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);lcd.print("***");hide=1;}i=3;j=4;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(new1);lcd.print(new2);lcd.print(new3);lcd.print(new4);}
        else{lcd.setCursor(0,1);lcd.print("****");}i=3;j=5;}}
    if(i==3 && j==5){newenter = customKeypad.getKey();
      while (newenter == NO_KEY || newenter=='0' || newenter=='1' || newenter=='2' || newenter=='3' || newenter=='4' || newenter=='5' || newenter=='6' || newenter=='7' || newenter=='8' || newenter=='9' || newenter=='B' || newenter=='#') newenter = customKeypad.getKey();
      if(newenter=='C'){lcd.clear();i=3;j=1;hide=1;}
      else if(newenter == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(newenter=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);lcd.print(new1);lcd.print(new2);lcd.print(new3);lcd.print(new4);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("New Password");lcd.setCursor(0,1);lcd.print("****");hide=1;}i=3;j=5;}
      else{lcd.clear();i=4;j=1;hide=1;}}
    if(i==4 && j==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");cf1 = customKeypad.getKey();
      while (cf1 == NO_KEY || cf1=='B' || cf1=='C' || cf1=='D' || cf1=='#' || cf1=='*')  cf1 = customKeypad.getKey();
      if(cf1 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else{lcd.setCursor(0,1);lcd.print("*");i=4;j=2;}}
    if(i==4 && j==2){cf2 = customKeypad.getKey();
      while (cf2 == NO_KEY || cf2=='B' || cf2=='D' || cf2=='#') cf2 = customKeypad.getKey();
      if(cf2 == 'C'){lcd.clear();i=4;j=1;hide=1;}
      else if(cf2 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(cf2 == '*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);lcd.print(cf1);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);lcd.print("*");hide=1;}i=4;j=2;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(cf1);lcd.print(cf2);}
        else{lcd.setCursor(0,1);lcd.print("**");}i=4;j=3;}}
    if(i==4 && j==3){cf3 = customKeypad.getKey();
      while (cf3 == NO_KEY || cf3=='B' || cf3=='D' || cf3=='#') cf3 = customKeypad.getKey();
      if(cf3=='C'){lcd.clear();i=4;j=1;hide=1;}
      else if(cf3 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(cf3=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);lcd.print(cf1);lcd.print(cf2);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);lcd.print("**");hide=1;}i=4;j=3;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(cf1);lcd.print(cf2);lcd.print(cf3);}
        else{lcd.setCursor(0,1);lcd.print("***");}i=4;j=4;}}
    if(i==4 && j==4){cf4 = customKeypad.getKey();
      while (cf4 == NO_KEY || cf4=='B' || cf4=='D' || cf4=='#') cf4 = customKeypad.getKey();
      if(cf4=='C'){lcd.clear();i=4;j=1;hide=1;}
      else if(cf4 == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(cf4=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);lcd.print(cf1);lcd.print(cf2);lcd.print(cf3);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);lcd.print("***");hide=1;}i=4;j=4;}
      else{lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);
        if(hide==0){lcd.setCursor(0,1);lcd.print(cf1);lcd.print(cf2);lcd.print(cf3);lcd.print(cf4);}
        else{lcd.setCursor(0,1);lcd.print("****");}i=4;j=5;}}
    if(i==4 && j==5){cfenter = customKeypad.getKey();
      while (cfenter == NO_KEY || cfenter=='0' || cfenter=='1' || cfenter=='2' || cfenter=='3' || cfenter=='4' || cfenter=='5' || cfenter=='6' || cfenter=='7' || cfenter=='8' || cfenter=='9' || cfenter=='B' || cfenter=='#') cfenter = customKeypad.getKey();
      if(cfenter=='C'){lcd.clear();i=4;j=1;hide=1;}
      else if(cfenter == 'A'){i=1;j=1;lcd.clear();lcd.print("Enter Password");delay(2000);lcd.clear();hide=1;}
      else if(cfenter=='*'){
        if(hide==1){lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);lcd.print(cf1);lcd.print(cf2);lcd.print(cf3);lcd.print(cf4);hide=0;}
        else{lcd.clear();lcd.setCursor(0,0);lcd.print("Confirm Password");lcd.setCursor(0,1);lcd.print("****");hide=1;}i=4;j=5;}
      else{
        if(new1==cf1 && new2==cf2 && new3==cf3 && new4==cf4){write1=cf1-'0';write2=cf2-'0';write3=cf3-'0';write4=cf4-'0';EEPROM[1]=write1;EEPROM[2]=write2;EEPROM[3]=write3;EEPROM[4]=write4; lcd.clear();lcd.print("Password Set");delay(2000);lcd.clear();i=1;j=1;hide=1;}
        else{lcd.clear();lcd.print("not matched");delay(2000);lcd.clear();i=3;j=1;hide=1;}}}}
  lcd.clear();
  //2nd feature
  pinMode(A0,INPUT);pinMode(alc,INPUT);pinMode(hel,INPUT);pinMode(buzzer,OUTPUT);pinMode(motor, OUTPUT);
  //while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){}
  while(Block_2==0){detection=detect();lcd.setCursor(0,1);
    if(detection==1)lcd.print("alc: N    hel: N");
    else if(detection==2)lcd.print("alc: Y    hel: N");
    else if(detection==3)lcd.print("alc: N    hel: Y");
    else if(detection==4)lcd.print("alc: Y    hel: Y");else;
    if(detection==4){
      if(maxspeed<60){maxspeed++;digitalWrite(buzzer, HIGH);delay(100);digitalWrite(buzzer, LOW);}
      else  delay(100);}
    else{
      if(maxspeed>10){  maxspeed--;digitalWrite(buzzer, HIGH);delay(100);digitalWrite(buzzer, LOW);}
      else  delay(100);}lcd.setCursor(0,0);curspeed=analogRead(A0);
    if(curspeed>maximum){curspeed=1000;}
    curspeed=curspeed/10;curspeed+=2;curspeed=maxspeed*curspeed;curspeed=curspeed/100;analogWrite(motor,curspeed*4);
    if(twotimes==2){lcd.print(curspeed);lcd.print("/");lcd.print(maxspeed);lcd.print(" kmph");twotimes=0;}delay(400);twotimes++;
    //Vector normAccel = mpu.readNormalizeAccel();
    //int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  //  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;
   // if(pitch>50 || pitch<-50 || roll>50 || roll<-50){digitalWrite(13, HIGH);watch=1;}
    if(watch==1){digitalWrite(13, HIGH);
      if(delaytime==0){Block_2==1;break;}lcd.setCursor(13,0);ij++;
      if(ij==2){lcd.print(delaytime);ij=0;delaytime--;}lcd.setCursor(13,0);lcd.print(delaytime);
      if(delaytime==9){lcd.setCursor(14,0);lcd.print(" ");}}
    char hash = customKeypad.getKey();
    if(hash=='#'){watch=0;delaytime=30;digitalWrite(13, LOW);lcd.setCursor(13,0);lcd.print("  ");}}
  analogWrite(motor, 0);lcd.clear();lcd.print("Emergency");delay(1000);lcd.clear();lcd.print("Message sent");
  gpsSerial.begin(9600);
  if (gpsSerial.available() > 0) {Serial.print(F("- latitude: "));Serial.println("gps.location.lat()");Serial.print(F("- longitude: "));Serial.println("gps.location.lng()");
  mySerial.begin(9600);delay(100);SendMessage();}}
void loop() {}
