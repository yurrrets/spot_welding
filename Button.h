#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

#define CLICK 0x80

class Button
{
public:
    Button(int pin);
    void setup();
    void loop();
    uint8_t getVal(){ return currVal; }
private:
    int pin;
    uint8_t currVal;
    unsigned long prevTime;
};

#endif // BUTTON_H
