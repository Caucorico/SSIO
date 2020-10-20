#include "contiki.h"
#include "net/rime.h"
#include "dev/cc2420.h"
#include "dev/leds.h"
#include <stdio.h>

PROCESS(receiver_process, "Receiver process");
AUTOSTART_PROCESSES(&receiver_process);

static void set_leds(int i){
  if (i & 0x1) {
    leds_on(LEDS_RED);
  } else {
    leds_off(LEDS_RED);
  }
  if (i & 0x2) {
    leds_on(LEDS_GREEN);
  } else {
    leds_off(LEDS_GREEN);
  }
  if (i & 0x4) {
    leds_on(LEDS_BLUE);
  } else {
    leds_off(LEDS_BLUE);
  }
}

static void abc_recv(struct abc_conn *c)
{
  int rssi = cc2420_last_rssi;
  char color_flags = 0;

  if ( rssi < -24 ) {
    color_flags = 0;
  } else if ( rssi < -20 && rssi >= -24 ) {
    color_flags = 1;
  } else if ( rssi < -16 && rssi >= -20 ) {
    color_flags = 2;
  } else if ( rssi < -12 && rssi >= -16 ) {
    color_flags = 3;
  } else if ( rssi < -8  && rssi >= -12 ) {
    color_flags = 4;
  } else if ( rssi < -4  && rssi >= -8  ) {
    color_flags = 5;
  } else if ( rssi < 0   && rssi >= -4  ) {
    color_flags = 6;
  } else {
    color_flags = 7;
  }
  
  set_leds(color_flags);
}

PROCESS_THREAD(receiver_process, ev, data){
  static const struct abc_callbacks abc_call = {abc_recv};
  static struct abc_conn abc;
  PROCESS_EXITHANDLER(abc_close(&abc));
  PROCESS_BEGIN();
  printf("Receiver!\n");

  abc_open(&abc, 128, &abc_call);  

  PROCESS_END();
}
