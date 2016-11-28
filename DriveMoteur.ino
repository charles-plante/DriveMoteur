#include "MoteurDrive.h"
#include "Arduino.h"

void doDynamicThing();

 Moteur A(10, 9, 4000, true);
Moteur B(11, 12, 2000, true);



void setup() {
  //Serial.begin(9600);
/*
A.setSpeed(255, false);
A.setSpeed(-255, true);
B.setSpeed(0, false);
B.setSpeed(255, true);
//*/

}

void loop()
{
    doDynamicThing();

//    Serial.print("A : ");Serial.print(analogRead(A0));Serial.print(" B : ");Serial.println(analogRead(A1));
//A = 528 B = 522

    A.setSpeed(map(analogRead(A0), 0, 1023, -255, 255), true);
    B.setSpeed(map(analogRead(A1), 0, 1023, -255, 255), true);
/* For debug
    if(A.getSpeed() == -255)
        A.setSpeed(255, true);
    else if(A.getSpeed() == 255)
        A.setSpeed(-255, true);

    if(B.getSpeed() == -128)
        B.setSpeed(128, true);
    else if(B.getSpeed() == 128)
        B.setSpeed(-128, true);
//*/




}
void doDynamicThing()
{
    A.doDyn();
//    B.doDyn();
}
