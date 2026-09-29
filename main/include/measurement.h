#pragma once
#include <stddef.h>
#include <stdint.h>
typedef struct { float voltage_rms_v; float current_rms_a; float apparent_power_va; float active_power_w; float power_factor; float energy_wh; uint32_t sample_count; uint32_t alarm_flags; } energy_measurement_t;
typedef struct { float voltage_limit_v; float current_limit_a; } measurement_limits_t;
float energy_rms(const float*, size_t); float energy_apparent_power(float,float); float energy_active_power(float,float); float energy_accumulate_wh(float,float,float);
void energy_build_measurement(const float*,const float*,size_t,float,float,float,const measurement_limits_t*,uint32_t,energy_measurement_t*);