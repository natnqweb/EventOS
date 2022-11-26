
# **EventOS Library** Version - 1.1.0

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
| ------------------- | --------------------------- |
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

# MODIFYING PIN SUPPORT (FOR ANY BOARD)

You can modify supported pins array whatever you like (add, remove) - basicaly adjust it to any board.

1. **recommended** way
   
   using automatic macro

   ``` C++

    #define DEBUG
    #include <EventOS.h>
    // this example is for any board adjust for your own usage
    // map two buttons for example button A will be connected to real board pin 4 and button b to pin 5
    // there is no debouncing so you might notice some pin bouncing by default pins are PULLED_UP via internal resistor
    #define BUTTON_PIN_A 4
    #define BUTTON_PIN_B 5

    OVERRIDE_PINMAPPING_START
    ADD_PIN(BUTTON_PIN_A)
    ADD_PIN(BUTTON_PIN_B)
    OVERRIDE_PINMAPPING_END

    void OnPinAChangeEvent()
    {
    LOG("Pin A State changed to: ");
    // retrieve pin state from Pin A using GetPinState Function
    LOGLN(GetPinState(BUTTON_PIN_A));
    }

    void OnPinBChangeEvent()
    {
    LOG("Pin B State changed to: ");
    // retrieve pin state from Pin B using GetPinState Function
    LOGLN(GetPinState(BUTTON_PIN_B));
    }
    // when u use OVERRIDE_PINMAPPING macro to change default pins you must use PROGRAM_SETUP_AUTO()
    void PROGRAM_SETUP_AUTO(115200)
    {
    AddEventListener(BUTTON_PIN_A, ON_CHANGE_EVENT, OnPinAChangeEvent);
    AddEventListener(BUTTON_PIN_B, ON_CHANGE_EVENT, OnPinBChangeEvent);
    }

    void PROGRAM_LOOP()
    {

    }

   ```
   

2. another way (advanced) modifying source

    *default is:*

    ``` C++
    // EventOS\src\PinMapping.h
    #ifndef PIN_MAPPING
    #define PIN_MAPPING

    typedef unsigned char PinType;
    typedef PinType ArrSizeType;
    #include "MappingMacro.h"

    #ifdef EVENT_OS
    START_PIN_ARRAY
    #if defined(ESP8266) 
    // ADD REAL HARDWARE PIN TO ARRAY. ALL PINS ADDED TO ARRAY WILL SUPPORT EVENTS
    ADD_PIN(5)
    ADD_PIN(4)
    ADD_PIN(14)
    ADD_PIN(12)
    ADD_PIN(13)
    #elif defined(ESP32)
    ADD_PIN(4)
    ADD_PIN(5)
    ADD_PIN(13)
    ADD_PIN(14)
    ADD_PIN(15)
    ADD_PIN(16)
    ADD_PIN(17)
    ADD_PIN(18)
    ADD_PIN(19)
    ADD_PIN(21)
    ADD_PIN(22)
    ADD_PIN(23)
    ADD_PIN(25)
    ADD_PIN(26)
    ADD_PIN(27)
    ADD_PIN(32)
    ADD_PIN(33)
    ADD_PIN(34)
    ADD_PIN(35)
    ADD_PIN(36)
    ADD_PIN(39)
    #elif  defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO)
    ADD_PIN(2)
    ADD_PIN(3)
    ADD_PIN(4)
    ADD_PIN(5)
    ADD_PIN(6)
    ADD_PIN(7)
    ADD_PIN(8)
    ADD_PIN(9)
    ADD_PIN(10)
    ADD_PIN(11)
    ADD_PIN(12)
    ADD_PIN(13)
    #else
    // ADD YOUR BOARD PINS HERE MODIFY THIS ARRAY AS YOU NEED
    ADD_PIN(2)
    ADD_PIN(3)
    ADD_PIN(4)
    ADD_PIN(5)
    ADD_PIN(6)
    ADD_PIN(7)
    ADD_PIN(8)
    ADD_PIN(9)
    ADD_PIN(10)
    ADD_PIN(11)
    ADD_PIN(12)
    ADD_PIN(13)
    #endif
    END_PIN_ARRAY

    #endif // EVENT_OS

    #endif // PIN_MAPPING

    ```

3. **another way (more Generic)**

    you can override default code behaviour by using __OVERRIDE specification before void PROGRAM_SETUP(BAUD) and providing arguments to ChangEvents function:

    ```C++
    #define DEBUG
    #include <EventOS.h>
    // for this example Custom mapping pins in esp8266
    // you can custom map any board as long as it is supported by arduino framework
    // esp32 , esp8266 .. all arduino.. raspberrypi .. stm ... etc... 
    static const ArrSizeType numberOfPins{ 2 };
    PinType customPinMap[numberOfPins]
    {
        //* REAL ACTUAL BOARD PIN - pin that you pass for example to digitalRead(REAL ACTUAL BOARD PIN)
        ADD_PIN(5)
        ADD_PIN(4)
    };

    // define PinEvent array it hold your events
    PinEvent customEvents[numberOfPins]{};

    void Pin5FallingEvent()
    {
        LOG("pin 1 state changed from 1 to ");
        LOGLN(GetPinState(5));
    }

    void Pin4FallingEvent()
    {
        LOG("pin 2 state changed from 1 to ");
        LOGLN(GetPinState(4));
    }
    // OVERRIDE DEFAULT PROGRAM_SETUP
    __OVERRIDE void PROGRAM_SETUP(115200)
    {
        // this ovverrides all default events with custom events
        ChangeEvents(customPinMap, customEvents, numberOfPins);

        //USER CODE
        //HERE ...
        AddEventListener(5, ON_FALLING_EDGE_EVENT, Pin5FallingEvent);
        AddEventListener(4, ON_FALLING_EDGE_EVENT, Pin4FallingEvent);
        LOGLN("program started");
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

1. `void ChangeEvents(PinMap* pinMapping, PinEvent* newEvents, IndexType numberOfNewEvents)`

    description:
        Function for overriding default behaviour look at example: FullyCustom.ino

2. `TurnOffEventsOnPin(pin, reset = false (optional))`

    description:
        turns off all events on given pin if reset set to true events are turned on back

3. `AddEventListener(pin,event,function)`

    description:
        calls function whenever event happens on given pin

4. `bool GetPinState(PinType boardPin)`

    description:
        Returns actual state of pin very handy if you are using ON_CHANGE_EVENT and want to know what is the state of pin right now

5. `void ShutDownEventOS()`, `void TurnOnEventOS()`

    description: Functions for turninging on and turning off whole EventOS logic Functions

**LICENSE**
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
