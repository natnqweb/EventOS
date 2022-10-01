
# **EventOS Library**

## Fully Tested On

### ESPRESSIF

- [x] - ESP8266 - NodeMcu 0.9
- [x] - ESP8266 - NodeMcu 1.0
- [X] - ESP8266 - Wemos D1 R1
- [X] - ESP32
- [ ] - Others *

### Arduino

- [x] - Arduino Uno R3
- [x] - Arduino Mega
- [X] - Arduino Nano
- [ ] - Others *

### RaspberryPi

- [X] - Pico

### STM

- [ ] - Not Yet *

#### * feel free to leave feedback when you tested it yourself and report issues via issue tab on github

## **Event based system designed for Arduino Framework**

### EventOS alllows you to add event listener to any pin

## Supported Events On Pins

| Event               | Equivalent macro in EventOS |
| -----------         | -----------                 |
| on pin state change | `ON_CHANGE_EVENT`           |
| on rising edge      | `ON_RISING_EDGE_EVENT`      |
| on falling edge     | `ON_FALLING_EDGE_EVENT`     |

### **Pin state change in time and event calls graph:**

![graph](<assets/events_graph.png>)

# **EventOS Main program structure**

- Normal arduino program structure 'BareMinimum.ino'
  
``` C++

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

```

- EventOS BareMinimum

``` C++
#define DEBUG // remove this line if not using LOG and Serial port
#include <EventOS.h>

void PROGRAM_SETUP(115200) /*115200 - Serial Port Baud rate */
{

}

void PROGRAM_LOOP()
{

}
```

# *Pin Mapping*

You can custom map pins whatever you like (add, remove, rearrange) - basicaly adjust it to any board.

*default is:*

``` C++
// EventOS\src\PinMapping.h

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

```

# **Pin Remaping example**

remap pins in library src directory!

```C++

// EventOS\src\PinMapping.h

#ifndef PIN_MAPPING
#define PIN_MAPPING _PINMAPPING

struct PinMap { unsigned char pin, index; };

enum PinMapping
{
    _PIN_V1,
    _PIN_V2,
    NUMBER_OF_PINS // keep NUMBER_OF_PINS always at end of enum
};

#ifdef EVENT_OS
static const PinMap s_map[NUMBER_OF_PINS]
{
    // {actual hardware pin number, pin name used in code}
    {3,_PIN_V1},
    {2,_PIN_V2},
};
#endif // EVENT_OS

#endif // PIN_MAPPING

```

then you can use your remaped pins

``` C++
#define DEBUG
#include <EventOS.h>

static const int ledPin = 13;
bool ledState = true;

void ChangeLedState()
{
    LOGLN("pin state has changed");
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
}

void PrintPinStateIsFalling()
{
    LOGLN("Pin State is falling");
}

void PrintPinStateIsRising()
{
    LOGLN("Pin State is Rising");
}

void PROGRAM_SETUP(115200)
{
    pinMode(ledPin, OUTPUT);
    AddEventListener(_PIN_V1, ON_CHANGE_EVENT, ChangeLedState); // event fired when state is changing 0 -> 1 or 1 -> 0
    AddEventListener(_PIN_V1, ON_RISING_EDGE_EVENT, PrintPinStateIsRising); // event fired on pin rising edge 0 -> 1
    AddEventListener(_PIN_V1, ON_FALLING_EDGE_EVENT, PrintPinStateIsFalling); // event fired on pin falling edge1 -> 0
}

void PROGRAM_LOOP()
{

}

```

# **How To Add Event Listener**

1. Create you own function that will be called whenever subscribed event is fired this function must return void and take no params example:

``` C++
void your_function()
{
    /* your code */
}
```

2. then you need to Add Event Listener using `AddEventListener` function in setup
example:

``` C++
 AddEventListener(_PIN_D2, ON_CHANGE_EVENT, your_function); // event will be fired when state is changing 0 -> 1 or 1 -> 0
```

# **Functions**

`TurnOffEventsOnPin(pin, reset = false (optional))`

turns off all events on given pin if reset set to true events are turned on back
=

`AddEventListener(pin,event,function)`

calls function whenever event happens on given pin
=

MIT License

Copyright (c) 2022 Natan Lisowski

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
