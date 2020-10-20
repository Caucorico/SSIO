#include "contiki.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include <stdio.h>

PROCESS(count_process, "Count process");
AUTOSTART_PROCESSES(&count_process);

PROCESS_THREAD(count_process, ev, data)
{
  char pressed = 0;
  static struct etimer et;
  static int i = 0;
  PROCESS_BEGIN();
  SENSORS_ACTIVATE(button_sensor);

  while(1)
  {
    PROCESS_WAIT_EVENT();
    pressed = (ev == sensors_event && data == &button_sensor );
    if ( pressed )
    {
      while(1)
      {
        etimer_set(&et, CLOCK_SECOND);
        PROCESS_WAIT_EVENT();
        if ( etimer_expired(&et) )
        {
          printf(" i = %d \n", i);

          /* Le code couleur est permutte par rapport a la consigne */
          leds_off( ~((LEDS_RED|LEDS_BLUE|LEDS_GREEN)&i) );
          leds_on( (LEDS_RED|LEDS_BLUE|LEDS_GREEN)&i );
          i++;
        } 
      }
      break;
    }
  }
  PROCESS_END();
}
