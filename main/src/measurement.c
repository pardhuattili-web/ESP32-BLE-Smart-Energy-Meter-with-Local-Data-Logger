#include "measurement.h"
#include <math.h>

static uint32_t alarm_flags_for(float v, float i, const measurement_limits_t *limits)
{
    uint32_t flags = 0U;
    if (limits == NULL) return flags;
    if (v > limits->voltage_limit_v) flags |= (1U << 0);
    if (i > limits->current_limit_a) flags |= (1U << 1);
    return flags;
}

float energy_rms(const float *samples, size_t count)
{
    if (samples == NULL || count == 0U) return 0.0f;
    double sum_sq = 0.0;
    for (size_t i = 0U; i < count; ++i)
        sum_sq += (double)samples[i] * (double)samples[i];
    return (float)sqrt(sum_sq / (double)count);
}

float energy_apparent_power(float vrms, float irms) { return vrms * irms; }

float energy_active_power(float apparent_va, float power_factor)
{
    if (power_factor < 0.0f) power_factor = 0.0f;
    if (power_factor > 1.0f) power_factor = 1.0f;
    return apparent_va * power_factor;
}

float energy_accumulate_wh(float energy_wh, float active_power_w, float dt_seconds)
{
    if (dt_seconds <= 0.0f) return energy_wh;
    return energy_wh + active_power_w * (dt_seconds / 3600.0f);
}

void energy_build_measurement(
    const float *voltage_samples,
    const float *current_samples,
    size_t count,
    float power_factor,
    float previous_energy_wh,
    float dt_seconds,
    const measurement_limits_t *limits,
    uint32_t sample_count,
    energy_measurement_t *out)
{
    if (out == NULL) return;
    const float v = energy_rms(voltage_samples, count);
    const float i = energy_rms(current_samples, count);
    const float s = energy_apparent_power(v, i);
    const float p = energy_active_power(s, power_factor);

    out->voltage_rms_v = v;
    out->current_rms_a = i;
    out->apparent_power_va = s;
    out->active_power_w = p;
    out->power_factor = power_factor;
    out->energy_wh = energy_accumulate_wh(previous_energy_wh, p, dt_seconds);
    out->sample_count = sample_count;
    out->alarm_flags = alarm_flags_for(v, i, limits);
}
