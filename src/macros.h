#pragma once
#ifdef DEBUG
#define LOGLN(X) Serial.println(X)
#define LOG(X) Serial.print(X)
#define SETUP_START(BAUDRATE)\
 void setup()\
 {\
 Serial.begin(BAUDRATE);\
 InitPinEvents();
#else
#define LOGLN(X)
#define LOG(X)
#define SETUP_START(BAUDRATE)\
 void setup()\
 {\
  InitPinEvents();
#endif

#define SETUP_END }

#define LOOP_START void loop(){\
  RunEventsOnPins();
#define LOOP_END }