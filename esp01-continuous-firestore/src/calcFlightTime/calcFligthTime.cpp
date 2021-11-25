#include <Arduino.h>

unsigned long getFlightTime(unsigned long inicialTime){
    unsigned long now = millis();
    unsigned long flight = now - inicialTime;
    return flight;
}