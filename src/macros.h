#pragma once
#ifdef DEBUG // DEBUG
#define LOGLN(X) Serial.println(X)
#define LOG(X) Serial.print(X)

#define PROGRAM_SETUP(BAUDRATE) ProgramInit(); \
void setup() \
{\
 Serial.begin(BAUDRATE);\
 InitPinEvents();\
 ProgramInit();\
} \
void ProgramInit()

#else// NOT DEBUG

#define LOGLN(X)
#define LOG(X)

#define PROGRAM_SETUP(BAUDRATE) ProgramInit(); \
void setup() \
{\
 InitPinEvents();\
 ProgramInit();\
} \
void ProgramInit()

#endif // DEBUG
#define SHUTDOWN_EVENT_OS s_bShutdown
#define PROGRAM_LOOP() \
RunInLoop(); \
void loop() \
{ \
RunEventsOnPins(!SHUTDOWN_EVENT_OS); \
RunInLoop(); \
} \
void RunInLoop()

#define TURN_OFF_EVENT_OS() SHUTDOWN_EVENT_OS = true
#define TURN_ON_EVENT_OS() SHUTDOWN_EVENT_OS = false
