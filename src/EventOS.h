#define ON_FALL_EVENT 0
#define ON_RAISE_EVENT 1
#define ON_CHANGE_EVENT 2

typedef void (*Event)(void);
void __EmptyFunction__() {}
struct PinMap { unsigned char pin, index; };

enum PinMapping
{
    _PIN_D2,
    _PIN_D3,
    _PIN_D4,
    _PIN_D5,
    _PIN_D6,
    _PIN_D7,
    _PIN_D8,
    _PIN_D9,
    _PIN_D10,
    _PIN_D11,
    _PIN_D12,
    _PIN_D13,
    NUMBER_OF_PINS // keep NUMBER_OF_PINS always at end of enum
};

static PinMap s_map[NUMBER_OF_PINS]
{
    // {actual hardware pin number, pin name used in code}
    {2,_PIN_D2},
    {3,_PIN_D3},
    {4,_PIN_D4},
    {5,_PIN_D5},
    {6,_PIN_D6},
    {7,_PIN_D7},
    {8,_PIN_D8},
    {9,_PIN_D9},
    {10,_PIN_D10},
    {11,_PIN_D11},
    {12,_PIN_D12},
    {13,_PIN_D13},
};

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

static void RunEventsOnPins(bool run = true)
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

static void AddEventListener(unsigned char pin, const char* strNameOfEvent, Event function)
{
    PinEvent& refEvent = s_events[pin];
    if (strNameOfEvent == "OnChange" || strNameOfEvent == "onchange")
    {
        refEvent.OnPinStateChange = function;
    }
    else if (strNameOfEvent == "OnRaise" || strNameOfEvent == "onraise")
    {
        refEvent.OnPinStateHigh = function;
    }
    else if (strNameOfEvent == "OnFall" || strNameOfEvent == "onfall")
    {
        refEvent.OnPinStateLow = function;
    }
}

static void TurnOffEventsOnPin(unsigned char pin, bool reset = false)
{
    s_events[pin].settings.bStopAll = !reset;
}

static void AddEventListener(unsigned char pin, int nNameOfEvent, Event function)
{
    PinEvent& refEvent = s_events[pin];
    switch (nNameOfEvent)
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
