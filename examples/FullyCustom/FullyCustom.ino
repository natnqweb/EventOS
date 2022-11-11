#define DEBUG
#include <EventOS.h>
//for example Custom mapping pins in esp8266

enum CustomVirtualPins : PinType
{
    VIRTUAL_PIN1,
    VIRTUAL_PIN2,
    TOTAL_NUMBER_OF_CUSTOM_PINS
};

PinMap customPinMap[TOTAL_NUMBER_OF_CUSTOM_PINS]
{
    // MERGE_PINS(REAL ACTUAL BOARD PIN,  YOUR VIRTUALPIN)
    MERGE_PINS(5, VIRTUAL_PIN1)
    MERGE_PINS(4, VIRTUAL_PIN2)
};

PinEvent customEvents[TOTAL_NUMBER_OF_CUSTOM_PINS]{};

void VPin1FallingEvent()
{
    LOGLN("pin 1 state changed from 1 to 0");
}

void VPin2FallingEvent()
{
    LOGLN("pin 2 state changed from 1 to 0");
}

__OVERRIDE void PROGRAM_SETUP(115200)
{
    ChangeEvents(customPinMap, customEvents, TOTAL_NUMBER_OF_CUSTOM_PINS);
    InitPinEvents();
    AddEventListener(VIRTUAL_PIN1, ON_FALLING_EDGE_EVENT, VPin1FallingEvent);
    AddEventListener(VIRTUAL_PIN2, ON_FALLING_EDGE_EVENT, VPin2FallingEvent);
    LOGLN("program started");
}

void PROGRAM_LOOP()
{

}
