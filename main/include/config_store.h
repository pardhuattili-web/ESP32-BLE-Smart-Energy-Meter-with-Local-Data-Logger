#pragma once
#include <stdint.h>
#include "measurement.h"

typedef struct {
    uint32_t sample_period_ms;
    uint32_t log_period_ms;
    measurement_limits_t limits;
} energy_config_t;

void config_store_defaults(energy_config_t *config);
int config_store_save(const energy_config_t *config);
int config_store_load(energy_config_t *config);
