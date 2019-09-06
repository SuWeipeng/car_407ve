#ifndef __RTT_INTERFACE_H
#define __RTT_INTERFACE_H

#include <entry.h>

#define LED_PIN    GET_PIN(B, 12)

extern rt_thread_t led_thread;
extern rt_thread_t log_thread;

void led_thread_entry(void* parameter);
void log_thread_entry(void* parameter);

#endif
