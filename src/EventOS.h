#ifndef EVENTS_OS
#define EVENTS_OS
#include "PinMapping.h"
#include "macros.h"
#define ON_FALLING_EDGE_EVENT 0
#define ON_RISING_EDGE_EVENT 1
#define ON_CHANGE_EVENT 2

typedef void (*Event)(void);
void __EmptyFunction__();

#ifndef EVENT_OS
#ifdef EVENT_OS_OFF
static bool s_bShutdown{ true };
#else
static bool s_bShutdown{ false };
#endif
#endif

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
void RunEventsOnPins(bool run = true);
void TurnOffEventsOnPin(PinType pin, bool reset = false);
void AddEventListener(PinType pin, int nEventType, Event function);
#endif
