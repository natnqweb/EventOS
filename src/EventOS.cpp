#include <Arduino.h>
#define EVENT_OS
#include "EventOS.h"
void __EmptyFunction__() {}

#ifdef EVENT_OS_OFF
static bool s_bShutdown{ true };
#else
static bool s_bShutdown{ false };
#endif // EVENT_OS_OFF
static PinEvent* s_pEvents = nullptr;
static PinType* s_pMap = s_map;
static ArrSizeType s_numberOfPins = 0;
static bool s_bInitialized = false;
static bool s_bInitOverride = false;
static bool s_bOverrideMacroMappingUsed = false;

__set_override_flag::__set_override_flag(int i)
{
    __SetInitOverride();
    if (i > 0)
        s_bOverrideMacroMappingUsed = true;
}

void __SetInitOverride()
{
    s_bInitOverride = true;
}

const bool& __GetOverrideMacroMappingUsedFlag()
{
    return s_bOverrideMacroMappingUsed;
}

const bool& __GetInitOverride()
{
    return s_bInitOverride;
}

bool GetPinState(PinType pin)
{
    bool bPinState = false;
    for (ArrSizeType i = 0; i < s_numberOfPins; i++)
    {
        PinEvent& event = s_pEvents[i];
        if (event.pin == pin)
        {
            bPinState = event.bLastPinState;
            break;
        }
    }
    return bPinState;
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

    if (!__GetInitOverride())
    {
        s_pEvents = new PinEvent[_SIZE_OF_PIN_ARRAY]{};
        s_numberOfPins = _SIZE_OF_PIN_ARRAY;
    }

    for (ArrSizeType i = 0; i < s_numberOfPins; i++)
    {
        PinType& pin = s_pMap[i];
        PinEvent& event = s_pEvents[i];
        event.pin = pin;
        pinMode(pin, INPUT_PULLUP);
        event.bLastPinState = digitalRead(pin);
    }

    s_bInitialized = true;
}

void ChangeEvents(PinType* pinArray, PinEvent* newEvents, ArrSizeType numberOfNewEvents)
{
    s_pMap = pinArray;
    s_numberOfPins = numberOfNewEvents;
    s_pEvents = newEvents;
    InitPinEvents();
}

void RunEventsOnPins(bool run)
{
    for (ArrSizeType i = 0; (run && i < s_numberOfPins); i++)
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
    for (ArrSizeType i = 0; i < s_numberOfPins; i++)
    {
        auto& event = s_pEvents[i];
        if (event.pin == pin)
        {
            event.settings.bStopAll = !reset;
            break;
        }
    }
}

void AddEventListener(PinType pin, int eventType, Event function)
{
    for (ArrSizeType i = 0; i < s_numberOfPins; i++)
    {
        auto& refEvent = s_pEvents[i];
        if (refEvent.pin == pin)
        {
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
            break;
        }
    }
}
