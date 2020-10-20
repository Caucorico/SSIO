#include <stdio.h>
#include "contiki.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"


/* ---------------------------------------------------------------- */
PROCESS(exercice01, "Exercice 01");
AUTOSTART_PROCESSES(&exercice01);
/* ---------------------------------------------------------------- */

PROCESS_THREAD(exercice01, ev, data)
{
	int pressed = 0;
	PROCESS_BEGIN();
	SENSORS_ACTIVATE(button_sensor);
	while(1)
	{
		PROCESS_WAIT_EVENT();
		pressed = (ev == sensors_event && data == &button_sensor);
		if ( pressed )
		{
			if ( leds_get() == 0 )
			{
				printf("start\n");
				leds_on(LEDS_RED);
			}
			else
			{
				printf("no_start\n");
				leds_toggle(LEDS_GREEN|LEDS_RED);
			}
		}
		
	}

	PROCESS_END();
}
