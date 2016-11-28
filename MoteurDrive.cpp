/***************************************
* Classe qui s'occupe de faire la gestion d'un moteur
* Ecrit le 23 Novenvre 2026
* Charles Plante-Veillette
* Version 1
* For this code to work you must prohibit delay() fct anywhere or the dynamic will glitch
*/

#include "MoteurDrive.h"

Moteur::Moteur(){}

Moteur::Moteur(int pin1, int pin2, bool mode)
{
    //Set the pin as output
    m_pin1 = pin1;
    m_pin2 = pin2;
    pinMode(m_pin1, OUTPUT);
    pinMode(m_pin2, OUTPUT);

    m_oneWireMode = mode;

}
Moteur::Moteur(int pin1, int pin2, int time, bool mode)
{
    //Set the pin as output
    m_pin1 = pin1;
    m_pin2 = pin2;
    pinMode(m_pin1, OUTPUT);
    pinMode(m_pin2, OUTPUT);

    m_cstTime = time;
    m_oneWireMode = mode;
}
Moteur::Moteur(int pin1, int pin2, int max, int min, int time, bool mode)
{
    m_pin1 = pin1;
    m_pin2 = pin2;
    pinMode(m_pin1, OUTPUT);
    pinMode(m_pin2, OUTPUT);

    m_cstTime = time;
    m_oneWireMode = mode;
    m_minSpeed = min;
    m_maxSpeed = max;
}
void Moteur::setSpeed(int vitesse, bool acc)
{
    m_acc = acc;
    if(m_acc == 0)//If we dont use accleration
    {
        m_speed = m_currentSpeed = vitesse;
        //detect if used in mode 1 or 2
        if (m_oneWireMode)
        {
            if(m_speed > 0)//Front rotation
            {
                analogWrite(m_pin1, m_map(m_speed));
                digitalWrite(m_pin2, HIGH);//Subject to change
            }
            else if(m_speed < 0)//Back rotation
            {
                analogWrite(m_pin1, m_map(m_speed));
                digitalWrite(m_pin2, LOW);//Subject to change
            }
            else    //Stop the motor
            {
                analogWrite(m_pin1, 0);
                digitalWrite(m_pin2, LOW);
            }
        }
        else
        {
            if(m_speed > 0)
            {

                analogWrite(m_pin1, m_speed);
                digitalWrite(m_pin2, LOW);
            }
            else if(m_speed < 0)
            {
                digitalWrite(m_pin1, LOW);
                analogWrite(m_pin2, abs(m_speed));
            }
            else
            {
                digitalWrite(m_pin1, LOW);
                digitalWrite(m_pin2, LOW);
            }
        }
    }
    else
    {
        m_speed = vitesse;
        doDyn();
    }

}

void Moteur::doDyn()
{
    //If acceleration is not used or if timer is not reached : return
    if((!m_acc) || (micros() < m_accTimer) || (m_currentSpeed == m_speed))
        return;

    //Increase of decrease the speed toward goal
    if(m_currentSpeed < m_speed)
        m_currentSpeed++;

    else if(m_currentSpeed > m_speed)
        m_currentSpeed--;

    //Check wich mode is used and send change PWM to the pin
    if(m_oneWireMode)
    {
        analogWrite(m_pin1, m_map(m_currentSpeed));
        if(m_currentSpeed > 0)
            digitalWrite(m_pin2, HIGH);
        else
            digitalWrite(m_pin2,LOW);
    }
    else
    {
        if(m_currentSpeed > 0)
        {
            analogWrite(m_pin1, m_map(m_currentSpeed));
            digitalWrite(m_pin2, LOW);
        }
        else if(m_currentSpeed < 0)
        {
            digitalWrite(m_pin1, LOW);
            analogWrite(m_pin2, m_map(m_currentSpeed));
        }
        else
        {
            digitalWrite(m_pin1, LOW);
            digitalWrite(m_pin2, LOW);
        }
    }

    m_accTimer = micros() + m_cstTime;//Refresh the acceleration time interval
}
int Moteur::getSpeed()              {   return m_currentSpeed;}
void Moteur::setMaxSpeed(int speed) {   m_maxSpeed = speed;}
void Moteur::setMinSpeed(int speed) {   m_minSpeed = speed;}
void Moteur::setTimeCst(int time)   {   m_cstTime = time;}

int Moteur::m_map(int vitesse)
{
    /* This function convert a % value to the range of the motor */
    if(vitesse == 0)
        return 0;
    else if(vitesse > 0)
        return  map(vitesse, 1, 100, m_minSpeed, m_maxSpeed);
    else
        return map(vitesse, -1, -100, m_minSpeed, m_maxSpeed);
}
