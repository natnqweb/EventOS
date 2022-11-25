#ifndef MACROS_H
#define MACROS_H
#define __UNUSED_OBJ(X)
#define __CREATE_OVERRIDE_OBJ __set_override_flag __override_flag{};
#define __IGNORE_UNUSED_OVERRIDE_OBJ __UNUSED_OBJ(__override_flag);
#define __OVERRIDE __CREATE_OVERRIDE_OBJ  __IGNORE_UNUSED_OVERRIDE_OBJ

#define __OVERRIDE_MACRO_USED 2
#define __CREATE_OVERRIDE_OBJ2 __set_override_flag __override_flag2{__OVERRIDE_MACRO_USED};
#define __IGNORE_UNUSED_OVERRIDE_OBJ2 __UNUSED_OBJ(__override_flag2);
#define __OVERRIDE_MAPPING_HIDDEN __CREATE_OVERRIDE_OBJ2  __IGNORE_UNUSED_OVERRIDE_OBJ2

#define CREATE_VIRTUAL_PINS_TABLE_DEFAULT enum OVERRIDE_CustomVirtualPins : PinType \
{ \
VIRTUAL_PIN1,\
VIRTUAL_PIN2,\
VIRTUAL_PIN3,\
VIRTUAL_PIN4,\
VIRTUAL_PIN5,\
VIRTUAL_PIN6,\
VIRTUAL_PIN7,\
VIRTUAL_PIN8,\
VIRTUAL_PIN9,\
VIRTUAL_PIN10,\
VIRTUAL_PIN11,\
VIRTUAL_PIN12,\
VIRTUAL_PIN13,\
VIRTUAL_PIN14,\
VIRTUAL_PIN15,\
VIRTUAL_PIN16,\
VIRTUAL_PIN17,\
VIRTUAL_PIN18,\
VIRTUAL_PIN19,\
VIRTUAL_PIN20,\
VIRTUAL_PIN21,\
VIRTUAL_PIN22,\
VIRTUAL_PIN23,\
VIRTUAL_PIN24,\
VIRTUAL_PIN25,\
VIRTUAL_PIN26,\
VIRTUAL_PIN27,\
VIRTUAL_PIN28,\
VIRTUAL_PIN29,\
VIRTUAL_PIN30,\
VIRTUAL_PIN31,\
VIRTUAL_PIN32,\
VIRTUAL_PIN33,\
VIRTUAL_PIN34,\
VIRTUAL_PIN35,\
VIRTUAL_PIN36,\
VIRTUAL_PIN37,\
VIRTUAL_PIN38,\
VIRTUAL_PIN39,\
VIRTUAL_PIN40,\
VIRTUAL_PIN41,\
VIRTUAL_PIN42,\
VIRTUAL_PIN43,\
VIRTUAL_PIN44,\
VIRTUAL_PIN45,\
VIRTUAL_PIN46,\
VIRTUAL_PIN47,\
VIRTUAL_PIN48,\
VIRTUAL_PIN49,\
VIRTUAL_PIN50,\
};

#define OVERRIDE_PINMAPPING_START CREATE_VIRTUAL_PINS_TABLE_DEFAULT PinMap s_overrideCustomPinMap[]{
#define OVERRIDE_PINMAPPING_END }; __OVERRIDE_MAPPING_HIDDEN \
PinEvent* s_overrideCustomEvents{nullptr};

#ifdef DEBUG // DEBUG
#define LOGLN(X) Serial.println(X)
#define LOG(X) Serial.print(X)


#define PROGRAM_SETUP_AUTO(BAUDRATE) \
ProgramInit(); \
void setup() \
{ \
Serial.begin(BAUDRATE);\
if (!__GetInitOverride() && !__GetOverrideMacroMappingUsedFlag()) \
    InitPinEvents(); \
else if(__GetInitOverride() && __GetOverrideMacroMappingUsedFlag()) \
{ \
const size_t s_overrideArrSize = sizeof(s_overrideCustomPinMap)/sizeof(s_overrideCustomPinMap[0]); \
s_overrideCustomEvents = new PinEvent[s_overrideArrSize]{}; \
ChangeEvents(s_overrideCustomPinMap, s_overrideCustomEvents, s_overrideArrSize); \
InitPinEvents(); \
} \
ProgramInit();\
} \
void ProgramInit()

#define PROGRAM_SETUP(BAUDRATE) \
ProgramInit(); \
void setup() \
{ \
Serial.begin(BAUDRATE);\
if (!__GetInitOverride()) \
    InitPinEvents(); \
ProgramInit();\
} \
void ProgramInit()

#else// NOT DEBUG

#define LOGLN(X)
#define LOG(X)

#define PROGRAM_SETUP_AUTO(BAUDRATE) \
ProgramInit(); \
void setup() \
{ \
if(!__GetInitOverride() && !__GetOverrideMacroMappingUsedFlag()) \
    InitPinEvents(); \
else if(__GetInitOverride() && __GetOverrideMacroMappingUsedFlag()) \
{ \
const size_t s_overrideArrSize = sizeof(s_overrideCustomPinMap)/sizeof(s_overrideCustomPinMap[0]); \
s_overrideCustomEvents = new PinEvent[s_overrideArrSize]{}; \
ChangeEvents(s_overrideCustomPinMap, s_overrideCustomEvents, s_overrideArrSize); \
InitPinEvents(); \
} \
ProgramInit();\
} \
void ProgramInit()

#define PROGRAM_SETUP(BAUDRATE) \
ProgramInit(); \
void setup() \
{ \
if(!__GetInitOverride()) \
    InitPinEvents(); \
ProgramInit();\
} \
void ProgramInit()

#endif // DEBUG
#define SHUTDOWN_EVENT_OS IsEventOSTurnedOff()
#define PROGRAM_LOOP() \
RunInLoop(); \
void loop() \
{ \
RunEventsOnPins(!SHUTDOWN_EVENT_OS); \
RunInLoop(); \
} \
void RunInLoop()

#define TURN_OFF_EVENT_OS() ShutDownEventOS()
#define TURN_ON_EVENT_OS() TurnOnEventOS()

#endif // MACROS_H