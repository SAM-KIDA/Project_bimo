//________________REMOTE_________________
#include <IRremote.h>
IRrecv mo(7);
decode_results ans;
int press;

//________________DC-MOTOR_________________
int speedpinA = 6, speedpinB = 3,  dir1 = A0, dir2 = A1, dir3 = A2, dir4 = A3; 
int zspeed = 255; //it carries too much load so going for max speed for now 

//________________STEPPER-MOTOR_________________
#include <Stepper.h>
const int stepsPerRevolution = 500;
Stepper myStepper = Stepper(stepsPerRevolution, 3, 2, 1, 0);

//________________SERVO-MOTOR_________________
#include <Servo.h>
int servoPin = 5;
Servo servo;
int angle = 0;

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

int time = 1000, time2 = 500, time3 = 3000;

void setup()
{
//_________LCD___________  
lcd.begin(16 ,2); 
lcd.clear();  
lcd.createChar(1 , customchar);   //Creating custom characters in CG-RAM
lcd.createChar(2 , a);                              
lcd.createChar(3 , s);
lcd.createChar(4 , s1);
lcd.createChar(5 , s2);
lcd.createChar(6 , s3);
lcd.createChar(7 , s4);
wait();

//_________REMOTE___________  
mo.enableIRIn();

//_________DC___________  
pinMode(speedpinA, OUTPUT);
pinMode(speedpinA, OUTPUT);
pinMode(dir1, OUTPUT);
pinMode(dir2, OUTPUT);
pinMode(dir3, OUTPUT);
pinMode(dir4, OUTPUT);

//_________SERVO___________  
servo.attach(servoPin);

}
void loop()
{
  smile();

  while (mo.decode(&ans) == 0)  {}
  delay(1000);
  press = ans.value;
  switch(press) 
  {
    case 0xFF02FD:
      myStepper.setSpeed(10);
      myStepper.step(stepsPerRevolution);
      delay(1000);
      break;
   case 0xFFC23D:
      myStepper.setSpeed(10);
      myStepper.step(-stepsPerRevolution);
      delay(1000);
      break;
      
    case 0xFFA25D:
      focus();
      for(angle = 0; angle < 60; angle++) {
          servo.write(angle);
          delay(15);
      }
      break;

    case 0xFF629D:
       focus();
       for(angle = 60; angle > 0; angle--) {
          servo.write(angle);
          delay(15);
      }
       break;
    case 0xFFA857:
      focus();
      digitalWrite(dir1, LOW);
      digitalWrite(dir2, HIGH);
      digitalWrite(dir3, LOW);
      digitalWrite(dir4, HIGH);
      analogWrite(speedpinA, zspeed);
      analogWrite(speedpinB, zspeed);
      break;
    case 0xFF906F:
      focus();
      digitalWrite(dir2, LOW);
      digitalWrite(dir1, HIGH);
      digitalWrite(dir4, LOW);
      digitalWrite(dir3, HIGH);
      analogWrite(speedpinA, zspeed);
      analogWrite(speedpinB, zspeed);
      break;
    case 0xFFE21D:
      digitalWrite(dir2, LOW);
      digitalWrite(dir1, LOW);
      digitalWrite(dir3, LOW);
      digitalWrite(dir4, LOW);
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
  delay(time3);
}