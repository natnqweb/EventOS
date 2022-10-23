#include <Arduino.h>
#define EVENT_OS
#include "EventOS.h"
void __EmptyFunction__() {}

static PinEvent s_events[NUMBER_OF_PINS]{};

void InitPinEvents()
{
    for (IndexType i = 0; i < NUMBER_OF_PINS; i++)
    {
        IndexType index = s_map[i].index;
        PinType pin = s_map[i].pin;
        PinEvent& event = s_events[index];
        event.pin = pin;
        pinMode(pin, INPUT_PULLUP);
        event.bLastPinState = digitalRead(pin);
    }
}

void RunEventsOnPins(bool run)
{
    for (IndexType i = 0; (run && i < NUMBER_OF_PINS); i++)
    {
        PinEvent& event = s_events[i];
        if (event.settings.bStopAll)
            continue;

        bool pinState = digitalRead(event.pin);
        if (pinState != event.bLastPinState)
        {
            event.bLastPinState = pinState;

            if (event.settings.bEventOnPinStateChange)
                event.OnPinStateChange();

            if (event.settings.bEventOnPinSetHigh && pinState)
                event.OnPinStateHigh();
            else if (event.settings.bEventOnPinSetLow && !pinState)
                event.OnPinStateLow();
        }
    }
}

void TurnOffEventsOnPin(PinType pin, bool reset)
{
    s_events[pin].settings.bStopAll = !reset;
}

void AddEventListener(PinType pin, int eventType, Event function)
{
    PinEvent& refEvent = s_events[pin];
    switch (eventType)
    {
        case ON_CHANGE_EVENT:
            refEvent.OnPinStateChange = function;
            refEvent.settings.bEventOnPinStateChange = true;
            break;
        case ON_RISING_EDGE_EVENT:
            refEvent.OnPinStateHigh = function;
            refEvent.settings.bEventOnPinSetHigh = true;
            break;
        case ON_FALLING_EDGE_EVENT:
            refEvent.OnPinStateLow = function;
            refEvent.settings.bEventOnPinSetLow = true;
        default:
            break;
    }

    refEvent.settings.bStopAll = false;

}
