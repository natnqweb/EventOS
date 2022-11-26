#define DEBUG
#include <EventOS.h>
// program notify user when pin 2 is changing state from high to low while blinking led at the same time
// Arduino Uno
const unsigned char ledPin = LED_BUILTIN;
unsigned long lastMillis = 0;
const unsigned long interval = 1000;
bool ledState = false;
void BlinkLED()
{
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
}

void LogChangedToLow()
{
    LOGLN("Pin 2 State Changed from High to Low");
}

void LogMessageAndValue(const char* msg, int val)
{
    LOG(msg);
    LOG(' ');
    LOGLN(val);
}

void PROGRAM_SETUP(115200)
{
    pinMode(ledPin, OUTPUT);
    AddEventListener(2, ON_FALLING_EDGE_EVENT, LogChangedToLow);
}

void PROGRAM_LOOP()
{
    if (millis() - lastMillis >= interval)
    {
        // execution every interval [ms]
        lastMillis = millis();
        BlinkLED();
        LogMessageAndValue("led state changed to:", (int)ledState);
    }

}