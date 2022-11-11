#define DEBUG
#include <EventOS.h>
// for this example Custom mapping pins in esp8266
// you can custom map any board as long as it is supported by arduino framework
// esp32 , esp8266 .. all arduino.. raspberrypi .. stm ... etc... 


// define your custom virtual pins to use them later in program
enum CustomVirtualPins : PinType
{
    VIRTUAL_PIN1,
    VIRTUAL_PIN2,
    TOTAL_NUMBER_OF_CUSTOM_PINS
};

//map real pins and virtual pins together
PinMap customPinMap[TOTAL_NUMBER_OF_CUSTOM_PINS]
{
    // MERGE_PINS(REAL ACTUAL BOARD PIN,  YOUR VIRTUALPIN)
    //* REAL ACTUAL BOARD PIN - pin that you pass for example to digitalRead(REAL ACTUAL BOARD PIN)
    MERGE_PINS(5, VIRTUAL_PIN1)
    MERGE_PINS(4, VIRTUAL_PIN2)
};

// define PinEvent array it hold your events
PinEvent customEvents[TOTAL_NUMBER_OF_CUSTOM_PINS]{};

void VPin1FallingEvent()
{
    LOG("pin 1 state changed from 1 to ");
    LOGLN(GetPinState(VIRTUAL_PIN1));
}

void VPin2FallingEvent()
{
    LOG("pin 2 state changed from 1 to ");
    LOGLN(GetPinState(VIRTUAL_PIN2));
}
// OVERRIDE DEFAULT PROGRAM_SETUP
__OVERRIDE void PROGRAM_SETUP(115200)
{
    // this ovverrides all default events with custom events
    ChangeEvents(customPinMap, customEvents, TOTAL_NUMBER_OF_CUSTOM_PINS);
    // Init PinEvents after you changed to your custom events
    InitPinEvents();

    //USER CODE
    //HERE ...
    AddEventListener(VIRTUAL_PIN1, ON_FALLING_EDGE_EVENT, VPin1FallingEvent);
    AddEventListener(VIRTUAL_PIN2, ON_FALLING_EDGE_EVENT, VPin2FallingEvent);
    LOGLN("program started");
}

void PROGRAM_LOOP()
{

}
