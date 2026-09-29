#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct {
    float voltage_rms_v;
    float current_rms_a;
    float apparent_power_va;
    float active_power_w;
    float power_factor;
    float energy_wh;
    uint32_t sample_count;
    uint32_t alarm_flags;
} energy_measurement_t;

typedef struct {
    float voltage_limit_v;
    float current_limit_a;
} measurement_limits_t;

float energy_rms(const float *samples, size_t count);
float energy_apparent_power(float vrms, float irms);
float energy_active_power(float apparent_va, float power_factor);
float energy_accumulate_wh(float energy_wh, float active_power_w, float dt_seconds);
void energy_build_measurement(
    const float *voltage_samples,
    const float *current_samples,
    size_t count,
    float power_factor,
    float previous_energy_wh,
    float dt_seconds,
    const measurement_limits_t *limits,
    uint32_t sample_count,
    energy_measurement_t *out
);
