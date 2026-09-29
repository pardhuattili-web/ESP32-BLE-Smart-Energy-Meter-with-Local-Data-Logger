#include "fault_monitor.h"
static uint32_t latched;
void fault_monitor_init(void){latched=0;}
void fault_monitor_process(energy_measurement_t*m){if(!m)return;latched|=m->alarm_flags;m->alarm_flags=latched;}