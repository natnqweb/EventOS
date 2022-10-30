#ifndef PIN_MAPPING
#define PIN_MAPPING
#ifdef ESP8266
#define _IS8266 true
#else
#define _IS8266 false
#endif
#ifdef ESP32 
#define _IS32 true
#else
#define _IS32 false
#endif
#ifdef UNO
#define _ISUNO true
#else
#define _ISUNO false
#endif
typedef unsigned char PinType;
typedef PinType IndexType;
#include "MappingMacro.h"

START_MAPPING_DECLARATION
#if _IS8266 || _ISUNO || _IS32
#ifdef ESP8266
_PIN_D1,
_PIN_D2,
_PIN_D5,
_PIN_D6,
_PIN_D7,
#endif
#ifdef ESP32
_PIN_D4,
_PIN_D5,
_PIN_D13,
_PIN_D14,
_PIN_D15,
_PIN_D16,
_PIN_D17,
_PIN_D18,
_PIN_D19,
_PIN_D21,
_PIN_D22,
_PIN_D23,
_PIN_D25,
_PIN_D26,
_PIN_D27,
_PIN_D32,
_PIN_D33,
_PIN_D34,
_PIN_D35,
_PIN_D36,
_PIN_D39,
#endif
#ifdef UNO
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
#endif
#else // otherboard than esp8266 uno or esp32
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
#endif
END_MAPPING_DECLARATION

#ifdef EVENT_OS
START_MAPPING_DEFINITION
#if _IS8266 || _ISUNO || _IS32
// Merge (actual hardware pin number, pin name used in code)
// connecting real pins with virtual pins
#ifdef ESP8266
MERGE_PINS(D1, _PIN_D1)
MERGE_PINS(D2, _PIN_D2)
MERGE_PINS(D5, _PIN_D5)
MERGE_PINS(D6, _PIN_D6)
MERGE_PINS(D7, _PIN_D7)
#endif
#ifdef ESP32
MERGE_PINS(4, _PIN_4)
MERGE_PINS(5, _PIN_5)
MERGE_PINS(13, _PIN_13)
MERGE_PINS(14, _PIN_14)
MERGE_PINS(15, _PIN_15)
MERGE_PINS(16, _PIN_16)
MERGE_PINS(17, _PIN_17)
MERGE_PINS(18, _PIN_18)
MERGE_PINS(19, _PIN_19)
MERGE_PINS(21, _PIN_21)
MERGE_PINS(22, _PIN_22)
MERGE_PINS(23, _PIN_23)
MERGE_PINS(25, _PIN_25)
MERGE_PINS(26, _PIN_26)
MERGE_PINS(27, _PIN_27)
MERGE_PINS(32, _PIN_32)
MERGE_PINS(33, _PIN_33)
MERGE_PINS(34, _PIN_34)
MERGE_PINS(35, _PIN_35)
MERGE_PINS(36, _PIN_36)
MERGE_PINS(39, _PIN_39)
#endif
#ifdef UNO
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
#endif
#else
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
#endif
END_MAPPING_DEFINITION

#endif // EVENT_OS

#endif // PIN_MAPPING