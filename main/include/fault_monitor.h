#pragma once
#include "measurement.h"
void fault_monitor_init(void);
void fault_monitor_process(energy_measurement_t *measurement);
