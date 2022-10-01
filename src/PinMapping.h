#ifndef PIN_MAPPING
#define PIN_MAPPING _PINMAPPING

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

#ifdef EVENT_OS
static const PinMap s_map[NUMBER_OF_PINS]
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
#endif // EVENT_OS

#endif // PIN_MAPPING