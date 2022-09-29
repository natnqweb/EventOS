// ===========================Author: Natan Lisowski========================
// ===========================Email: pythonboardsbeta@gmail.com=============
// ===========================GitHub: https://github.com/natnqweb ==========
// ===========================LICENSE: MIT License==========================
// ===========================Version: 1.2.0================================
// ===========================DOCUMENTATION=================================
// ======================LINK: https://github.com/natnqweb/EventSystem =====
/*  MIT License

    Copyright(c) 2022 Natan Lisowski

    Permission is hereby granted,
    free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),
    to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and / or sell copies of the Software,
    and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies
    or
    substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS",
    WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    DAMAGES OR OTHER
    LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
// ===========================BASIC EXAMPLE=================================
// =========================================================================
// This is a basic example of how to use the EventSystem library.
//  - The EventSystem library is a simple library that allows you to create
//    events and trigger them.
//  - The EventSystem library is designed to be used with the Arduino framework.
// It will print out the events that are received.
// every 1000ms temperature and humidity will be updated and that change in value will trigger event.
// =========================================================================
// =================================Header Files============================
#include <EventSystem.h>
#include <Arduino.h>
// =================================Header Files============================
// =========================================================================
// ----------------------------GLOBAL---------------------

unsigned long lastUpdateTime = 0;
static const unsigned long updateInterval = 1000; // ms
bool ledState = false;

// ----------------------------GLOBAL---------------------
// =========================================================================

// ---------------------------- AUTOMATIC EVENTS --------------------------

// YOU MUST MAP EVERY EVENT/ naming convention is -> EVENT_(EVENT NAME)
DECLARATION_MAP_BEGIN
EVENT_TemperatureChangedEvent,
EVENT_HumidityChangedEvent,
EVENT_BlinkLED,
DECLARATION_MAP_END

DECLARE_EVENT(TemperatureChangedEvent /*event name*/, temperature /*variable name*/, 15.5 /*initial variable value*/);
DECLARE_EVENT(HumidityChangedEvent, humidity, 65);
DECLARE_EVENT_FUNCTION(BlinkLED); // blink led event // we dont sign variable to it becouse already existing variable will trigger it

//when you declared event add it to event order matters order same as in declaration
EVENT_LIST_START
TemperatureChangedEvent,
HumidityChangedEvent,
BlinkLED,
EVENT_LIST_END

//same as above. remember to add & before variable name
VARIABLE_LIST_START
& temperature,
& humidity,
& temperature,// change in temperature will trigger LED
VARIABLE_LIST_END


// ---------------------------- AUTOMATIC EVENTS --------------------------

// =========================================================================
// =========================================================================
// ----------------------------------SETUP----------------------------------

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    EVENT_SYSTEM_AUTO();
}

// ----------------------------------SETUP----------------------------------
// =========================================================================
// =========================================================================
// ----------------------------------LOOP-----------------------------------

void loop()
{
    EVENT_SYSTEM_RUN();
    if (millis() - lastUpdateTime > updateInterval)
    {
        lastUpdateTime = millis();
        temperature = temperature > 30 ? 20 : temperature + 0.5;
        humidity = humidity > 80 ? 50 : humidity + 1;
    }
    digitalWrite(LED_BUILTIN, ledState);
}

// ----------------------------------LOOP-----------------------------------
// =========================================================================
// =========================================================================
// ---------------------------- EVENTS DEFINITION---------------------------

DEFINE_EVENT_FUNCTION(TemperatureChangedEvent)
{
    Serial.print(F("Temperature updated T = "));
    Serial.print(temperature);
    Serial.println(F("C"));
}

DEFINE_EVENT_FUNCTION(HumidityChangedEvent)
{
    Serial.print(F("Humidity updated H = "));
    Serial.print(humidity);
    Serial.println(F("%"));
}

DEFINE_EVENT_FUNCTION(BlinkLED)
{
    ledState = !ledState;
}

// ---------------------------- EVENTS DEFINITION---------------------------
// =========================================================================
