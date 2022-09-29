#pragma once
#include "PinMapping.h"
#include "macros.h"
#define ON_FALL_EVENT 0
#define ON_RAISE_EVENT 1
#define ON_CHANGE_EVENT 2

typedef void (*Event)(void);
void __EmptyFunction__();

struct RunEventSettings
{
    bool bEventOnPinStateChange = true;
    bool bEventOnPinSetLow = true;
    bool bEventOnPinSetHigh = true;
    bool bLastButtonState = true;
    bool bStopAll = false;
};

struct PinEvent
{
    unsigned char pin = 2;
    Event OnPinStateChange = __EmptyFunction__;
    Event OnPinStateHigh = __EmptyFunction__;
    Event OnPinStateLow = __EmptyFunction__;
    bool bLastPinState = true;
    RunEventSettings settings{};
};

void InitPinEvents();
void RunEventsOnPins(bool run = true);
void TurnOffEventsOnPin(unsigned char pin, bool reset = false);
void AddEventListener(unsigned char pin, int nEventType, Event function);
