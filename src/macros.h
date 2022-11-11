#ifndef MACROS_H
#define MACROS_H
#define __UNUSED_OBJ(X)
#define __CREATE_OVERRIDE_OBJ __set_override_flag __override_flag{};
#define __IGNORE_UNUSED_OVERRIDE_OBJ __UNUSED_OBJ(__override_flag);
#define __OVERRIDE __CREATE_OVERRIDE_OBJ  __IGNORE_UNUSED_OVERRIDE_OBJ

#ifdef DEBUG // DEBUG
#define LOGLN(X) Serial.println(X)
#define LOG(X) Serial.print(X)

#define PROGRAM_SETUP(BAUDRATE) \
ProgramInit(); \
void setup() \
{\
Serial.begin(BAUDRATE); \
if(!__GetInitOverride()) \
    InitPinEvents();\
 ProgramInit();\
} \
void ProgramInit()

#else// NOT DEBUG

#define LOGLN(X)
#define LOG(X)

#define PROGRAM_SETUP(BAUDRATE) \
ProgramInit(); \
void setup() \
{ \
if (!__GetInitOverride()) \
InitPinEvents();\
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