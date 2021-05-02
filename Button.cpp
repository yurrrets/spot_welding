#include "Button.h"

Button::Button(int pin)
    :pin(pin)
{

}

void Button::setup()
{
    pinMode(pin,INPUT_PULLUP);
    prevTime=millis();
}

void Button::loop()
{
    uint8_t val=digitalRead(pin);

    currVal &=~CLICK;

    if (currVal==val)
        prevTime=millis();
    else{
        if (val==HIGH &&
            millis()-prevTime>100){
            // button released
            currVal=val;
        }
        if (val==LOW &&
            millis()-prevTime>10){
            // button pressed
            currVal=val | CLICK;
        }
    }
}

