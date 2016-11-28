/*  This is used to drive a DC motor at different directions and speeds
 *  You can also add an acceleration and a deceleration for your design needs
 *  Two type of drive can be used : Mode 1 -> one pin for the direction
 *                                  Mode 2 -> each direction as a pin
 */
#include "Arduino.h"

 #ifndef _DRIVE_MOTOR
 #define _DRIVE_MOTOR


class Moteur
{
private:

  //used for control the Drive
    int m_pin1;
    int m_pin2;

    bool m_acc = false;//Are we using the acc fonction ?
    bool m_oneWireMode = false;//Reference for the kind of drive used (0 for two on off input PWM // 1 for 1PWM/1Direction )

    int m_speed = 0;//Steady speed of the motor
    int m_currentSpeed = 0;//Temporary speed

    //PWM output to drive motor
    int m_maxSpeed = 255;
    int m_minSpeed = 0;


    long long m_accTimer = 0;//Timing for delay control
    int m_cstTime = 4000; //One step each mS

    /*
    TODO :  
            2. Add a non-linear acceleration curve whit n points on an array
            3. Add different time for acceleration and deceleration
    */

public:
    Moteur();
    //Speed need to be a PWM pin & Direction stand for 0 = clockwise anything else = anti-clockwise  ***See next fonction***
    Moteur(int pin1, int pin2, bool mode = 0);
    Moteur(int pin1, int pin2, int time, bool mode = 0);
    Moteur(int pin1, int pin2, int max, int min, int time, bool mode = 0);

    void setSpeed(int vitesse, bool acc = false);
    void setMaxSpeed(int speed);
    void setMinSpeed(int speed);

    void doDyn();
    int m_map(int vitesse); //Transform % to PWM value on the motor range

    //Acces and setting
    int getSpeed();
    void setTimeCst(int time);

};

#endif
