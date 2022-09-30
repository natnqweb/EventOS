#define DEBUG
#include <EventOS.h>

void LogHelloFromEventOS()
{
    LOGLN("HelloFromEventOS");
}

PROGRAM_SETUP(115200)
{
    AddEventListener(_PIN_D2, ON_RAISE_EVENT, LogHelloFromEventOS);
}

PROGRAM_LOOP()
{

}
