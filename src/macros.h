#pragma once
#ifdef DEBUG // DEBUG
#define LOGLN(X) Serial.println(X)
#define LOG(X) Serial.print(X)

#define PROGRAM_SETUP(BAUDRATE) void ProgramInit(); \
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

#define PROGRAM_SETUP(BAUDRATE) void ProgramInit(); \
void setup() \
{\
 InitPinEvents();\
 ProgramInit();\
} \
void ProgramInit()

#endif // DEBUG

#define PROGRAM_LOOP() \
void RunInLoop(); \
void loop() \
{ \
RunEventsOnPins(); \
RunInLoop(); \
} \
void RunInLoop()
