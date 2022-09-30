#include <Arduino.h>
#define EVENT_OS
#include "EventOS.h"
void __EmptyFunction__() {}

static PinEvent s_events[NUMBER_OF_PINS]{};

void InitPinEvents()
{
    for (unsigned char i = 0; i < NUMBER_OF_PINS; i++)
    {
        int index = s_map[i].index;
        unsigned char pin = s_map[i].pin;
        PinEvent& event = s_events[index];
        event.pin = pin;
        pinMode(pin, INPUT_PULLUP);
        event.bLastPinState = digitalRead(pin);
    }
}

void RunEventsOnPins(bool run)
{
    for (unsigned char i = 0; (run && i < NUMBER_OF_PINS); i++)
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

            if (pinState && event.settings.bEventOnPinSetHigh)
                event.OnPinStateHigh();
            else if (!pinState && event.settings.bEventOnPinSetLow)
                event.OnPinStateLow();
        }
    }
}

void TurnOffEventsOnPin(unsigned char pin, bool reset)
{
    s_events[pin].settings.bStopAll = !reset;
}

void AddEventListener(unsigned char pin, int eventType, Event function)
{
    PinEvent& refEvent = s_events[pin];
    switch (eventType)
    {
        case ON_CHANGE_EVENT:
            refEvent.OnPinStateChange = function;
            break;
        case ON_RAISE_EVENT:
            refEvent.OnPinStateHigh = function;
            break;
        case ON_FALL_EVENT:
            refEvent.OnPinStateLow = function;

        default:
            break;
    }
}
