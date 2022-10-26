//________________REMOTE_________________
#include <IRremote.h>
IRrecv mo(7);
decode_results ans;
int press;

//________________DC-MOTOR_________________
int speedpin = 6,  dir1 = A0, dir2 = A1;
int zspeed = 255; //it carries too much load so going for max speed for now

//________________LCD_________________
#include<LiquidCrystal.h>
LiquidCrystal lcd(13 ,12, 11, 10, 9, 8); //16x2 lcd arduino interface pins

//Custom characters byte arrays
byte customchar[8]={B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111};
byte a[8]={B00000,B00000,B00000,B00000,B10000,B01000,B00100,B00011};
byte s[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00000,B11111};
byte s1[8]={B00000,B00000,B00000,B00000,B00001,B00010,B00100,B11000};
byte s2[8]={B11000,B11000,B11000,B11000,B11000,B11000,B11000,B11000};
byte s3[8]={B00011,B00011,B00011,B00011,B00011,B00011,B00011,B00011};
byte s4[8]={0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00};
byte s5[8]={B11111,B11101,B11011,B11101,B11111,B10000,B10000,B10000,};
//Custom characters byte arrays

int time = 1000, time2 = 500;

void setup()
{
lcd.begin(16 ,2);
lcd.clear();

lcd.createChar(1 , customchar);   //Creating custom characters in CG-RAM
lcd.createChar(2 , a);
lcd.createChar(3 , s);
lcd.createChar(4 , s1);
lcd.createChar(5 , s2);
lcd.createChar(6 , s3);
lcd.createChar(7 , s4);
/*lcd.createChar(8 , s5); //Creating custom characters in CG-RAM
*/

Serial.begin(9600);
mo.enableIRIn();

pinMode(speedpin, OUTPUT);
pinMode(dir1, OUTPUT);
pinMode(dir2, OUTPUT);
}
void loop()
{
 // wait();

  while (mo.decode(&ans) == 0)  {}
  delay(1000);
  press = ans.value;
  switch(press)
  {
    case 0xFFA25D:
      smile();
      break;

    case 0xFF629D:
       focus();
       break;
    case 0xFFA857:
      digitalWrite(dir1, LOW);
      digitalWrite(dir2, HIGH);
      analogWrite(speedpin, zspeed);
      break;
    case 0xFF906F:
      digitalWrite(dir2, LOW);
      digitalWrite(dir1, HIGH);
      analogWrite(speedpin, zspeed);
      break;
    case 0xFFE21D:
      digitalWrite(dir2, LOW);
      digitalWrite(dir1, LOW);
      analogWrite(speedpin, zspeed);
      break;
  }
  delay(time);
  mo.resume();

}
void smile()
  {
  lcd.clear();
  lcd.setCursor(7 ,0);
  lcd.write(1);
  lcd.setCursor(9 ,0);
  lcd.write(1);
  lcd.setCursor(7 ,1);
  lcd.write(2);
  lcd.setCursor(8 ,1);
  lcd.write(3);
  lcd.setCursor(9 ,1);
  lcd.write(4);
  lcd.setCursor(6 ,0);
  lcd.write(5);
  lcd.setCursor(10 ,0);
  lcd.write(6);
  lcd.setCursor(6 ,1);
  lcd.write(5);
  lcd.setCursor(10 ,1);
  lcd.write(6);
  delay(time);
  }
void focus()
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("FOCUS MODE");
    delay(time);
    lcd.clear();
    lcd.setCursor(7 ,0);
    lcd.write(7);
    lcd.setCursor(9 ,0);
    lcd.write(7);
    lcd.setCursor(7 ,1);
    lcd.write(3);
    lcd.setCursor(8 ,1);
    lcd.write(3);
    lcd.setCursor(9 ,1);
    lcd.write(3);
    lcd.setCursor(6 ,0);
    lcd.write(5);
    lcd.setCursor(10 ,0);
    lcd.write(6);
    lcd.setCursor(6 ,1);
    lcd.write(5);
    lcd.setCursor(10 ,1);
    lcd.write(6);
    delay(time2);
  }
void wait()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("waiting for");
  lcd.setCursor(2, 1);
  lcd.print("command");
}
