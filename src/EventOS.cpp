#include <Arduino.h>
#define EVENT_OS
#include "EventOS.h"
void __EmptyFunction__() {}

#ifdef EVENT_OS_OFF
static bool s_bShutdown{ true };
#else
static bool s_bShutdown{ false };
#endif // EVENT_OS_OFF

static PinEvent s_events[NUMBER_OF_PINS]{};
static PinEvent* s_pEvents = s_events;
static PinMap* s_pMap = s_map;
static IndexType s_numberOfPins = NUMBER_OF_PINS;
static bool s_bInitialized = false;
static bool s_bInitOverride = false;
__set_override_flag::__set_override_flag()
{
    __SetInitOverride();
}
void __SetInitOverride()
{
    s_bInitOverride = true;
}
const bool& __GetInitOverride()
{
    return s_bInitOverride;
}
const bool& GetPinState(PinType pin)
{
    return s_pEvents[pin].bLastPinState;
}

void ShutDownEventOS()
{
    s_bShutdown = true;
}

void TurnOnEventOS()
{
    s_bShutdown = false;
}

const bool& IsEventOSTurnedOff()
{
    return s_bShutdown;
}

void InitPinEvents()
{
    if (s_bInitialized)
        return;

    for (IndexType i = 0; i < s_numberOfPins; i++)
    {
        IndexType index = s_pMap[i].index;
        PinType pin = s_pMap[i].pin;
        PinEvent& event = s_pEvents[index];
        event.pin = pin;
        pinMode(pin, INPUT_PULLUP);
        event.bLastPinState = digitalRead(pin);
    }

    s_bInitialized = true;
}

void ChangeEvents(PinMap* pinMapping, PinEvent* newEvents, IndexType numberOfNewEvents)
{
    s_pMap = pinMapping;
    s_numberOfPins = numberOfNewEvents;
    s_pEvents = newEvents;
    InitPinEvents();
}

void RunEventsOnPins(bool run)
{

    for (IndexType i = 0; (run && i < s_numberOfPins); i++)
    {
        PinEvent& event = s_pEvents[i];
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
    s_pEvents[pin].settings.bStopAll = !reset;
}

void AddEventListener(PinType pin, int eventType, Event function)
{
    PinEvent& refEvent = s_pEvents[pin];
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
