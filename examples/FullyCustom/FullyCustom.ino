#define DEBUG
#include <EventOS.h>
// for this example Custom mapping pins in esp8266
// you can custom map any board as long as it is supported by arduino framework
// esp32 , esp8266 .. all arduino.. raspberrypi .. stm ... etc... 
static const ArrSizeType numberOfPins{ 2 };
PinType customPinMap[numberOfPins]
{
    //* REAL ACTUAL BOARD PIN - pin that you pass for example to digitalRead(REAL ACTUAL BOARD PIN)
    ADD_PIN(5)
    ADD_PIN(4)
};

// define PinEvent array it hold your events
PinEvent customEvents[numberOfPins]{};

void Pin5FallingEvent()
{
    LOG("pin 1 state changed from 1 to ");
    LOGLN(GetPinState(5));
}

void Pin4FallingEvent()
{
    LOG("pin 2 state changed from 1 to ");
    LOGLN(GetPinState(4));
}
// OVERRIDE DEFAULT PROGRAM_SETUP
__OVERRIDE void PROGRAM_SETUP(115200)
{
    // this ovverrides all default events with custom events
    ChangeEvents(customPinMap, customEvents, numberOfPins);

    //USER CODE
    //HERE ...
    AddEventListener(5, ON_FALLING_EDGE_EVENT, Pin5FallingEvent);
    AddEventListener(4, ON_FALLING_EDGE_EVENT, Pin4FallingEvent);
    LOGLN("program started");
}

void PROGRAM_LOOP()
{

}
