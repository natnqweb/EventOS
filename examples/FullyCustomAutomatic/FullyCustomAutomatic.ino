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