#include "LedControl.h"

LedControl lc=LedControl(12,11,10);  // Pin and # of Displays
unsigned long delayTime=1000;  // Delay between Frames
unsigned int LDR1;
int trigger_pin = 2;
int echo_pin = 3;
int time;
int distance; 
char bye[] = "Error, Kindly check the system";

// Put values in arrays
byte frameA[] =
{
   B00000000,
   B00000000,  // Dim Mode
   B00000000,
   B00011000,
   B00011000,
   B00000000,
   B00000000,
   B00000000
};

byte frameB[] =
{
   B00000000,
   B00000000,  // Off mode
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte frameC[] =
{
   B11111111,
   B11111111,  // Max mode
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111
};

byte frameD[] =
{
   B00000000,
   B00000000,  // Dim Mode
   B00111100,
   B00111100,
   B00111100,
   B00111100,
   B00000000,
   B00000000
};
void setup(){
  lc.shutdown(0,false);  // Wake up displays
  lc.setIntensity(0,0);  // Set intensity levels
  lc.clearDisplay(0);  // Clear Displays
  Serial.begin(9600);
  pinMode (trigger_pin, OUTPUT); 
  pinMode (echo_pin, INPUT);
}


//  Take values in Arrays and Display them
void modeA(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frameA[i]);
  }
}

void modeB(){
  for (int i = 0; i < 8; i++){
    lc.setRow(0,i,frameB[i]);
  }
}

void modeC(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frameC[i]);
  }
}

void modeD(){
  for (int i = 0; i < 8; i++)  {
    lc.setRow(0,i,frameD[i]);
  }
}

void loop(){
    digitalWrite (trigger_pin, HIGH);
    delayMicroseconds (10);
    digitalWrite (trigger_pin, LOW);
    time = pulseIn (echo_pin, HIGH);
    distance = (time * 0.034) / 2;
//Using LDR to detect light **SUN**
    LDR1 = analogRead(A1);
    Serial.println(LDR1);
    Serial.println(distance); 
    if(LDR1 <50) {
// Put #1 frame on both Display
      lc.setIntensity(0,0);
      modeB();
      delay(delayTime);
    }
    else if(LDR1 >= 1000 && distance > 100){
      // Put #1 frame on both Display
      lc.setIntensity(0,1);
      modeA();
      delay(delayTime);
    }
    else if(LDR1 >= 1000 && distance > 40 && distance <100){
      // Put #1 frame on both Display
      lc.setIntensity(0,1);
      modeD ();
      delay(delayTime);
    }
    else {
      lc.setIntensity(0,7);
      modeC();
      delay(delayTime);
    }

}
