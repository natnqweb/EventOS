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

#define OVERRIDE_PINMAPPING_START PinType s_overrideCustomPinMap[]{
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
const ArrSizeType s_overrideArrSize = sizeof(s_overrideCustomPinMap)/sizeof(s_overrideCustomPinMap[0]); \
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
const ArrSizeType s_overrideArrSize = sizeof(s_overrideCustomPinMap)/sizeof(s_overrideCustomPinMap[0]); \
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