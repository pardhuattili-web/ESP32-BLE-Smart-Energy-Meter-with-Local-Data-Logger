#include "fault_monitor.h"

static uint32_t latched_flags;

void fault_monitor_init(void) { latched_flags = 0U; }

void fault_monitor_process(energy_measurement_t *measurement)
{
    if (measurement == NULL) return;
    latched_flags |= measurement->alarm_flags;
    measurement->alarm_flags = latched_flags;
}
