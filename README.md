
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

# CUSTOM PIN REMAPPING (FOR ANY BOARD)

You can custom map pins whatever you like (add, remove, rearrange) - basicaly adjust it to any board.

1. **recommended** way
   
   using automatic macro

   ``` C++

    #define DEBUG
    #include <EventOS.h>
    // this example is for any board adjust  custom
    // if you use this macro there will be 50 Virtual Pins for your disposition numbered like this : VIRTUAL_PIN1, VIRTUAL_PIN2, VIRTUAL_PIN3 ,VIRTUAL_PIN4 ... VIRTUAL_PIN50
    // just map real board pins to them and use in code
    // map two buttons for example button A will be connected to real board pin 4 and button b to pin 5 adjust it whatever you like
    // there is no debouncing so you might notice some pin bouncing by default pins are PULLED_UP via internal resistor
    #define BUTTON_PIN_A 4
    #define BUTTON_PIN_B 5

    OVERRIDE_PINMAPPING_START
    MERGE_PINS(BUTTON_PIN_A, VIRTUAL_PIN1)
    MERGE_PINS(BUTTON_PIN_B, VIRTUAL_PIN2)
    OVERRIDE_PINMAPPING_END

    void OnVirtualPin1ChangeEvent()
    {
    LOG("Virtual Pin 1 State changed to: ");
    // retrieve pin state from Virtual Pin1 using GetPinState Function
    LOGLN(GetPinState(VIRTUAL_PIN1));
    }

    void OnVirtualPin2ChangeEvent()
    {
    LOG("Virtual Pin 2 State changed to: ");
    // retrieve pin state from Virtual Pin2 using GetPinState Function
    LOGLN(GetPinState(VIRTUAL_PIN2));
    }

    void PROGRAM_SETUP_AUTO(115200)
    {
    AddEventListener(VIRTUAL_PIN1, ON_CHANGE_EVENT, OnVirtualPin1ChangeEvent);
    AddEventListener(VIRTUAL_PIN2, ON_CHANGE_EVENT, OnVirtualPin2ChangeEvent);
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
    typedef PinType IndexType;
    #include "MappingMacro.h"

    START_MAPPING_DECLARATION
    #if defined(ESP8266) 
    _PIN_D1,
    _PIN_D2,
    _PIN_D5,
    _PIN_D6,
    _PIN_D7,
    #elif defined(ESP32)
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
    #elif defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO)
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
    #else
    // THIS IS WHERE YOU PLACE YOUR OWN VIRTUAL PINS FOR ANY BOARD THAT IS NOT LISTED AS ABOVE
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
    #if defined(ESP8266) 
    // Merge (actual hardware pin number, pin name used in code)
    // connecting real pins with virtual pins

    MERGE_PINS(5, _PIN_D1)
    MERGE_PINS(4, _PIN_D2)
    MERGE_PINS(14, _PIN_D5)
    MERGE_PINS(12, _PIN_D6)
    MERGE_PINS(13, _PIN_D7)
    #elif defined(ESP32)
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
    #elif  defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO)
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
    #else
    // THIS IS WHERE YOU MERGE YOUR CUSTOM PIN WITH REAL BOARD PIN 
    // FOR EXAMPLE YOU MIGHT  WANT TO MAP HERE RASPBERRYPI OR STM BOARD PINS TO VIRTUAL PINS
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

    ```

3. **another way (more Generic)**

    you can override default code behaviour by using __OVERRIDE specification before void PROGRAM_SETUP(BAUD) and providing arguments to ChangEvents function:

    ```C++

    #define DEBUG
    #include <EventOS.h>
    // for this example Custom mapping pins in esp8266
    // you can custom map any board as long as it is supported by arduino framework
    // esp32 , esp8266 .. all arduino.. raspberrypi .. stm ... etc... 


    // define your custom virtual pins to use them later in program
    enum CustomVirtualPins : PinType
    {
        VIRTUAL_PIN1,
        VIRTUAL_PIN2,
        TOTAL_NUMBER_OF_CUSTOM_PINS // this entry always needs to be last in enum
    };

    //map real pins and virtual pins together
    PinMap customPinMap[TOTAL_NUMBER_OF_CUSTOM_PINS]
    {
        // MERGE_PINS(REAL ACTUAL BOARD PIN,  YOUR VIRTUALPIN)
        //* REAL ACTUAL BOARD PIN - pin that you pass for example to digitalRead(REAL ACTUAL BOARD PIN)
        MERGE_PINS(5, VIRTUAL_PIN1)
        MERGE_PINS(4, VIRTUAL_PIN2)
    };

    // define PinEvent array it hold your events
    PinEvent customEvents[TOTAL_NUMBER_OF_CUSTOM_PINS]{};

    void VPin1FallingEvent()
    {
        LOG("pin 1 state changed from 1 to ");
        LOGLN(GetPinState(VIRTUAL_PIN1));
    }

    void VPin2FallingEvent()
    {
        LOG("pin 2 state changed from 1 to ");
        LOGLN(GetPinState(VIRTUAL_PIN2));
    }
    // OVERRIDE DEFAULT PROGRAM_SETUP
    __OVERRIDE void PROGRAM_SETUP(115200)
    {
        // this ovverrides all default events with custom events
        ChangeEvents(customPinMap, customEvents, TOTAL_NUMBER_OF_CUSTOM_PINS);
        // Init PinEvents after you changed to your custom events
        InitPinEvents();

        //USER CODE
        //HERE ...
        AddEventListener(VIRTUAL_PIN1, ON_FALLING_EDGE_EVENT, VPin1FallingEvent);
        AddEventListener(VIRTUAL_PIN2, ON_FALLING_EDGE_EVENT, VPin2FallingEvent);
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
        Function for custom mapping pins and overriding default behaviour look at example: FullyCustom.ino

1. `TurnOffEventsOnPin(pin, reset = false (optional))`

    description:
        turns off all events on given pin if reset set to true events are turned on back

1. `AddEventListener(pin,event,function)`

    description:
        calls function whenever event happens on given pin

1. `const bool& GetPinState(PinType virtualPin)`

    description:
        Returns actual state of pin that is mapped to virtualPin very handy if you are using ON_CHANGE_EVENT and want to know what is the state of pin right now

1. `void ShutDownEventOS()`, `void TurnOnEventOS()`

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
