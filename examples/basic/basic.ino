#define DEBUG
#include <EventOS.h>

void LogHelloFromEventOS()
{
    LOGLN("HelloFromEventOS");
}

SETUP_START(115200)
AddEventListener(_PIN_D2, ON_RAISE_EVENT, LogHelloFromEventOS);
SETUP_END

LOOP_START

LOOP_END
