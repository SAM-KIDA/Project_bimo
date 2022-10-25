
#include<LiquidCrystal.h>
LiquidCrystal lcd(13 ,12, 11, 10, 9, 8); //16x2 lcd arduino interface pins

//Custom characters byte arrays
byte customchar[8]={B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111};
byte a[8]={B00000,B00000,B00000,B00000,B10000,B01000,B00100,B00011};
byte s[8]={B00000,B00000,B00000,B00000,B00000,B00000,B00000,B11111};
byte s1[8]={B10000,B01000,B00100,B00011,B00000,B00000,B00000,B00000};
byte s2[8]={B01010,B00100,B00100,B01010,B10001,B00100,B10001,};
byte s3[8]={B00100,B01010,B11111,B01010,B10101,B11011,B10001,};
byte s4[8]={0x1F,0x11,0x11,0x11,0x11,0x11,0x1F,};
byte s5[8]={B11111,B11101,B11011,B11101,B11111,B10000,B10000,B10000,};
//Custom characters byte arrays

void setup()
{
lcd.begin(16 ,2);  //Initialize 16x2 lcd
lcd.clear();       //Clear lcd display screen

lcd.createChar(1 , customchar);   //Creating custom characters in CG-RAM
lcd.createChar(2 , a);                              
lcd.createChar(3 , s);
lcd.createChar(4 , s1);
/*lcd.createChar(5 , s2);
lcd.createChar(6 , s3);
lcd.createChar(7 , s4);
lcd.createChar(8 , s5); //Creating custom characters in CG-RAM
*/
}
void loop()
{
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
  /*int rand,i;
  lcd.setCursor(0 ,0);            //Place lcd cursor on first row and first coulomb of 16x2 lcd
  lcd.print("Cust Character!!");  //Display this test on first row on 16x2 lcd
  lcd.setCursor(0 ,1);            //Place lcd cursor on second row of 16x2 lcd first coulomb

  for(rand=0;rand<10;rand++){     //For loop will display custom characters one by one
    i=random(10);
    lcd.setCursor(i ,1);
    lcd.write(i);                 //-->>>PRINTING/DISPLAYING CUSTOM CHARACTERS
    delay(500);
  }*/
  delay(1000);
  lcd.clear();
   delay(1000);                      //Clear lcd and start again
}