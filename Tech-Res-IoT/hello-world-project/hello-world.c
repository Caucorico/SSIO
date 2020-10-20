#include <stdio.h>
#include "contiki.h"

PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);

PROCESS_THREAD(hello_world_process, ev, data)
{
	PROCESS_BEGIN();
	printf("Hello world !\n");
	/* write(0, "Hello from System\n", 18); */
	PROCESS_END();
}
