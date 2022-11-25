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