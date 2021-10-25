#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "pitches.h"

#define SHOOT_LED 8
#define LEVEN_3 9
#define LEVEN_2 10
#define LEVEN_1 11
#define BUTTON 2
#define LEDR 6
#define LEDG 7
#define LEDB 12
#define SPEAKER 13
#define minimum 1000
#define maximum 5000
#define DATA 3
#define LATCH 4
#define CLOCK 5
#define PUNT 1
#define a 32
#define b 64
#define c 2
#define d 4
#define e 128
#define f 16
#define g 8

#define EEN b+c 
#define TWEE a+b+g+e+d
#define DRIE a+b+g+c+d
#define VIER f+g+b+c
#define VIJF a+f+g+c+d
#define ZES a+f+g+c+d+e
#define ZEVEN a+b+c
#define ACHT a+b+c+d+e+f+g
#define NEGEN d+c+g+f+a+b
#define SAD b+d+f

unsigned long time1;
unsigned long time2;
bool uplevel=false;
int modus=0;
byte data = 0;
int level=1;

int cycle=0;
int score=0;
int begintijd=1000;
int leven=3;
bool start=false;

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display






// Two things need to be created: the array for the notes of the melody (in order)
// and the duration of each (think of it like sheet music in two parts)

// BOTH ARRAYS MUST BE THE SAME SIZE!

// The melody array 
int melody[] = {
  NOTE_FS3, NOTE_GS3, NOTE_A3, NOTE_E3, NOTE_FS3, NOTE_C4,NOTE_B2
  ,NOTE_B2,NOTE_B2
};

// The note duration, 8 = 8th note, 4 = quarter note, etc.
int durations[] = {
  8, 8, 8, 8, 4,4, 2
 ,4,4
};
// determine the length of the arrays to use in the loop iteration
int songLength = sizeof(melody)/sizeof(melody[0]);






void setup() {
  lcd.init();       // initialize the lcd 
  lcd.backlight();
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(SHOOT_LED, OUTPUT);
  pinMode(LEVEN_1, OUTPUT);
  pinMode(LEVEN_2, OUTPUT);
  pinMode(LEVEN_3, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);  
  pinMode(CLOCK, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(SPEAKER,OUTPUT);
  Serial.begin(9600);
}


void resetled(){
  digitalWrite(LEVEN_3, LOW);
  digitalWrite(LEVEN_2, LOW);
  digitalWrite(LEVEN_1, LOW);
  digitalWrite(SHOOT_LED, LOW);
}

void loop(){
  int buttonState = digitalRead(BUTTON);
  if(modus==0){
  if(start==false){
    lcd.clear();
    lcd.setCursor(0,0);
     lcd.print("PRESS THE BUTTON");
    lcd.setCursor(4,1);
    lcd.print("TO START");
    start=true;
  }

     cycle+=1;
     if(cycle==3){
        cycle=0;
     }
     level=1;
     if(cycle==0){
      digitalWrite(LEVEN_3, LOW);
      digitalWrite(LEVEN_1, HIGH);
      digitalWrite(SHOOT_LED, HIGH);
      RGB_color(0, 255, 255); // Light blue
      
    
      data= PUNT;
     }
     if(cycle==1){
      digitalWrite(LEVEN_1, LOW);
      digitalWrite(LEVEN_2, HIGH);
      RGB_color(255, 0, 255); // Magenta
     
     }
     if(cycle==2){
      digitalWrite(LEVEN_2, LOW);
      digitalWrite(LEVEN_3, HIGH);
      digitalWrite(SHOOT_LED, LOW);
      RGB_color(255, 255, 0); // Yellow 
      data=0;
     }
  
  delay(300);

  if(buttonState == LOW){
    modus=1;
    resetled();
    lcd.clear();
    start=false;
    delay(1000);
  }
  }

if(modus==1){
resetled();
if(leven==3){
   RGB_color(0, 255, 0);
  digitalWrite(LEVEN_1, HIGH);
  digitalWrite(LEVEN_2, HIGH);
  digitalWrite(LEVEN_3, HIGH);
   
  }
  if(leven==2){
    RGB_color(255, 255, 0);
  digitalWrite(LEVEN_2, HIGH);
  digitalWrite(LEVEN_3, HIGH);
  }
  if(leven==1){
    RGB_color(255, 0, 0);
  digitalWrite(LEVEN_3, HIGH);
  
  }

int tijd=random(minimum,maximum);

int time3=10;
bool vroeg=false;
float testtijd=level*100;
time1=millis();
if(level==1){
  data=EEN;
}
if(score==3){
  level=2; //0.8
data=TWEE;
levelup();
  } 
  if(score==6){
  level=3; //0.7
  data=DRIE;
  levelup();
  }
  if(score==9){
  level=4; //0.6
  data=VIER;
  levelup();
  }
  if(score==13){
  level=5; //0.5
  data=VIJF;
  levelup();
  }
  if(score==17){
  level=6; //0.4
  data=ZES;
  levelup();
  }
  if(score==22){
  level=7; //0.3
  data=ZEVEN;
  levelup();
  }
  if(score==27){
  level=8; //0.2
  data=ACHT;
  levelup();
  }
  if(score==33){
  level=9; //0.1
  data=NEGEN;
  levelup();
  }

lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PRESS THE BUTTON");
  lcd.setCursor(0,1);
  lcd.print("IF RED LED IS ON");
  if(uplevel==true){
    delay(2000);
    uplevel=false;
  }

while(time3<=tijd&&vroeg==false){
  
time3=millis()-time1;

buttonState = digitalRead(BUTTON);

if(buttonState==LOW){
  leven-=1;
  Serial.println("te vroeg!");
  lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("TE VROEG");
  lcd.setCursor(0,1);
  lcd.print("D:");
  RGB_color(0, 255, 255);
vroeg=true;
  delay(2000);
}
}



  if(buttonState==HIGH&&vroeg==false){
    digitalWrite(SHOOT_LED, HIGH);
  time1=millis();
  while(buttonState==HIGH){
    buttonState = digitalRead(BUTTON);
  }
  time2=millis();
     time3=time2-time1;
     
     
   if(time3<=begintijd-testtijd){
    Serial.println("RAAK!");
    RGB_color(0, 255, 255);
    lcd.clear();
     lcd.setCursor(0,0);
  lcd.print("RAAK!");
  lcd.setCursor(0,1);
  lcd.print(":D");
   }

  if(time3>=begintijd-testtijd){
    leven-=1;
    Serial.println("te laat!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TE LAAT");
  lcd.setCursor(0,1);
  lcd.print("D:");
  RGB_color(0, 255, 255);
    RGB_color(0, 255, 255);
  }
  delay(2000);
  }
  if(vroeg==false){
  Serial.println("Dit koste: ");
  Serial.print(time3*0.001);
  Serial.println(" Seconden");
  lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("Dit koste:");
   lcd.setCursor(0,1);
  lcd.print(time3*0.001);
   lcd.setCursor(13,1);
  lcd.print("sec");
  delay(2000);
  }
vroeg=false;
uplevel=false;
score+=1;
  if(leven==0){
  modus=2;
  }
  
  
}


if(modus==2){
  digitalWrite(SHOOT_LED, HIGH);
  long highscore=score+15;
  Serial.println("WOW, Je hebt wel ");
  Serial.print(score);
  Serial.print(" punten, dat is bijna de high score  >---");
  Serial.print(highscore);
  Serial.print("---<");
  modus=0;
  leven=3;
  data=SAD;
      updateShiftRegister();
    music();

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Helaas");
lcd.setCursor(5,1);
lcd.print("D:");
delay(1500);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Je hebt al");
lcd.setCursor(0,1);
lcd.print("je levens");
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("verloren");
    delay(1500);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("je score is:");
lcd.setCursor(4,1);
lcd.print(score);
delay(1500);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Highscore is:");
lcd.setCursor(4,1);
lcd.print(score+3);
delay(1500);
  score=0;

}
  
 
  
  
  
  updateShiftRegister();
  }

  void updateShiftRegister()
{
   digitalWrite(LATCH, LOW);
   shiftOut(DATA, CLOCK, LSBFIRST, data);
   digitalWrite(LATCH, HIGH);
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(LEDR, red_light_value);
  analogWrite(LEDG, green_light_value);
  analogWrite(LEDB, blue_light_value);
}

void music(){
  for (int thisNote = 0; thisNote < songLength; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000/ durations[thisNote];
    tone(13, melody[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(13);
  }
}

void levelup(){
  lcd.clear();
  updateShiftRegister();
  lcd.setCursor(1,0);
lcd.print("-LEVEL UP-");
tone(13,NOTE_B2,500);
delay(400);
lcd.setCursor(1,0);
lcd.print("*LEVEL UP*");
delay(400);
lcd.setCursor(1,0);
lcd.print("|LEVEL UP|");
delay(400);
lcd.setCursor(1,0);
lcd.print("*LEVEL UP*");
delay(400);
lcd.setCursor(1,0);
lcd.print("-LEVEL UP-");
delay(400);
lcd.setCursor(1,0);
lcd.print("*LEVEL UP*");
delay(400);
lcd.setCursor(1,0);
lcd.print("|LEVEL UP|");
delay(400);
lcd.setCursor(1,0);
lcd.print("*LEVEL UP*");
tone(13,NOTE_A1,500);
delay(1000);
uplevel=true;
}
