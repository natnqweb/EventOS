#ifndef EVENTS_OS
#define EVENTS_OS
#include "PinMapping.h"
#include "macros.h"
#define ON_FALLING_EDGE_EVENT 0
#define ON_RISING_EDGE_EVENT 1
#define ON_CHANGE_EVENT 2
struct __set_override_flag
{
    __set_override_flag(int i = 0);
};
typedef void (*Event)(void);
void __EmptyFunction__();

struct RunEventSettings
{
    bool bEventOnPinStateChange = false;
    bool bEventOnPinSetLow = false;
    bool bEventOnPinSetHigh = false;
    bool bLastButtonState = true;
    bool bStopAll = true;
};

struct PinEvent
{
    PinType pin = 2;
    Event OnPinStateChange = __EmptyFunction__;
    Event OnPinStateHigh = __EmptyFunction__;
    Event OnPinStateLow = __EmptyFunction__;
    bool bLastPinState = true;
    RunEventSettings settings{};
};

void InitPinEvents();
void ChangeEvents(PinMap* pinMapping, PinEvent* newEvents, IndexType numberOfNewEvents);
void RunEventsOnPins(bool run = true);
void TurnOffEventsOnPin(PinType pin, bool reset = false);
void AddEventListener(PinType pin, int nEventType, Event function);
const bool& GetPinState(PinType pin);
void ShutDownEventOS();
void TurnOnEventOS();
const bool& __GetInitOverride();
void __SetInitOverride();
const bool& __GetOverrideMacroMappingUsedFlag();
const bool& IsEventOSTurnedOff();

#endif
