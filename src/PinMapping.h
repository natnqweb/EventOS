#ifndef PIN_MAPPING
#define PIN_MAPPING

typedef unsigned char PinType;
typedef PinType IndexType;
#include "MappingMacro.h"

START_MAPPING_DECLARATION

ADD_PIN_TO_MAP(_PIN_D2)
ADD_PIN_TO_MAP(_PIN_D3)
ADD_PIN_TO_MAP(_PIN_D4)
ADD_PIN_TO_MAP(_PIN_D5)
ADD_PIN_TO_MAP(_PIN_D6)
ADD_PIN_TO_MAP(_PIN_D7)
ADD_PIN_TO_MAP(_PIN_D8)
ADD_PIN_TO_MAP(_PIN_D9)
ADD_PIN_TO_MAP(_PIN_D10)
ADD_PIN_TO_MAP(_PIN_D11)
ADD_PIN_TO_MAP(_PIN_D12)
ADD_PIN_TO_MAP(_PIN_D13)

END_MAPPING_DECLARATION

#ifdef EVENT_OS

START_MAPPING_DEFINITION
// Merge (actual hardware pin number, pin name used in code)
// connecting real pins with virtual pins
MERGE_PINS(2, _PIN_D2)
MERGE_PINS(3, _PIN_D3)
MERGE_PINS(4, _PIN_D4)
MERGE_PINS(5, _PIN_D5)
MERGE_PINS(6, _PIN_D6)
MERGE_PINS(7, _PIN_D7)
MERGE_PINS(8, _PIN_D8)
MERGE_PINS(9, _PIN_D9)
MERGE_PINS(10, _PIN_D10)
MERGE_PINS(11, _PIN_D11)
MERGE_PINS(12, _PIN_D12)
MERGE_PINS(13, _PIN_D13)

END_MAPPING_DEFINITION

#endif // EVENT_OS

#endif // PIN_MAPPING