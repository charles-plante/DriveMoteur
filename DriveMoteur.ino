#include "MoteurDrive.h"
#include "Arduino.h"

void doDynamicThing();

 Moteur A(10, 9, 8000, true);
 Moteur B(11, 12, 200, 50, 2000, true);



void setup()
{
    //Serial.begin(9600);

    A.setMinSpeed(64);
    A.setMaxSpeed(196);
}



void loop()
{
    doDynamicThing();

    //Serial.print("A : ");Serial.print(analogRead(A0));Serial.print(" B : ");Serial.println(analogRead(A1));
/*Test #1
if((millis() > 5000) && (!lock1))
{
    A.setSpeed(100, true);
    lock1 = true;
    Serial.println("L1!");
}
if((millis() > 10000) && (!lock2))
{
    A.setSpeed(0, true);
    lock2 = true;
    Serial.println("L2!");

}
if((millis() > 15000) && (!lock3))
{
    A.setSpeed(25, true);
    lock3 = true;
    Serial.println("L2!");
}
//*/
    A.setSpeed(map(analogRead(A0), 0, 1023, -100, 100), true);
    B.setSpeed(map(analogRead(A1), 0, 1023, -100, 100), true);

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
    B.doDyn();
}
